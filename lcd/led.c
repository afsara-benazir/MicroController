#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h" 

/*ADC Function Declarations*/
void adc_init(void);
float read_adc_channel();


/*ADC Function Definitions*/
void adc_init(void)
{                    
  //ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2);
	ADCSRA=(1<<ADEN)|(1<<ADPS2);
 	SFIOR=0x00;
   	ADMUX=0b01000000;
}
float read_adc_channel()
{
	  int adc_value;
	  unsigned char temp;
	 
	 
	  _delay_ms(10);
	 
	ADCSRA=ADCSRA|(1<<ADSC);
	while(ADCSRA & (1<<ADSC));
        temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return adc_value;
}

 char result[100];
 char voltageSTR[100] = "";


int main(void)
{
  DDRD = 0xFF;
  DDRC = 0xFF;
  int i;

  float adc_output;
  

  Lcd4_Init();
  Lcd4_Clear();

 adc_init();
  while(1)
  {
    
    Lcd4_Set_Cursor(1,1);
    Lcd4_Write_String("ADC VALUE : ");
    
    /*Reading adc output of channel 0*/
    adc_output=read_adc_channel();
    adc_output = (adc_output*5)/1024;
   

    Lcd4_Set_Cursor(2,2);
    char charVal[10] ;                

	//4 is mininum width, 3 is precision; float value is copied onto buff
	dtostrf(adc_output, 4, 3, charVal);
    
     Lcd4_Write_String(charVal);
    _delay_ms(10);
  }
}
