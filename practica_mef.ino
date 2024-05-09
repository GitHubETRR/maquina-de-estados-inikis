#define LED_PIN 1
#define SW_PIN 2

#define SW_PRESS 3
#define SW_RELEASE 4

#define MIN_TIME 40
#define PRESIONADO 0

void debounceFSM_init();    // debe cargar el estado inicial
void debounceFSM_update();  // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
void buttonPressed();     // debe invertir el estado del LED1
void buttonReleased();    // debe invertir el estado del LED2
bool botonPresionado(int boton);

typedef enum{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

debounceState_t estado;

unsigned long time = 0;

void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT);
  debounceFSM_init();
  time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  debounceFSM_update();
}

void debounceFSM_init(){
  digitalWrite(LED_PIN, 0);
  if(botonPresionado(SW_PIN))estado=BUTTON_DOWN;
  else estado=BUTTON_UP;
 
}

void debounceFSM_update(){
 

  switch (estado){
    case BUTTON_UP:
        if (botonPresionado(SW_PIN))estado=BUTTON_FALLING;
        break;
        
    case BUTTON_FALLING:
        if(millis()-time>=MIN_TIME){
          if (botonPresionado(SW_PIN)){
            buttonPressed();
            estado = BUTTON_DOWN;  
          }
          else estado = BUTTON_UP;          
          time=millis();
        }
        break;
        
    case BUTTON_DOWN:
        if (!botonPresionado(SW_PIN))estado=BUTTON_RAISING;
        break;
        
    case BUTTON_RAISING:
        if(millis()-time>=MIN_TIME){
          if (!botonPresionado(SW_PIN)){
            buttonReleased();
            estado = BUTTON_UP;  
          }
          else estado = BUTTON_DOWN;          
          time=millis();
        }
        break;
    
    default:
        debounceFSM_init();
        break;
  }
}

void buttonPressed(){
    digitalWrite(SW_PRESS,!digitalRead(SW_PRESS));
}

void buttonReleased(){
    digitalWrite(SW_RELEASE,!digitalRead(SW_RELEASE));
}

bool botonPresionado(int boton){
  if (digitalRead(boton) == PRESIONADO)return (true);
  return (false);
}