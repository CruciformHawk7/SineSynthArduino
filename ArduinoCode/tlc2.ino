#include <avr/pgmspace.h>
#include "data.h"
#define outputSelector 30
#define CS 31
#define WR 32

byte signals = &sinc;
int scale = 1, x = 1365,  note = 1;
int index1 = 0;

void setup(){
  for (byte i=22;i<30;i++){
    pinMode(i, OUTPUT);//set digital pins 0-7 as outputs
  } 
  pinMode(outputSelector,OUTPUT);
  pinMode(CS,OUTPUT);
  pinMode(WR,OUTPUT);
  DDRL=0x00;
  Serial.begin(57600);
  attachInterrupt(digitalPinToInterrupt(20), occured, HIGH);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 361;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);
  sei();
  digitalWrite(CS,LOW);
}

ISR(TIMER1_COMPA_vect){
  PORTC |= B00000100;
  PORTA = pgm_read_byte_near(signals + index1);
  if (note==0){ PORTA = pgm_read_byte_near(sinc + index1); x = 1365;}
  if (note==1){ PORTA = pgm_read_byte_near(sincs + index1); x = 1259;}
  if (note==2){ PORTA = pgm_read_byte_near(sind + index1); x = 1191;}
  if (note==3){ PORTA = pgm_read_byte_near(sinds + index1); x = 1130;}
  if (note==4){ PORTA = pgm_read_byte_near(sine + index1); x = 1075;}
  if (note==5){ PORTA = pgm_read_byte_near(sif + index1); x = 1001;}
  if (note==6){ PORTA = pgm_read_byte_near(sinfs + index1); x = 958; }
  if (note==7){ PORTA = pgm_read_byte_near(sing + index1); x = 899; }
  if (note==8){ PORTA = pgm_read_byte_near(sings + index1); x = 847; }
  if (note==9){ PORTA = pgm_read_byte_near(sina + index1); x = 800; }
  if (note==10){ PORTA = pgm_read_byte_near(sinas + index1); x = 759; }
  if (note==11){ PORTA = pgm_read_byte_near(sinb + index1); x = 710; }
  PORTC &= B11111110;
  //digitalWrite(outputSelector,LOW);//select DACA
  index1 +=scale;
  if (index1>=x){
    index1=0;
  }
  PORTC &= B11111011;
}


void occured() {
  byte p = PINL;
  Serial.println(p, BIN);
  note = p & 0x0F;
  Serial.println(note);
  scale = p&0xF0;
  Serial.println(scale);
}

void loop() {}
