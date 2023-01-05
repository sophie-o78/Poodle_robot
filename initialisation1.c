#include<p18f2520.h>

void Initialisation(void){
    
    //surveillance batterie
    PORTAbits.RA2 = 1; 
   
    //FOSC à 8Mhz
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1; 
    OSCCONbits.IRCF2 = 1;
    INTCON2bits.INTEDG0 = 0; //Front descendant interruption 0
    
    //initialisation interruption telecommande
    INTCONbits.INT0IE = 1; 
    
    //timer 0 initialisation, periode de 5s
    INTCONbits.TMR0IE=1; // active l'IT
    T0CONbits.PSA = 1; // pas de prescaler
    T0CONbits.TMR0ON = 1; //active timer0
    T0CONbits.T08BIT = 0; // timer0 sur 16 bits
    TMR0H = 0x63; //début à 25 452 pour un timer0 de 20ms
    TMR0L = 0x6C;
    
    //timer 2 initialisation (ON à 1)
    T2CON.TMR2ON = 1;
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;      // CLK /4
    PR2 = 499;                  // Reglage periode FPWM = Fosc/(4*(PR2+1)*PRE)
    //Configuration E/S
    TRISCbits.RC1 = 0;          // RC1 en sortie PWMD
    TRISCbits.RC2 = 0;          // RC2 en sortie PWMG
    //info p109
 
      //initialisation des moteurs
    TRISAbits.RA6=0; //sortie DIRD 
    TRISAbits.RA7=0; //sortie DIRG
    TRISAbits.RA4=1; //acquisition moteur droit
    TRISCbits.RC0=1; //acquisition moteur gauche
       
    // Reglage rapport cyclique
    CCP1CONbits.DC1B0 = 0;
    CCP1CONbits.DC1B1 = 0;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 0;
    // Selection Mode PWM
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;  
    T2CONbits.TMR2ON = 1;    //Lance le moteur
    INTCONbits.GIE=1;  // Validation globale des INT
    
    //Desactivation des infrarouges
    PORTBbits.RB1 = 1;
    T0CONbits.T08BIT=0;//timer 16 bits
    
    //initialisation ADC
    TRISBbits.RB5=0;
    ADCON1bits.VCFG=0;//Vref- = Vss & Vref+ =VDD
    ADCON1bits.PCFG=12;
    ADCON2bits.ADCS=6;//Fosc/8 1
    ADCON2bits.ACQT=7;//4 TAD 3
     
  /// initialisation I2C

    SSPCON1bits.SSPEN = 1; //active I2C
    SSPCON1bits.SSPM3 = 1; // mode MAITRE //clock = Fosc/(4*(SSPADD+1))
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;
    SSPADD = 39; //pour avoir 50kHz
    SSPSTATbits.SMP = 1;    //slew rate 100KHz (SMP en mode I2C)
//info ====> page 172

    // Bouton reset
    PORTEbits.RE3 = 0;
    
    //initialisation uart
    TXSTAbits.SYNC=0;//Asynchronous mode
    TXSTAbits.BRGH=1;//High speed
    BAUDCONbits.BRG16=0;//Baud rate 8 bits
    RCSTAbits.SPEN=1;
    TXSTAbits.TXEN=1;//transmit enable
    PIR1bits.TXIF=0;
    PIE1bits.TXIE=0;
    RCSTAbits.CREN=1;//enables receiver
    
    //led test
    PORTBbits.RB5 = 1;
}

void main(void)
{
    Initialisation();
}