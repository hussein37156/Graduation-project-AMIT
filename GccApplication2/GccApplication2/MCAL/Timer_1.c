/*
 * Timer_1.c
 *
 * Created: 8/27/2023 5:29:50 PM
 *  Author: husse
 */ 

#include "Timer_1.h"

u16 array[2];
volatile int y=0;
volatile int z=0;


void M_Timer_1_input_capture_unit_init(interruption_edge edge){
	clear_bit(DDRD,6);
	set_reg_mask(TCCR1B,1);
	set_bit(TIMSK,5);
	if (edge==rinsing_edge)
	{
		set_bit(TCCR1B,6);
	}
	else if (edge==falling_edge)
	{
		clear_bit(TCCR1B,6);
	}
	sei();
}

u16 M_Timer_1_pulse_width(void){
	u16 x;
	if (y%2==0)
	{
		x=array[1]-array[0];
		return x;
	}
}



ISR(TIMER1_CAPT_vect){	
	array[z]=ICR1;
	y++;
	z^=1;
	toggle_bit(TCCR1B,6);
}