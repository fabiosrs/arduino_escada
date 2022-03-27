#include <Adafruit_NeoPixel.h>
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 36 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels
 
//=============================
const int led = 12;
const int inc = 13;
const int dec = 11;
unsigned long int tempo_anterior = 0;
unsigned long int tempo_anterior2 = 0;
unsigned long int tempo_anterior3 = 0;
//==============================
int r = 20;
int g = 0;
int b = 0;
int i = 0;
int estado_inc = 0;
int estado_dec = 0;
//===============================
//
//FUNÇÕES
//===============================
void fita_led_inc(){
  i = i + 1;
  if(i >= 5){
            i = 5; 
            }
  pixels.setPixelColor(i, pixels.Color(0, 0, 50));
  Serial.println(i);
                                  pixels.show();  
                                  //delay(10);
  
               }//fita_led
//===============================
void fita_led_dec(){
  i = i - 1;
  if ( i <= 0){
              i = 0;
              }
  pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  Serial.println(i);
                                  pixels.show();  
                                  //delay(10);
  
                    }//fita_led               
//=========================================================================================
void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pinMode(led, OUTPUT);
  pinMode(inc, INPUT_PULLUP);
  pinMode(dec, INPUT_PULLUP);
  Serial.begin(9600);
  pixels.clear();
}//SETUP

void loop() {
  while (true){ 
//pisca led apenas
    if ( millis() - tempo_anterior >= 1000){
      digitalWrite(led, !digitalRead(led));
      tempo_anterior = millis();
                                            }
//===========================================                                         
//BOTÕES
//INCREMENTO /  DECREMENTO
     if ( millis() - tempo_anterior2 >= 500){      
      //digitalWrite(led, !digitalRead(led));
      estado_inc = digitalRead(inc); 
      estado_dec = digitalRead(dec);
      if ( estado_inc == 0) {
                            pixels.setPixelColor(i, pixels.Color(0, 0, 50));
                            pixels.show();
                            fita_led_inc();
                            }
                            
      if ( estado_dec == 0) {
                            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                            pixels.show(); 
                            fita_led_dec();
                            }                            
      tempo_anterior2 = millis();
                                            }
//===========================================  


//===========================================                                              
 //Serial.println("piscando");
 //
              }

             }//LOOP
