#include "timer.h"

TIMER_Type *timer0 =  ((TIMER_Type *) TIMER0_BASE);
TIMER_Type *timer1 =  ((TIMER_Type *) TIMER1_BASE);

static inline void TIMER_Clear_Regs(TIMER_Type *timer) {
	timer->CMP_REG_HIGH             = 0;
	timer->CMP_REG_LOW              = 0;
	timer->CONF_REG.config_register = 0;
	timer->DATA_REG_HIGH 			= 0;
	timer->DATA_REG_LOW 			= 0;
}

TIMER_ValueType TIMER_Initialize(TIMER_Type *timer, TIMER_InitType init_values) {
	TIMER_Clear_Regs(timer);

	timer->CMP_REG_HIGH 			= (uint32_t) (init_values.compare_value >> 32);
	timer->CMP_REG_LOW 			    = (uint32_t) init_values.compare_value;
	timer->CONF_REG.bit.auto_reload = init_values.auto_reload;
	timer->CONF_REG.bit.interrupt   = init_values.interrupt_enable;
	timer->CONF_REG.bit.enable      = 1;

	return TIMER_VALUE_OK;
}

TIMER_ValueType TIMER_Start(TIMER_Type *timer) {
	timer->CONF_REG.bit.start = 1;

	return TIMER_VALUE_OK;
}

uint64_t TIMER_Get_Counter(TIMER_Type *timer) {	
	return (((uint64_t) timer->DATA_REG_HIGH) << 32) | ((uint64_t) timer->DATA_REG_LOW);
}

TIMER_ValueType TIMER_Stop(TIMER_Type *timer) {
	timer->CONF_REG.bit.enable = 0;

	return TIMER_VALUE_OK;
}

TIMER_ValueType TIMER_Wait(TIMER_Type *timer) {
	while(timer->CONF_REG.bit.overflow == 0);

	timer->CONF_REG.bit.overflow = 0;

	return TIMER_VALUE_OK;
}