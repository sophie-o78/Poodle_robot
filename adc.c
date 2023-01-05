#include <p18f2520.h>
#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

volatile unsigned int ubat=0;
void HighISR(void);
#pragma code HighVector=0x08
void IntHighVector(void)
{
    //command asm
    _asm goto HighISR _endasm
}
#pragma code

#pragma interrupt HighISR
void HighISR(void)
{
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
    TMR0H=0x67;
    TMR0L=0x69;
    //si le flag d'interruption est ON
    ADCON0bits.GO=1;
    }
   if(PIR1bits.ADIF==1)
   {
      PIR1bits.ADIF=0;
      ubat=256*ADRESH+ADRESL;
    }
}

void main(void) {
   OSCCONbits.IRCF0 = 0 ;
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;
   TRISBbits.RB5=0;
   TRISAbits.RA2=1;
   ADCON1bits.VCFG=0;
   ADCON1bits.PCFG=12;
   ADCON2bits.ADCS=4;
   ADCON2bits.ACQT=3;
   ADCON0bits.CHS=2;
   ADCON2bits.ADFM=0;
   ADCON0bits.ADON=1;

   PIR1bits.ADIF=0;
   PIE1bits.ADIE=1;

   INTCON2bits.INTEDG0 = 0;
   INTCON2bits.INTEDG1 = 0;
   //On valide l'interruption

   //peripheral and core interrupt
   INTCONbits.PEIE = 1;
   INTCONbits.GIE = 1;

   ADCON0bits.GO=1;


   T0CONbits.TMR0ON=1;
   T0CONbits.T08BIT=0;
   T0CONbits.T0CS=0;
   T0CONbits.PSA=0;
   T0CONbits.T0PS=6;
   INTCONbits.TMR0IE=1;
   TMR0H=0x67;
   TMR0L=0x69;

   while(1){
       if(ubat<38272){
           PORTBbits.RB5=1;
       }
       else{
           PORTBbits.RB5=0;
       }
       }
   }


