#include <LiquidCrystal.h>

//Datasheet 74HC595 : https://www.hwlibre.com/wp-content/uploads/2019/06/registro-74hc595.jpg
//Display 7 Segmentos: http://www.circuitstoday.com/wp-content/uploads/2016/03/7_segment_display_pin_outs.png

const int latchPin = 8;  // Pin 12 74HC595(Latch)-OUTPUT
const int dataPin  = 9;  //Pin 14 74HC595(Data)-OUTPUT
const int clockPin = 10; // Pin 11 74HC595(Clock)-OUTPUT

const int botonENTER = 1; //
const int botonUP = 2;  //
const int botonDWN = 3; // Botón hacia abajo
const int rs = 11;
const int en = 12;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const byte numeros[10] = {
                0b11111100,
                0b01100000,
                0b11011010,
                0b11110010,
                0b01100110,
                0b10110110,
                0b10111110,
                0b11100000,
                0b11111110,
                0b11100110,}; // Vector de bytes con números en orden[0-9]
int i = 0,val= 0;
int j= 0,k= 0;
bool borrar= false;

//============================================================================================================================================================//
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(botonUP,INPUT);
  pinMode(botonDWN,INPUT);
  pinMode(botonENTER,INPUT);
  
  
  lcd.begin(16,2);
  lcd.noAutoscroll();
    
}

//============================================================================================================================================================//
void loop() {
 lcd.setCursor(0,0);
 if (digitalRead(botonENTER )== LOW){
   if(borrar){
     lcd.clear();
     borrar = false;
   }
    lcd.setCursor(j,k);
    lcd.print(i);
    delay(300);
    j++;
    if(j>15){
      j=0;
      k++;
      if(k>1){
        k=0;
        borrar=true;
      }
    } 
  }
  
  if( digitalRead(botonUP) ==  LOW){
    i ++;
    delay(500);
    if(i>9) i=0;
  }

  if( digitalRead(botonDWN) ==  LOW){
    i--;
    delay(500);
    if(i<0) i=9;
  }
  EscribirDigito(numeros[i]);
}

void EscribirDigito(byte numer){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numer);
  digitalWrite(latchPin, HIGH); 
}