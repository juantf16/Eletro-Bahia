#include <Arduino.h>

const int up = 4;
const int dow = 5;
const int selecionar = 15;
const int temp = 34;
const int ebulidor = 19;
const int prep = 23;

int valorup = 0;
int valordow = 0;
int valorselect = 0;
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

  if (valorup == 1){
      delay(500);
 }

 if (valorup == 1){
  menu++;

  if (menu >4){
    menu = 1;
  }
 }


 Serial.println(menu);
 delay(1000);

}