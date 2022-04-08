#include "i2c.h"

I2C_Type *i2c =  ((I2C_Type *) I2C_BASE);

static inline void I2C_Clear_Regs(I2C_Type *i2c) {
	i2c->CONF0_REG.config_register0 = 0;
	i2c->CONF1_REG                  = 0;
	i2c->CONF2_REG                  = 0;
	i2c->CONF3_REG.config_register3 = 0;
}

I2C_ValueType I2C_Initialize(I2C_Type *i2c, I2C_InitType init_values) {
	I2C_Clear_Regs(i2c);

	i2c->CONF0_REG.bit.prescaler = SYS_CLK_FREQ / (2 * init_values.OperationMode * 1000) - 1;
	i2c->CONF0_REG.bit.enable    = 1;
	i2c->CONF0_REG.bit.interrupt = init_values.interrupt_enable;

	return I2C_VALUE_OK;
}

I2C_ValueType I2C_Transmit(I2C_Type *i2c, uint8_t addr, uint8_t *data, uint8_t data_size) {
	/* Clear device addr */
	i2c->CONF0_REG.bit.addr = 0;

	/* Clear data and data size */
	i2c->CONF1_REG = 0;
	i2c->CONF2_REG = 0;
	i2c->CONF3_REG.bit.data_size = 0;

	/* In a transmission RW needs to be 0 */
	if(addr & 0x1) {
		return I2C_VALUE_INVALID_ADDR;
	}

	/* 9 bytes is the maximum that can be transfered for each transmission */
	if(data_size > 9) {
		return I2C_VALUE_INVALID_SIZE;
	}

	/* Fill the register with the data to send */
	i2c->CONF1_REG = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	i2c->CONF2_REG = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
	i2c->CONF3_REG.bit.data_to_send = data[8];
	i2c->CONF3_REG.bit.data_size    = data_size;

	/* Start communication */
	i2c->CONF0_REG.bit.addr  = addr;
    i2c->CONF0_REG.bit.start = 1;

    /* Wait for the valid transmission bit */
	while(i2c->CONF0_REG.bit.valid_transmission == 0){}

    return I2C_VALUE_OK;
}

I2C_ValueType I2C_Receive(I2C_Type *i2c, uint8_t addr, uint8_t *data) {
	/* Clear device addr */
	i2c->CONF0_REG.bit.addr = 0;

	/* Clear reg1 because the 1st byte is the register addr */
	i2c->CONF1_REG = 0;

	/* In a reception RW needs to be 1 */
	if(!(addr & 0x1)) {
		return I2C_VALUE_INVALID_ADDR;
	}

	/* Insert the register addr in the 1st MSByte of reg1 */
	i2c->CONF1_REG  = (data[0] << 24);
	
	/* Start communication */
	i2c->CONF0_REG.bit.addr  = addr;
    i2c->CONF0_REG.bit.start = 1;

	/* Wait for the valid reception bit */
    while(i2c->CONF0_REG.bit.valid_reception == 0){}

	data[1] = i2c->CONF3_REG.bit.data_received;
	
	return I2C_VALUE_OK;
}
