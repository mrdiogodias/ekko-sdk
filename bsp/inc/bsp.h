#ifndef __BSP__ /* prevent circular inclusions */
#define __BSP__ /* by using protection macros */


/*****  Include Files *****/

#include <stdint.h>


/***** Macros *****/
  
#define TIMER0_BASE  0x20000
#define TIMER1_BASE  0x21000
#define I2C_BASE     0x22000

#define SYS_CLK_FREQ 41500000 /* 40 MHz */


/*****  Device Peripheral Access Layer *****/

typedef struct {
    union {
        struct {
            uint32_t reserved    : 27;
            uint8_t  overflow    : 1;
            uint8_t  auto_reload : 1;
            uint8_t  interrupt   : 1;
            uint8_t  enable      : 1; 
            uint8_t  start       : 1;
        } bit;
        uint32_t config_register;
    } CONF_REG;             /* (TIMER_BASE_ADDR + 0x00) */
    uint32_t DATA_REG_HIGH; /* (TIMER_BASE_ADDR + 0x04) */
    uint32_t DATA_REG_LOW;  /* (TIMER_BASE_ADDR + 0x08) */
    uint32_t CMP_REG_HIGH;  /* (TIMER_BASE_ADDR + 0x0C) */
    uint32_t CMP_REG_LOW;   /* (TIMER_BASE_ADDR + 0x10) */
} TIMER_Type;


typedef struct {
    union {
        struct {
            uint8_t  addr;
            uint8_t  start              : 1;
            uint8_t  error              : 1;
            uint8_t  valid_transmission : 1;
            uint8_t  valid_reception    : 1;
            uint8_t  enable             : 1;
            uint8_t  interrupt          : 1;
            uint8_t  reserved           : 2;
            uint16_t prescaler;
        } bit;
        uint32_t config_register0;
    } CONF0_REG;         /* (I2C_BASE_ADDR + 0x00) */
    uint32_t CONF1_REG;  /* (I2C_BASE_ADDR + 0x04) */
    uint32_t CONF2_REG;  /* (I2C_BASE_ADDR + 0x08) */
    union {
        struct {
            uint8_t  reserved;
            uint8_t  data_received;
            uint8_t  data_size;
            uint8_t  data_to_send; 
        } bit;
        uint32_t config_register3;
    } CONF3_REG;         /* (I2C_BASE_ADDR + 0x0C) */
} I2C_Type;


/***** Function prototypes *****/

/* Software delays */
void sleep_us(unsigned long us);
void sleep_ms(unsigned long ms);

/* Memset implementation */
void *my_memset(void *s, int c, unsigned int len);


/***** External Variables *****/

/* Don't remove this variable. */
extern uint32_t *dummy_var;

#endif