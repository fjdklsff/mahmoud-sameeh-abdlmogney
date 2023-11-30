#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ICU.h"
#include <avr/io.h>
void ICU_init()
{
	unsigned int a,b,c;
	TCCR1A = 0;
	TCNT1=0;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0x41;
	while ((TIFR&(1<<ICF1)) == 0);
	a = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0x01;
	while ((TIFR&(1<<ICF1)) == 0);
	b = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0x41;
	while ((TIFR&(1<<ICF1)) == 0);
	c = ICR1;
	TIFR = (1<<ICF1);
	
	TCCR1B = 0;
}