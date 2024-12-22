/*
 * ultrasonic.c
 *
 * Created: 8/27/2023 6:37:47 PM
 *  Author: husse
 */ 

#include "ultrasonic.h"

void H_ultrasonic_init(ultrasonic_object UTS){
	M_DIO_set_pin_direction(UTS.port,UTS.triger,output);
	M_Timer_1_input_capture_unit_init(rinsing_edge);
}

u16 H_ultrasonic_measure(ultrasonic_object UTS){
	M_DIO_set_pin_value(UTS.port,UTS.triger,low);
	_delay_us(2);
	M_DIO_set_pin_value(UTS.port,UTS.triger,high);
	_delay_us(10);
	M_DIO_set_pin_value(UTS.port,UTS.triger,low);
	return ((M_Timer_1_pulse_width()*34300)/(F_CPU*2));
}