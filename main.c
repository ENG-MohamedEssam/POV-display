#include <avr/io.h>
#include "STD_TYPES.h"
#include "TMR_interface.h"
#include "GIE_interface.h"
#include "BIT_MATH.h"
#include "EXTI_interface.h"


/* Electronoobs POV dsiplay (Persistance of vision)
 * Subscribe: http://www.youtube.com/c/ELECTRONOOBS
 * Tutorial: http://www.electronoobs.com/eng_arduino_tut21.php */




//Variables for real time count
unsigned long Real_time_millis = 0;
unsigned long Previous_real_time_millis = 0;
float SEC=0;
float MIN= 45;
float HOUR = 2;
float dots_marker = 0; //Variable used for the 4 red dots

//POV clock cariables
unsigned long currentMillis, elapsed_loop_counter, previousMillis;
unsigned long counter_1, current_count;

//Interruption varaibles to count rotation speed
//We create 4 variables to store the previous value of the input signal (if LOW or HIGH)
u8 last_IN_state = 0;               //Here we store the previous state on digital pin 13
float one_rot_time=0;             //Here we store the full rotation time
float time_per_deg=0;             //Here we store the time it takes to make one degree rotation

void ISR(void);
//void Test(void);

int main(void) {

//  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan
//  PCMSK0 |= (1 << PCINT5);  //Enable pin state interruption on pin D13
	GIE_voidEnable();
	EXTI_voidInt0init();
	EXTI_u8Int0SetCallBack(&ISR);
	TMR_voidTMR0Init();

  //Output pins register configuration
  /* D2 = Blue LED
   * D3 = Red 1 LED
   * D4 = Red 2 LED
   * D5 = Green 1 LED
   * D6 = Green 2 LED
   * D7 = Green 3 LED
   * D8 = Green 4 LED
   * D9 = Green 5 LED
   * D10 = Green 6 LED
   * D11 = Green 7 LED
   * D12 = Green 8 LED
   */

//  DDRD |= 0b11111100;      //2 to 7 as output
//  DDRB |= 0b00011111;      //8 to 12 as output
  DDRB |= 0b11111111;
  DDRA |= 0b00000111;

//  DDRB &= 0b11011111;      //13 input
  DDRD &= 0x00;

//  PORTD &= 0b00000011;     //2 to 7 LOW
//  PORTB &= 0b11100000;     //8 to 12 LOW
  PORTB &= 0b00000000;
  PORTA &= 0b00000000;
  PORTA |= 0b00000100;
//  PORTA |= 0xFF;
//  while(1);

  while(1)
  {
	  //Here we calculate seconds, minutes and hours
	   Real_time_millis = millis();

	   if(Real_time_millis - Previous_real_time_millis >= 1000){
	     Previous_real_time_millis += 1000;

	     SEC=SEC+1;
	     if(SEC > 59)
	     {
	       SEC=0;
	       MIN=MIN+1;
	     }

	     if(MIN > 59)
	     {
	       MIN = 0;
	       HOUR = HOUR+1;
	     }
	   }//End of real time count

	   //Here is our loop counter. elapsed_loop_counter will reset each loop and count the loop time
	   //When we reach the amount of time desired we turn ond or off the LEDs
	   currentMillis = micros();
	   elapsed_loop_counter = currentMillis - previousMillis;

//	   if(previousMillis != 0)
//	   {
//		   PORTB |= 0xFF;
//		   PORTA |= 0xFF;
//	   }

	  //Print the 4 red dots
	   if(elapsed_loop_counter >=  time_per_deg*(dots_marker) &&  elapsed_loop_counter <  time_per_deg*(dots_marker+3)    )
	   {
	     //PORTD |= 0b00011000; //3,4 HIGH
		   PORTA |= 0b00000011;
	   }

	   if(elapsed_loop_counter >= time_per_deg*(dots_marker+3))
	   {
//	     PORTD &= 0b11100111;               //3, 4 LOW, the two red LEDs
		   PORTA &= 0b00000100;
	     dots_marker = dots_marker + 90;
	     if(dots_marker >= 360)
	     {
	       dots_marker = 0;
	     }
	   }





	   //Print the second line
	   if(elapsed_loop_counter >=  time_per_deg*(SEC*6) &&  elapsed_loop_counter <  time_per_deg*((SEC*6)+2)    )
	   {
//	     PORTB |= 0b00011111; //8, 9, 10, 11 and 12 as HIGH
//	     PORTD |= 0b11100000; //2 (blue), 5, 6 and 7 as HIGH
		  PORTB |= 0xFF;
		  PORTA |= 0b00000100;
	   }

	   if(elapsed_loop_counter >= time_per_deg*((SEC*6)+2))
	   {
//	     PORTB &= 0b11100000;
//	     PORTD &= 0b00011111;
		  PORTB &= 0x00;
		  PORTA &= 0b11111100;
	   }




	    //Print the minute line
	   if(elapsed_loop_counter >=  time_per_deg*(MIN*6) &&  elapsed_loop_counter <  time_per_deg*((MIN*6)+1)    )
	   {
//	     PORTB |= 0b00011111; //8, 9, 10, 11 and 12 as HIGH
//	     PORTD |= 0b11000000; //2 (blue), 5, 6 and 7 as HIGH
		  PORTB |= 0xEF;
		  PORTA |= 0b00000100;
	   }

	   if(elapsed_loop_counter >= time_per_deg*((MIN*6)+1))
	   {
//	     PORTB &= 0b11110000;
//	     PORTD &= 0b00111111;
			  PORTB &= 0x00;
			  PORTA &= 0b11111100;
	   }



	    //Print the hour line
	   if(elapsed_loop_counter >=  time_per_deg*(HOUR*30) &&  elapsed_loop_counter <  time_per_deg*(   (HOUR*30)  +1)   )
	   {
//	     PORTB |= 0b00011111; //8, 9, 10, 11 and 12 as HIGH
//	     PORTD |= 0b00000000; //2 (blue), 5, 6 and 7 as HIGH
		  PORTB |= 0xFF;
		  PORTA |= 0b00000100;
	   }

	   if(elapsed_loop_counter >= time_per_deg*(  (HOUR*30)   +1))
	   {
//	     PORTB &= 0b11100000;
//	     PORTD &= 0b11111111;
		  PORTB &= 0x00;
		  PORTB |= 0xF0;

		  PORTA &= 0b11111100;
	   }

	 }

  return 0;
}


//void Test(void)
//{
//	PORTB |= 0xff;
//	PORTA |= 0x00;
//}

void ISR(void){
//First we take the current count value in micro seconds using the micros() function

  current_count = micros();
  ///////////////////////////////////////
  if(PIND & 0b00000100){                              //We make an AND with the pin state register, We verify if pin 13 is HIGH???
    if(last_IN_state == 0){                          //If the last state was 0, then we have a state change...
      last_IN_state = 1;                             //Store the current state into the last state for the next loop
      counter_1 = current_count;                     //Set counter_1 to current value.
    }
  }
  else if(last_IN_state == 1){                       //If pin 13 is LOW and the last state was HIGH then we have a state change
    last_IN_state = 0;                               //Store the current state into the last state for the next loop
    one_rot_time = current_count - counter_1;        //We make the time difference. one_rot_time 1 is current_count - counter_1.
    time_per_deg = one_rot_time/360.0;
    previousMillis = micros();

   }
}

