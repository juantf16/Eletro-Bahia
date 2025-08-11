#include <Arduino.h>

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


void setup() {
  Serial.begin (115200);
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


  // mepeando bot up
  if (valorup == 1){
      delay(500);
 }

 if (valorup == 1){
  menu++;

  if (menu >4){
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
      menu = 4;
     }
  }

  //mostra no seria os modos
  if (menu != ultimoMenu) {
    Serial.print("modo: ");
    Serial.println(menu);
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
       Serial.print ("modo selecionado: ");
       Serial.println (menu);
       break;

      case 2:
       Serial.print ("modo selecionado: ");
       Serial.println (menu);
       break;

      case 3:
       Serial.print ("modo selecionado: ");
       Serial.println (menu);
       break;

      case 4: 
       Serial.print ("modo manual selecionado: ");
       Serial.println (menu);
       break;

      default:
       Serial.print("modo inexistente");
       break;
    }
    delay (1000);
  }

} 