/*
 * Timer_.h
 *
 * Created: 8/27/2023 5:29:19 PM
 *  Author: husse
 */ 


#ifndef TIMER__H_
	#define TIMER__H_
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include "../UTIL/macros.h"
	#include "../UTIL/data_types.h"
	#include "../CPU_configuration.h"
	
	typedef enum 
	{
		falling_edge,
		rinsing_edge
	}interruption_edge;

	void M_Timer_1_input_capture_unit_init(interruption_edge edge);
	u16 M_Timer_1_pulse_width(void);
	//u8 M_UTS(void);

#endif /* TIMER__H_ */