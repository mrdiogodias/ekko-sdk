#ifndef __TIMER__ /* prevent circular inclusions */
#define __TIMER__ /* by using protection macros */


/*****  Include Files *****/

#include "bsp.h"

/***** Macros (Inline Functions) Definitions *****/

#define TIMER_VALUE_OK       0U
#define TIMER_VALUE_ERROR    1U

typedef uint32_t TIMER_ValueType;


/***** Type Definitions *****/

typedef struct{
    uint64_t compare_value;
    uint8_t  interrupt_enable;
    uint8_t  auto_reload;   
} TIMER_InitType;


/***** Type Definitions *****/

TIMER_ValueType TIMER_Initialize(TIMER_Type *timer, TIMER_InitType init_values);
TIMER_ValueType TIMER_Start(TIMER_Type *timer);
uint64_t        TIMER_Get_Counter(TIMER_Type *timer);
TIMER_ValueType TIMER_Stop(TIMER_Type *timer);
TIMER_ValueType TIMER_Wait(TIMER_Type *timer);


/***** External Variables *****/

extern TIMER_Type *timer0;
extern TIMER_Type *timer1;

#endif