#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <OneWire.h>


LiquidCrystal_I2C LCD (0x27, 16, 2);

const int PINO_ONEWIRE = 4;
OneWire oneWire(PINO_ONEWIRE);
DallasTemperature sensor(&oneWire); 
DeviceAddress endereco_temp;

//declaração de variaveis
const int up = 14; // evitar conflito com OneWire (GPIO4). Ajuste conforme seu circuito
const int down = 5;
const int selecionar = 18;
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
//unsigned long tempoAtual = 10 * 60UL * 1000UL;
bool preparo1 = false;
bool preparo2 = false;

void modo1 ();
void modo2 ();
void tocarBuzzer ();

void setup() {
  
  Wire.begin(21, 22); 
  sensor.begin();
  LCD.init();
  LCD.setBacklight(HIGH);
  LCD.clear();
  LCD.setCursor(0,0); 
  LCD.print("Cuscuszeira");

  pinMode(up, INPUT);  
  pinMode(down, INPUT);
  pinMode (selecionar, INPUT);
  pinMode (ebulidor, OUTPUT);
  pinMode (prep, OUTPUT);
  pinMode (buzzer, OUTPUT);

}

void loop() {

  // ler botões (INPUT_PULLUP: LOW = pressionado)
  valorup = digitalRead(up);
  valordown = digitalRead(down);
  valorselecionar = digitalRead(selecionar);

  // leitura do sensor: solicitar temperatura e em seguida obter o valor
  if (sensor.getAddress(endereco_temp, 0)) {
    sensor.requestTemperatures();
    temperatura = sensor.getTempC(endereco_temp);
  } else {
    temperatura = NAN; // sensor não disponível
  }


  // mepeando bot up
  if (valorup == 1){
      delay(200);
 }

 if (valorup == 1){
  menu++;

  if (menu >2){
    menu = 1;
  }
 }

 // mapeando bot down
  if (valordown == 1){
    delay (200);
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
    delay (200);
  }

  //config dos modos da cuscuszeira

  if (valorselecionar == 1){
    switch (menu){
      case 1:
       LCD.setCursor (0, 0);
       LCD.print ("modo 1 ");
       
       preparo1 = true;
       inicioPreparo = millis();
       
       break;

      case 2:
      LCD.setCursor (0, 0);
      LCD.print("modo 2:  "); 

      preparo2 = true;
      inicioPreparo = millis();
      break;

      default:
       LCD.setCursor(0, 0);
       LCD.print("modo inexistente");
       break;
    }
    delay (1000);
  }

  if (preparo1 == true){
    modo1();
  }

  if (preparo2 == true ){
    modo2();
  }
} 



void modo1 (){
  unsigned long agora = millis();

  // Termina após 5 minutos
  if (agora - inicioPreparo >= 5UL * 60UL * 1000UL) {
    digitalWrite(ebulidor, LOW);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Cuscuz pronto!   ");
    tocarBuzzer();
    preparo1 = false;
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

void modo2(){
  unsigned long agora = millis();
  //unsigned long tempoAtual = 10UL* 60UL * 1000UL; 

  /*if (valorup == HIGH){
    meuTempo ++;
  }

  if (valordown == HIGH){
    meuTempo --;
  }*/



  if (agora - inicioPreparo >= 10UL * 60UL * 1000UL) {
    digitalWrite(ebulidor, LOW);
    digitalWrite(prep, LOW);
    LCD.setCursor(0,0);
    LCD.print("Cuscuz pronto!   ");
    tocarBuzzer();
    preparo2 = false;
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

  

  /*LCD.setCursor (0, 1);
  LCD.print ("tempo: ");
  LCD.print(meuTempo);
  LCD.print (" min  ");
*/


}

void tocarBuzzer() {
  for (int i = 0; i < 5; i++) {  // Toca 5 vezes
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}