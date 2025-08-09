#include <Arduino.h>

const int up = 4;
const int dow = 5;
const int selecionar = 15;
const int temp = 34;
const int ebulidor = 19;
const int prep = 23;

int valorup = 0;
int valordow = 0;
int valorselecionar = 0;
int valortemp = 0;
int menu = 0;


void setup() {
  Serial.begin (115200);
  pinMode(up, INPUT);  
  pinMode(dow, INPUT);
  pinMode (selecionar, INPUT);
  pinMode (temp, INPUT);
  pinMode (ebulidor, OUTPUT);
  pinMode (prep, OUTPUT);

}

void loop() {

  valorup = digitalRead (up);
  valordow = digitalRead (dow);
  valorselecionar = digitalRead (selecionar);

  if (valorup == 1){
      delay(500);
 }

 if (valorup == 1){
  menu++;

  if (menu >4){
    menu = 1;
  }
 }

  if (valordow == 1){
    delay (500);
  }

  if (valordow == 1){
    menu --;
     if (menu < 1){
      menu = 4;
     }
  }

  if (valorselecionar == 1){
    delay (500);
  }

}