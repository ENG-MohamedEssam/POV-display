/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 10/12/2022			 */
/*				SWC  :	TIMERS	 			 */
/*			version  : 	1.0					 */
/*********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "TMR_config.h"
#include "TMR_interface.h"
#include "TMR_private.h"

#include <avr/interrupt.h>


#define F_CPU	8000000L
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

#define _BV(bit) (1 << (bit))


volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;


//#define TCCR0A	TMR_u8_TCCR0
//#define OCR0A	TMR_u8_OCR0
//#define TIMSK0	TMR_u8_TIMSK
//#define TCCR0B	TMR_u8_
//
//#define WGM01
//#define OCIE0A
//#define CS01
//#define CS00

void TMR_voidTMR0Init(void)
{
#if 1
	// Select mode => CTC mode
	CLR_BIT(TMR_u8_TCCR0,6);
	SET_BIT(TMR_u8_TCCR0,3);
	//set the value for 1ms
	TMR_u8_OCR0 = 0xF9;
	// Enable Interrupt CTC
	SET_BIT(TMR_u8_TIMSK,1);
//	sei();
	GIE_voidEnable();
	// Set preload value
//	TMR_u8_TCNT0 = 192;
	// Set prescaler value clk / 64
	CLR_BIT(TMR_u8_TCCR0,2);
	SET_BIT(TMR_u8_TCCR0,1);
	SET_BIT(TMR_u8_TCCR0,0);
#endif
//	TCCR0A|=(1<<WGM01);    //Set the CTC mode
//	 OCR0A=0xF9;            //Set the value for 1ms
//	 TIMSK0|=(1<<OCIE0A);   //Set the interrupt request
//	 sei();                 //Enable interrupt
//	 TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
//	 TCCR0B|=(1<<CS00);
	
}

// prototype of ovf ISR

void __vector_10(void)	__attribute__((signal));
void __vector_10(void)
//ISR(TIMER0_OVF_vect)
{
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}

unsigned long millis()
{
	unsigned long m;
	u8 oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
//	GIE_voidDisable();
	m = timer0_millis;
	SREG = oldSREG;
//	GIE_voidEnable();
	
	return m;
}

unsigned long micros() 
{
	unsigned long m;
	u8 oldSREG = SREG, t;
	cli();
	
//	GIE_voidDisable();
	m = timer0_overflow_count;

	t = TMR_u8_TCNT0;


	if ((GET_BIT(TMR_u8_TIFR,0)) && (t < 255))
		m++;

	SREG = oldSREG;
//	GIE_voidEnable();
	
	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}
