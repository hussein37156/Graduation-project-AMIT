/*
 * EEPROM.c
 *
 * Created: 7/14/2023 6:49:50 PM
 * Author : Hussein
 */ 
#include <stdio.h>
#include "CPU_configuration.h"
#include "HAL/DC_motor.h"
#include "HAL/Servo.h"
#include "HAL/ultrasonic.h"
#define max_distance 18  //cm


//hardware_objects and global variables
DC_motor_object left_wheel={A,4,5};
DC_motor_object right_wheel={A,6,7};
ultrasonic_object UTS={D,5};
int servo_feedback;
int ultrasonic_exit_flag;


//prototypes of system functions	
void car_forward(void);
void car_backward(void);
void car_right(void);
void car_left(void);
void car_stop(void);
void searching_algorithm(void);


int main(void){
	
	//DC_motor configurations
	H_DC_motor_init(left_wheel);
	H_DC_motor_init(right_wheel);
	
	//Servo configuration
	H_Servo_init();
	H_Servo_angle(90);
	
	//UTS configuration
	H_ultrasonic_init(UTS);
	
	
	_delay_ms(500);
	while (1)
	{
		if (H_ultrasonic_measure(UTS)>=max_distance)
		{
			car_forward();
		}
		else
		{
			car_stop();
			searching_algorithm();
		}
		_delay_ms(100);
	}
}


void car_forward(void){
	H_DC_motor_forward(left_wheel);
	H_DC_motor_forward(right_wheel);
}

void car_backward(void){
	H_DC_motor_backward(left_wheel);
	H_DC_motor_backward(right_wheel);
}

void car_right(void){
	H_DC_motor_forward(left_wheel);
	H_DC_motor_backward(right_wheel);
}

void car_left(void){
	H_DC_motor_backward(left_wheel);
	H_DC_motor_forward(right_wheel);
}

void car_stop(void){
	H_DC_motor_stop(left_wheel);
	H_DC_motor_stop(right_wheel);
}

void searching_algorithm(void){
	car_stop();
	ultrasonic_exit_flag=0;
	servo_feedback=90;
	_delay_ms(100);		
	for (int servo_angle=0;servo_angle<180;servo_angle++)
	{
		H_Servo_angle(servo_angle);
		if (H_ultrasonic_measure(UTS)>=max_distance )
		{
			servo_feedback=servo_angle;
			ultrasonic_exit_flag=1;
			break;
		}
		_delay_ms(15);
	}
	
	H_Servo_angle(90);
	_delay_ms(100);
	
	if (ultrasonic_exit_flag==1)
	{
		if (servo_feedback<90)
		{
			while (H_ultrasonic_measure(UTS)<max_distance)
			{
				car_right();
				_delay_ms(100);
			}
		}
		else if (servo_feedback>90)
		{
			while (H_ultrasonic_measure(UTS)<max_distance)
			{
				car_left();
				_delay_ms(100);
			}
		}
	}
	else if(ultrasonic_exit_flag==0)
	{
		while (H_ultrasonic_measure(UTS)<max_distance)
		{
			car_backward();
			_delay_ms(100);	
		}
		searching_algorithm();
	}
}