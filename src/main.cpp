#include <Arduino.h>
#include <stdio.h>

#define BIT_7 7
#define BIT_6 6
#define BIT_5 5
#define BIT_4 4
#define BIT_E 10
#define BIT_RW 11
#define BIT_RS 12
#define CONTRAST 3
#define LED 15
#define ALIMENTATION_LCD 16
///////////////////////////////////////////////////////////////////////////////////////////
//------------------------ PROTOTYPE-----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

void EnvoieTrameMode4Bit(int,int,int,int,int,int);
void AfficheurConfiguration(void);
void Tempo();
void Led(boolean b);
void AllumeLed1S(void);

///////////////////////////////////////////////////////////////////////////////////////////
//------------------------ VARIABLE------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

//char Trame[8];
String Trame = "00001000";

///////////////////////////////////////////////////////////////////////////////////////////
//------------------------ SETUP------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(BIT_7, OUTPUT);
  pinMode(BIT_6, OUTPUT);
  pinMode(BIT_5, OUTPUT);
  pinMode(BIT_4, OUTPUT);
  pinMode(BIT_E, OUTPUT);
  pinMode(BIT_RW, OUTPUT);
  pinMode(BIT_RS, OUTPUT);
  pinMode(CONTRAST, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ALIMENTATION_LCD, OUTPUT);
  //AfficheurConfiguration();
}

