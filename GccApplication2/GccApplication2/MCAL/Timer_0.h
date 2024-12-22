/*
 * Timer_0.h
 *
 * Created: 6/23/2023 10:21:40 AM
 *  Author: husse
 */ 


#ifndef TIMER_0_H_
	#define TIMER_0_H_
	#include "../UTIL/macros.h"
	#include "../UTIL/data_types.h"
	#include "../CPU_configuration.h"
	#include "../MCAL/M_DIO.h"
	#include <avr/io.h>
	#include <avr/interrupt.h>	


	typedef enum 
	{
		normal,
		CTC,
		PWM
	}wave_form_generator_mode;
	

	void M_Timer_0_init(wave_form_generator_mode generator_mode);
	void M_Timer_0_compared_value(u8 compared_value);
	void M_Timer_0_start(u8 prescaler);
	void M_Timer_0_stop(void);
	void M_Timer_0_reset(void);
	
	
	#define max_PWM_pins 3
		
	void M_Timer_0_PWM_init(void);
	void M_Timer_0_PWM(int pin,u8 PWM_duty_cycle);
		



#endif /* TIMER_0_H_ */