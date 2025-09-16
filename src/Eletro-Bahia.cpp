#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

LiquidCrystal_I2C LCD (0x27, 16, 2);

//declaração de variaveis
const int up = 4;
const int down = 5;
const int selecionar = 18;
const int temp = 34;
const int ebulidor = 12;
const int prep = 32;
const int buzzer = 23;

int valorup = 0;
int valordown = 0;
int valorselecionar = 0;
int valortemp = 0;
int menu = 0;
int ultimoMenu = 0;
int leiturapot = 0;
int meuTempo = 1;
int etapa = 0;

float tensao = 0;
float temperatura = 0;

unsigned long inicioPreparo = 0;
unsigned long tempoAtual = meuTempo * 60UL * 1000UL;
bool preparoAuto = false;
bool preparoManual = false;

void modoAutomatico ();
void modoManual ();
void tocarBuzzer ();


void setup() {
  
  Wire.begin(21, 22); 
  LCD.init();
  LCD.setBacklight(HIGH);
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Cuscuszeira");

  pinMode(up, INPUT);  
  pinMode(down, INPUT);
  pinMode (selecionar, INPUT);
  pinMode (temp, INPUT);
  pinMode (ebulidor, OUTPUT);
  pinMode (prep, OUTPUT);
  pinMode (buzzer, OUTPUT);

}

void loop() {

  valorup = digitalRead (up);
  valordown = digitalRead (down);
  valorselecionar = digitalRead (selecionar);
  leiturapot = analogRead (temp);


   // convertendo analog => para volts
  tensao = (leiturapot / 4095.0) * 3.3;

  // simulando: 0V => 0°C e 3.3V => 100°c
  temperatura = (tensao / 3.3) *100.0;

  // mepeando bot up
  if (valorup == 1){
      delay(500);
 }

 if (valorup == 1){
  menu++;

  if (menu >2){
    menu = 1;
  }
 }

 // mapeando bot down
  if (valordown == 1){
    delay (500);
  }

  if (valordown == 1){
    menu --;
     if (menu < 1){
      menu = 2;
     }
  }

  //mostra os modos
  if (menu != ultimoMenu) {

    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Modo:");
    LCD.setCursor(6,0);
    LCD.print(menu);
    ultimoMenu = menu;
  }

  //mapeando bot selecionar 
  if (valorselecionar == 1){
    delay (500);
  }

  //config dos modos da cuscuszeira

  if (valorselecionar == 1){
    switch (menu){
      case 1:
       LCD.setCursor (0, 0);
       LCD.print ("modo automatico ");
       
       preparoAuto = true;
       inicioPreparo = millis();
       
       break;

      case 2:
      LCD.setCursor (0, 0);
      LCD.print("modo manual:  "); 

      inicioPreparo = millis();
      preparoManual = true;
      break;

      default:
      LCD.setCursor(0, 0);
       LCD.print("modo inexistente");
       break;
    }
    delay (1000);
  }

  if (preparoAuto == true){
    modoAutomatico();
  }

  if (preparoManual == true ){
    modoManual();
  }
} 



void modoAutomatico (){
  unsigned long agora = millis();

  // Termina após 15 minutos
  if (agora - inicioPreparo >= 15UL * 60UL * 1000UL) {
    digitalWrite(ebulidor, LOW);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Cuscuz pronto!   ");
    tocarBuzzer();
    preparoAuto = false;
    return;
  }

  // Pré-aquecimento e preparo
  if (temperatura < 30) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, HIGH);
    LCD.setCursor(0,0);
    LCD.print("Pre-Aquecendo...  ");
  } else if (temperatura >= 31 && temperatura < 100) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Preparando...     ");
  }
}

void modoManual (){
  unsigned long agora = millis();
  unsigned long tempoAtual = meuTempo * 60UL * 1000UL; 

  if (valorup == HIGH){
    meuTempo ++;
  }

  if (valordown == HIGH){
    meuTempo --;
  }



  if (agora - inicioPreparo >= tempoAtual && preparoManual == true){
     digitalWrite (ebulidor, LOW);
     digitalWrite (prep, LOW);
     LCD.clear ();
     LCD.setCursor (0, 0);
     LCD.print ("Cuzcuz pronto"); 
     tocarBuzzer();
     preparoManual = false;
     return;
  }
  

  // Pré-aquecimento e preparo
  if (temperatura < 30) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, HIGH);
    LCD.setCursor(0,0);
    LCD.print("Pre-Aquecendo...  ");
  } else if (temperatura >= 31 && temperatura < 100) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Preparando...     ");
  } 

  

  LCD.setCursor (0, 1);
  LCD.print ("tempo: ");
  LCD.print(meuTempo);
  LCD.print (" min  ");



}

void tocarBuzzer() {
  for (int i = 0; i < 5; i++) {  // Toca 5 vezes
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}