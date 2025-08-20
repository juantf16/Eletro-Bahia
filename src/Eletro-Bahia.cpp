#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C LCD (0x27, 16, 2);

const int up = 4;
const int down = 5;
const int selecionar = 15;
const int temp = 34;
const int ebulidor = 19;
const int prep = 23;

int valorup = 0;
int valordown = 0;
int valorselecionar = 0;
int valortemp = 0;
int menu = 0;
int ultimoMenu = 0;
int leiturapot = 0;

float tensao = 0;
float temperatura = 0;

unsigned long inicioPreparo = 0;
bool preparando = false;

void preparoEaquecimento ();



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

  if (menu >3){
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
      menu = 3;
     }
  }

  //mostra no seria os modos
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
       
       preparando = true;
       inicioPreparo = millis();
       
       break;

      case 2:
      LCD.setCursor (0, 0);
      LCD.print("modo manual:  "); 
      break;

      case 3:
       LCD.setCursor (0, 0);
       LCD.print("modo agendado: ");
       break;

      default:
      LCD.setCursor(0, 0);
       LCD.print("modo inexistente");
       break;
    }
    delay (1000);
  }

  if (preparando){
    preparoEaquecimento();
  }

} 


void preparoEaquecimento (){
  unsigned long agora = millis();

  // Termina após 15 minutos
  if (agora - inicioPreparo >= 15UL * 60UL * 1000UL) {
    digitalWrite(ebulidor, LOW);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Cuscuz pronto!   ");
    preparando = false;
    return;
  }

  // Pré-aquecimento e preparo
  if (temperatura < 30) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, HIGH);
    LCD.setCursor(0,0);
    LCD.print("Pre-Aquecendo...  ");
  } else if (temperatura >= 31 && temperatura < 95) {
    digitalWrite(ebulidor, HIGH);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Preparando...     ");
  } else {
    digitalWrite(ebulidor, LOW);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Quente!    ");
  }
}