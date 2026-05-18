#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int leds[] = {A0, A1, A2, A3};
int botones[] = {2, 5, 3, 4};
int secuencia[100];
int nivel = 1;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Simon Says!");
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT_PULLUP);
  }
  pinMode(13, OUTPUT);
  randomSeed(analogRead(0));
  agregarSecuencia();
}
void parpadear(){
  for (int i = 0; i < 4; i++){
    digitalWrite(leds[i],HIGH);
    delay(500);
    digitalWrite(leds[i],LOW);
    delay(100);
  }
}
void sonidoCorrecto() {
  tone(13, 1000, 200); 
  delay(200);
}

void sonidoPerder() {
  tone(13, 200, 1000); 
  delay(1000);
}
void perder() {
  lcd.clear();
  lcd.print("Perdiste!");
  sonidoPerder();
  for (int j = 0; j < 5; j++) {  
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH); 
    }
    delay(300);
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);  
    }
    delay(300);

  }
  nivel = 1;
   agregarSecuencia();
}
void mostrarSecuencia(){
  for (int i = 0; i < nivel; i++) {
    digitalWrite(leds[secuencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[secuencia[i]], LOW);
    delay(500);
  }
}
void agregarSecuencia() {
  secuencia[nivel - 1] = random(4);
  mostrarSecuencia();
}


void loop() {
  for (int i = 0; i < nivel; i++) {
    bool esperando = true;
    while (esperando) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(botones[j]) == LOW) {
          digitalWrite(leds[j], HIGH);
          delay(300);
          digitalWrite(leds[j], LOW);
          if (j != secuencia[i]) {
            perder();
            return;
          }
          esperando = false;
          sonidoCorrecto();
          delay(200);
        }
      }
    }
  }
  nivel++;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nivel:");
  lcd.print(nivel);
  delay(800);
  agregarSecuencia();
}

