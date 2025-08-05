#include <Arduino.h>


void setup() {
  pinMode(2, OUTPUT);  // Configura o pino 2 como saída
}

void loop() {
  digitalWrite(2, HIGH);  // Liga o LED
  delay(1000);            // Espera 1 segundo
  digitalWrite(2, LOW);   // Desliga o LED
  delay(1000);            // Espera 1 segundo
}
