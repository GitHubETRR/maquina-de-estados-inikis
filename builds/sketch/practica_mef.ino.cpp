#include <Arduino.h>
#line 1 "C:\\Users\\imena\\OneDrive - Escuela Tecnica Roberto Rocca\\6\\Materias\\Lenguajes 6\\lenguajes6etrr\\practica_mef\\practica_mef.ino"

#define LED_PIN 1
#define LED_SW 2

#define MIN_TIME 40
#define PRESIONADO 0
void debounceFSM_init();    // debe cargar el estado inicial
void debounceFSM_update();  // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
void buttonPressed();     // debe invertir el estado del LED1
void buttonReleased();    // debe invertir el estado del LED2

typedef enum{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

debounceState_t estado;

int estadoLED1 = 0;
int estadoLED2 = 0;

unsigned long time = 0;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_SW, INPUT);
  
  debounceFSM_init();

  time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  debounceFSM_update();
}

void debounceFSM_init(){
  digitalWrite(LED_PIN, 0);
  estado, estadoLED1, estadoLED2 = 0,0,0;
}

void debounceFSM_update(){
  if (digitalRead(LED_SW) == 1){
    estado = BUTTON_RAISING;
  } else if(digitalRead(LED_SW)==0){
    estado = BUTTON_FALLING;
  }

  switch (estado){
    case BUTTON_UP:
        buttonReleased();
        break;
        
    case BUTTON_FALLING:
        if(millis()-time<=MIN_TIME){
          if (digitalRead(LED_SW) == PRESIONADO)estado = BUTTON_DOWN;  
          else estado = BUTTON_UP;          
          time=millis();
        }
        break;
        
    case BUTTON_DOWN:
        buttonPressed();
        break;
        
    case BUTTON_RAISING:
        
        break;
    
    default:
        debounceFSM_init();
        break;
  }
}

void buttonPressed(){
    estadoLED1 = !estadoLED1;
    digitalWrite(LED_PIN,estadoLED1);
}

void buttonReleased(){
    estadoLED2 = !estadoLED2;
    digitalWrite(LED_PIN,estadoLED2);
}

bool botonPresionado(int boton){
  if (digitalRead(boton) == SUELTO)return (false);
  else return (true);
}
