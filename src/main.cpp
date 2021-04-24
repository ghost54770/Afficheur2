#include <Arduino.h>
#include <stdio.h>
#define BIT_7 7
#define BIT_6 6
#define BIT_5 5
#define BIT_4 4
#define BIT_E 10
#define BIT_RW 11
#define BIT_RS 12
#define CONTRAST 14

/////////////////////////////////////////////////////////////////////////////////////////// 
//------------------------ PROTOTYPE-----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

void EnvoieTrameMode4Bit(char message[]);
void AfficheurConfiguration(void);

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
  analogWrite(CONTRAST, 50);

  AfficheurConfiguration();
}

/////////////////////////////////////////////////////////////////////////////////////////// 
//------------------------ LOOP------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  AfficheurConfiguration();
  //

  pinMode(BIT_RS, LOW);
  pinMode(BIT_RW, LOW);
  pinMode(BIT_7, LOW);
  pinMode(BIT_6, LOW);
  pinMode(BIT_5, HIGH);
  pinMode(BIT_4, HIGH);
  _delay_ms(50);
  pinMode(BIT_E, LOW);

 

/////////////////////////////////////////////////////////////////////////////////////////// 
//------------------------ FONCTION------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////

void EnvoieTrameMode4Bit(String trame)
{
  char LSB[4];
  char MSB[4];

  for (int i = trame.length(); i > 0 ; i++)
  {
    LSB[i-1] = trame[i-1];
  }

  for (unsigned int i = 1; i < trame.length(); i++)
  {
    printf("%d", trame[i]);
  }

  /*  for(unsigned int b = 0; b < trame.size()){
    
  }*/

  while (1)
  {
  }
}

void EnvoieTrame(int valeur)
{
}

void AfficheurConfiguration(void)
{
  //Contraset
  analogWrite(CONTRAST,50);

  //Mode 4 bit
  pinMode(BIT_RS, LOW);
  pinMode(BIT_RW, LOW);
  pinMode(BIT_7, LOW);
  pinMode(BIT_6, LOW);
  pinMode(BIT_5, HIGH);
  pinMode(BIT_4, HIGH);
  _delay_ms(50);
  pinMode(BIT_E, LOW);
}