///////////////////////////////////////////////////////////////////////////////////////////
//------------------------ LOOP------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  _delay_ms(20);





  //********Configuration du LCD***********
  //---Forcage en mode 8 bit------               RS | RW  |  7  |  6  |  5  |  4  |    
  EnvoieTrameMode4Bit(0,0,0,0,1,1);          //   0 |  0  |  0  |  0  |  1  |  DL |   DL : 1 = 8bit   0 = 4bit                                                                                           
  EnvoieTrameMode4Bit(0,0,0,0,1,1);          //   0 |  0  |  0  |  0  |  1  |  DL |                                           
  EnvoieTrameMode4Bit(0,0,0,0,1,1);          //   0 |  0  |  0  |  0  |  1  |  DL |                                           
  //---Passsage en mode 4 bit-----
  EnvoieTrameMode4Bit(0,0,0,0,1,0);          //   0 |  0  |  0  |  0  |  1  |  DL |   DL : 1 = 8bit   0 = 4bit        
  //---Config des fonctionnalité--
  EnvoieTrameMode4Bit(0,0,0,0,1,0);          //   0 |  0  |  0  |  0  |  1  |  DL |   DL : 1 = 8bit   0 = 4bit                            
  EnvoieTrameMode4Bit(0,0,1,0,0,0); //       //   0 |  0  |  N  |  F  |  *  |  * |    N  : 1 = 2 lignes   0 = 1 ligne      F : 1 = 5*10 pix   0 = 5*8 pix 
  //---Control de l'affichage-----
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  0  |  0  |  0  |  0  |   D  : 1 = afficheur ON  0 = afficheur OFF     C : 1 = Curseur ON   0 = Curseur OFF                                                                
  EnvoieTrameMode4Bit(0,0,1,0,0,0);          //   0 |  0  |  1  |  D  |  C  |  B  |   B  : 1 = curseur clignote   0 = curseur clignote ne clignote pas   
  //---Clear display---------------
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  0  |  0  |  0  |  0  |                                                  
  EnvoieTrameMode4Bit(0,0,0,0,0,1);          //   0 |  0  |  0  |  0  |  0  |  1  |    
  _delay_ms(2);   
  //--- Entry Mode Set------------
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  0  |  0  |  0  |  0  |    I/D : 1 = Move to right   0 = Move to left                                            
  EnvoieTrameMode4Bit(0,0,0,1,1,0);          //   0 |  0  |  0  |  1  | I/D |  S  |    S   : 1 = decale tous l'affichage
  //---Control de l'affichage-----
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  0  |  0  |  0  |  0  |   D  : 1 = afficheur ON  0 = afficheur OFF     C : 1 = Curseur ON   0 = Curseur OFF                                                                
  EnvoieTrameMode4Bit(0,0,1,1,1,1);          //   0 |  0  |  1  |  D  |  C  |  B  |   B  : 1 = curseur clignote   0 = curseur clignote ne clignote pas   
  

    //---Set DDRAM------------
  EnvoieTrameMode4Bit(0,0,1,0,0,0);          //   0 |  0  |  1  |  AC  |  AC  |  AC  |                                           
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  AC |  AC  |  AC  |  AC  |         
  _delay_ms(1000);   


    //---Ecriture du mot H------------
  EnvoieTrameMode4Bit(1,0,1,0,0,0);          //   1 |  0  |  M  |  M  |  M  |  M  |     M = MSB                                             
  EnvoieTrameMode4Bit(1,0,0,1,0,0);          //   1 |  0  |  L  |  L  |  L  |  L  |    L = LSB   
 
  /*                                 


      //---Return home------------
  EnvoieTrameMode4Bit(0,0,0,0,0,0);          //   0 |  0  |  0  |  0  |  0  |  0  |                                                  
  EnvoieTrameMode4Bit(0,0,0,0,1,0);          //   0 |  0  |  0  |  0  |  1  |  0  |  
  _delay_ms(2);
                                                                      

                                                                                             
  //---Ecriture du mot H------------
  EnvoieTrameMode4Bit(1,0,0,1,0,0);          //   1 |  0  |  M  |  M  |  M  |  M  |     M = MSB                                             
  EnvoieTrameMode4Bit(1,0,0,0,1,1);          //   1 |  0  |  L  |  L  |  L  |  L  |    L = LSB           
   
  //---Ecriture du mot E------------
 // EnvoieTrameMode4Bit(1,0,0,1,0,0);          //   1 |  0  |  M  |  M  |  M  |  M  |     M = MSB                                             
 // EnvoieTrameMode4Bit(1,0,0,0,1,1);          //   1 |  0  |  L  |  L  |  L  |  L  |    L = LSB       
  
 
  */
 
 



  //On ce place a la bonne adresse (DDRAM) donc 1er caractere (adresse 0x00)

  //Ecriture du caractere a l'adresse precedement indiqué
 
 
  while (1)
  {
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//------------------------ FONCTION------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

void EnvoieTrameMode4Bit(int RS, int RW, int Bit7, int Bit6, int Bit5, int Bit4)
{
  digitalWrite(BIT_RS, RS);
  Tempo();
  digitalWrite(BIT_RW, RW);
  Tempo();
  digitalWrite(BIT_E, 1);
  Tempo();
  digitalWrite(BIT_7, Bit7);
  Tempo();
  digitalWrite(BIT_6, Bit6);
  Tempo();
  digitalWrite(BIT_5, Bit5);
  Tempo();
  digitalWrite(BIT_4, Bit4);
  Tempo();
  digitalWrite(BIT_E, 0);

  digitalWrite(BIT_RS, RS);
  Tempo();
  digitalWrite(BIT_RW, RW);
  Tempo();
  digitalWrite(BIT_E, 1);
  Tempo();
  digitalWrite(BIT_7, Bit7);
  Tempo();
  digitalWrite(BIT_6, Bit6);
  Tempo();
  digitalWrite(BIT_5, Bit5);
  Tempo();
  digitalWrite(BIT_4, Bit4);
  Tempo();
  digitalWrite(BIT_E, 0);
  Tempo();

}
void EnvoieTrameMode4Bit(void)
{
  ;
}

void AfficheurConfiguration(void)
{
  //Contraset
  analogWrite(CONTRAST, 128);
  Tempo();

  //Force le mode 8 bit pour repacer en 4 bit
}

void Tempo(void)
{
  _delay_us(3000);
}

void Led(boolean b)
{
  if (b == true)
  {
    analogWrite(LED, 250);
  }
  else
  {
    analogWrite(LED, 0);
  }
}
void AllumeLed1S(void)
{
  analogWrite(LED, 255);
  _delay_ms(1000);
  analogWrite(LED, 0);
}