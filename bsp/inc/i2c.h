#ifndef __I2C__ /* prevent circular inclusions */
#define __I2C__ /* by using protection macros */

/***** Include Files *****/

#include "bsp.h"

/***** Macros (Inline Functions) Definitions *****/

#define I2C_VALUE_OK           0U
#define I2C_VALUE_INVALID_SIZE 1U
#define I2C_VALUE_INVALID_ADDR 2U
#define I2C_VALUE_ERROR        3U

typedef uint32_t I2C_ValueType;


/***** Type Definitions *****/

typedef enum {
    Standard    = 100,  /* 100khz */
    Fast        = 400,  /* 400khz */
    High_Speed  = 3400, /* 3.4Mhz */
} I2C_OperationModeType;

typedef struct{
    I2C_OperationModeType OperationMode;  
    uint8_t  interrupt_enable;   
} I2C_InitType;


/***** Type Definitions *****/

I2C_ValueType I2C_Initialize(I2C_Type *i2c, I2C_InitType init_values);
I2C_ValueType I2C_Transmit(I2C_Type *i2c, uint8_t addr, uint8_t *data, uint8_t data_size);
I2C_ValueType I2C_Receive(I2C_Type *i2c, uint8_t addr, uint8_t *data);


/***** External Variables *****/

extern I2C_Type *i2c;

#endif