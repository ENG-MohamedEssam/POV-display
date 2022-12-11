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



void TMR_voidTMR0Init(void)
{
	// Select mode => CTC mode
	CLR_BIT(TMR_u8_TCCR0,6);
	SET_BIT(TMR_u8_TCCR0,3);
	// Enable OVF Interrupt
	SET_BIT(TMR_u8_TIMSK,0);
	// Set preload value
	//TMR_u8_TCNT0 = 192;
	// Set prescaler value clk / 64
	CLR_BIT(TMR_u8_TCCR0,2);
	SET_BIT(TMR_u8_TCCR0,1);
	SET_BIT(TMR_u8_TCCR0,0);
	
}

// prototype of ovf ISR

//void __vector_11(void)	__attribute__((signal));
//void __vector_11(void)
ISR(TIMER0_OVF_vect)
{
	/*
	static u16 Local_u16CounterOVF = 0;
	static u32 Local_u32Counter = 1;
	Local_u16CounterOVF++;
	if(Local_u16CounterOVF >= 255)
	{
		//update preload value
		//TMR_u8_TCNT0 = 192;
		// Clear ovf counter
		Local_u16CounterOVF = 0;
		Local_u32Counter++;
	}
	*/
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
	//uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	//cli();
	GIE_voidDisable();
	m = timer0_millis;
	//SREG = oldSREG;
	GIE_voidEnable();
	
	return m;
}

unsigned long micros() 
{
	unsigned long m;
	//uint8_t oldSREG = SREG, t;
	u8 t;
	//cli();
	
	GIE_voidDisable();
	m = timer0_overflow_count;

	t = TMR_u8_TCNT0;


	if ((GET_BIT(TMR_u8_TIFR,0)) && (t < 255))
		m++;

	//SREG = oldSREG;
	GIE_voidEnable();
	
	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}
