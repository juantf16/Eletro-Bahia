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
  digitalWrite (ebulidor, HIGH);
  delay (100);
  digitalWrite (ebulidor, LOW);
  delay (100);
  digitalWrite (prep, HIGH);
  delay (100);
  digitalWrite (prep, LOW);
  delay(100);

}