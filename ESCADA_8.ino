/*
                                                             É NECESSÁRIO RETIRAR O RESISTOR DO LED NA PCI - D13

              _______
             |  USB  |
          --------------
      D13 |            | D12
          |            | D11
          |            | D10
          |            | D9
          |            | D8
          |            | D7
          |            | D6
          |            | D5
          |            | D4
          |            | D3
          |            | D2
       5V |            | GND
          |            | RST
      GND |            | RX
          |            | TX
          --------------

FUNCIONAMENTO DO CIRCUITO


            
*/




#include <Adafruit_NeoPixel.h>
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 500 // Popular NeoPixel ring size
// LIMITADO EM 8 METROS DE FITA
#include <EEPROM.h>
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels
//=============================
#define buzzer 10 
#define led_cor 5
#define led_status 12
#define led_cena 7
#define led_degrau 8
#define sens_baixo 9
#define sens_alto 3
//                                            
#define inc 13
#define dec 11
#define enter 4
//=============================
unsigned long int tempo_anterior = 0;
unsigned long int tempo_anterior2 = 0;
unsigned long int tempo_anterior3 = 0;
//==============================
int r = 255;
int g = 255;
int b = 255;
//int i = 0;
unsigned long int i = 0;
int x = 0;
//int soma = 0;
unsigned long int soma = 0;
int estado_inc = 0;
int estado_dec = 0;
int estado_prog = 0;
int estado_enter = 0;
int estado_sens_alto = 0;
int estado_sens_baixo = 0;
int var_tempo = 0;
int var_cor = 0;
int var_cena = 0;
int var_degrau = 30;// inicia o valor do comprimento da escada de 50 em 50 cm.
int total = 0;
int total_2 = 0;
int pisca = 20;
//===============================
//
//FUNÇÕES
//===============================
void fita_led_inc(){
  i = i + 1;
  if(i >= 5){
            i = 5; 
            }
  pixels.setPixelColor(i, pixels.Color(0,g, 0));
  Serial.println("EEPROM");
  EEPROM.write(0, i);
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
  //pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  pixels.setPixelColor(i, pixels.Color(r, 0, 0));
  Serial.println("EEPROM");
  EEPROM.write(0, i);
  Serial.println(i);
                                  pixels.show();  
                                  //delay(10);
  
                    }//fita_led  

//===============================
void tempo_100(){
  delay(100);
}

void tempo_500(){
  delay(500);
}
void tempo_50(){
  delay(50);
}
void tempo_200(){
  delay(200);
}
void tempo_10(){
  delay(10);
}
//==============================================================================================
void tempo_espera(){
  delay(30000);
}
//==============================================================================================
//================================= FUNÇÕES ===============================================
void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  //=========
  pinMode(led_status, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_cor, OUTPUT);
  pinMode(led_cena, OUTPUT);
  pinMode(led_degrau, OUTPUT);
  //
  pinMode(inc, INPUT_PULLUP);
  pinMode(dec, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  pinMode(sens_alto,INPUT_PULLUP);
  pinMode(sens_baixo,INPUT_PULLUP);
  //========
  Serial.begin(9600);
  //=======
  pixels.clear();
  //
  digitalWrite(led_cor,LOW);
  digitalWrite(led_status,LOW);
  digitalWrite(led_cena,LOW);
  digitalWrite(led_degrau,LOW);
  digitalWrite(buzzer,LOW);
}//SETUP

void loop() {
  //MODO PROGRAMAÇÃO
  pixels.clear();
            delay(2500);
            estado_prog = digitalRead(enter); // pino 4            
            //delay(2500);
            if (estado_prog == 0){
                    digitalWrite(buzzer,HIGH);
                    tempo_50();
                    digitalWrite(buzzer,LOW);
                    tempo_50();
                    digitalWrite(buzzer,HIGH);
                    tempo_100();
                    digitalWrite(buzzer,LOW);
                    
                    Serial.println("INICIALIZA A PROGRAMACAO");  
                    delay(2500); 
                    for (soma = 0;soma<=pisca; soma++){
                                       digitalWrite(led_status, !digitalRead(led_status));
                                       tempo_100();
                                                  }
                    //digitalWrite(led_status, !digitalRead(led_status)); // O LED STATUS É LED ACESO CONSTANTE DE PROG
                    // LED ESTAVA EM ZERO FOI PRA UM, ACESO
                    // INDICANDO MODO PROGRAMAÇÃO ATIVO
                    //AO FIM DA PROGRAMAÇÃO O LED APAGA
                    // E LED STATUS VOLTA A PISCAR
                    //=======================
                    while(true){
                    Serial.println("CONFIGURA COR");  
                                estado_enter = digitalRead(enter);
                                estado_inc = digitalRead(inc); 
                                estado_dec = digitalRead(dec);
                                digitalWrite(led_cor,HIGH);// led aceso, escolho o tempo
//=====================================================
                            if ( estado_inc == 0) {
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             tempo_500();
                             var_cor = var_cor + 1;
                             if ( var_cor >= 6){
                              //
digitalWrite(buzzer,HIGH);
tempo_500();
tempo_500();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);


                              //
                                                var_cor = 6;
                                                //break;
                                               }
                                                 }//inc
//=====================================================                                  
                            if ( estado_dec == 0) {
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             tempo_500();
                             var_cor = var_cor - 1;
                             if ( var_cor <= 0 ){
//
digitalWrite(buzzer,HIGH);
tempo_500();
tempo_500();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
//
                                                var_cor = 0;
                                                //break;
                                               }                                              
                            
                                                  }//dec
//=====================================================
                            if ( estado_enter == 0) {// grava na memoria e sai da cor
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                              delay(500);            // posição 02
                              for (soma = 0; soma <= pisca; soma ++){
                              pixels.setPixelColor(soma, pixels.Color(0,0,0));
                              pixels.show();
                              delay(50);
                                                                 }
                              Serial.println("COR"); 
                              Serial.println(var_cor);                                  
                              break;
                                                    }//enter

// ROTINAS CASE PARA MOSTRAR A COR

/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(var_cor){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
  break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
  break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
  break; 

  case 4:
  r = 255;
  g = 0;
  b = 255;
  break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
  break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break; 

              }// FIM DO SWITCH CASE

// FIM DA ROTINA DE CORES
                                               
// COLOCO  AS CORES AMOSTRA NA ESCADA OU CORRIMÃO
                            Serial.println(var_cor); 
                            for (soma = 0; soma <= pisca; soma ++){
                              pixels.setPixelColor(soma, pixels.Color(r,g,b));
                              pixels.show();
                              delay(50);
                                                               }
                            EEPROM.write(2,var_cor);// posição 02 na EEPROM
                            tempo_500();
// FIM DA AMOSTRAGEM                                                                                 
                               }//while

//--------------------------------cena----------------------------------------------------------                               
// INICIALIZO UM NOVO WILE PARA GRAVAR A CENA
//Serial.println(var_cena);
digitalWrite(led_cor,LOW);
digitalWrite(led_cena,LOW);
digitalWrite(led_degrau,LOW);
Serial.println("CONFIGURA CENA");
tempo_500();
for( soma = 0; soma <= pisca; soma++){
                                   digitalWrite(led_cena, !digitalRead(led_cena));
                                   tempo_100();
                                  }
                                  digitalWrite(led_cena,LOW);
                                  digitalWrite(led_cor,HIGH);

//#################################################################################################
//                       AQUI ENTRO COM A CENA 1 PARA MOSTRAR AO USUÁRIO
//################################################################################################# 
// CENA 0 
// PARA USUARIO CENA 1
  for(int i=0; i<30; i++) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                  pixels.show();  
                                  tempo_50();
  pixels.clear();        
                         }                                
// MENOR
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//#################################################################################################
                                  while(true){// inicio programação cena
                                              estado_enter = digitalRead(enter);
                                              estado_inc = digitalRead(inc); 
                                              estado_dec = digitalRead(dec);
                                              //digitalWrite(led_cor,HIGH);// led aceso, escolho o tempo          
//=====================================================
                            if ( estado_inc == 0) {
//################################################################################################
// APAGA OS LEDS ANTERIORES
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//################################################################################################
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             tempo_50();
                             var_cena = var_cena + 1;
//################################################################################################
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//################################################################################################                             
                             if ( var_cena == 1){
                                                digitalWrite(led_cor,LOW);
                                                digitalWrite(led_cena,HIGH);
                                                digitalWrite(led_degrau,LOW);
                                                tempo_50();
//#################################################################################################
//CENA 1
// PARA USUARIO CENA 2
for(int i=0; i<=30; i++) { // For each pixel...
                                  pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                  pixels.show();  
                                  tempo_50();

soma = soma + 1;
if (soma == 30/6) {
  soma = 0;
  pixels.clear(); 
  
                  }
        
                         }
                         tempo_100();// PROB
                                
// MENOR

for(int i=30; i>-1; i--) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(255,255, 255));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_50(); // Pause before next pass through loop
                                
                         }
//################################################################################################                                                
                                                }// CENA 1

                             
                             if ( var_cena >= 2){
                                                var_cena = 2;
                                                digitalWrite(led_cor,LOW);
                                                digitalWrite(led_cena,LOW);
                                                digitalWrite(led_degrau,HIGH);
                                                tempo_50();

//
digitalWrite(buzzer,HIGH);
tempo_500();
tempo_500();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
//
//################################################################################################
// APAGA OS LEDS ANTERIORES
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//################################################################################################
delay(100);
//###############################################################################################
// AQUI IREI MOSTRAR A CENA 2 PARA USUARIO
// AQUI CENA 1
  for(int i=0; i<((30/2) + 1); i++) { // For each pixel...9
    //((total/2) + 1)
                                  pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                  pixels.show();  
                                  delay(50);
                                 }
                                
// MENOR

for(int i=30; i>(30/2); i--) {  //16 - 8
  //i = total
  //i > (total/2)
                                pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                delay(50); // Pause before next pass through loop
                                }
//###############################################################################################
                                                }// FIM CENA 2
                                                 }//inc
//=====================================================                                  
                            if ( estado_dec == 0) {

//################################################################################################
// APAGA OS LEDS ANTERIORES
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//################################################################################################                              
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             tempo_50();
                             var_cena = var_cena - 1;
                             if ( var_cena <= 0 ){
                                                var_cena = 0;
                                                digitalWrite(led_cor,HIGH);
                                                digitalWrite(led_cena,LOW);
                                                digitalWrite(led_degrau,LOW);
//
digitalWrite(buzzer,HIGH);
tempo_500();
tempo_500();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
//
                                                tempo_50(); //PROB
//################################################################################################# 
// CENA 0 
// PARA USUARIO CENA 1
  for(int i=0; i<30; i++) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                  pixels.show();  
                                  tempo_50();
  pixels.clear();        
                         }                                
// MENOR
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//#################################################################################################
                                                
                                                 }// FIM CENA 0 / PARA USUARIO CENA 1
                          if ( var_cena == 1){
                                                digitalWrite(led_cor,LOW);
                                                digitalWrite(led_cena,HIGH);
                                                digitalWrite(led_degrau,LOW);
                                                tempo_50();
//#################################################################################################
//CENA 1
// PARA USUARIO CENA 2
for(int i=0; i<=30; i++) { // For each pixel...
                                  pixels.setPixelColor(i, pixels.Color(255, 255, 255));
                                  pixels.show();  
                                  tempo_50();

soma = soma + 1;
if (soma == 30/6) {
  soma = 0;
  pixels.clear(); 
  
                         }
        
                         }
                         tempo_100();
                                
// MENOR

for(int i=30; i>-1; i--) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(255,255, 255));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_50(); // Pause before next pass through loop
                                
                         }
//################################################################################################                                                
                                             }//CENA 1                             
                                                                                                         
                                                 }//dec
//=====================================================
                            if ( estado_enter == 0) {// grava na memoria e sai da cor
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                              delay(100);   

//################################################################################################
// APAGA OS LEDS ANTERIORES
for(int i=30; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_50(); // Pause before next pass through loop
                          }
//################################################################################################                                       
                              // posição 03 cena
                                                     EEPROM.write(3,var_cena);// posição 02 na EEPROM
                                                     Serial.println("VALOR DA CENA");
                                                     Serial.println(var_cena); 
                                                     digitalWrite(led_cor,LOW);
                                                     digitalWrite(led_cena,LOW);
                                                     digitalWrite(led_degrau,LOW);
                                                     tempo_500();
                                                     break;
                                                    }
//===================================================                                        
                                                  }//while                                             
//-----------------------------cena-------------------------------------------------------------
// FIM DA GRAVAÇÃO DA CENA
///*********************************************************************************************
// GRAVA DEGRAUS
// 50 cm de fita possui 30 leds, sendo assim 1 metro de fita 60 leds
//A CADA INCREMENTO SOMAREMOS 30 LED's A SOMA, POIS NÃO IREI TRABALHAR
// COM NUMEROS PICADOS EX: 71 LEDS...COMO DIVIDIR POR 2 E TER UM VALOR INTEIRO
//
Serial.println("CONFIGURA DEGRAUS");
digitalWrite(led_cor,LOW);
digitalWrite(led_cena,LOW);
digitalWrite(led_degrau,LOW);
digitalWrite(led_status,LOW);
tempo_500();
//********
for( soma = 0; soma <= pisca; soma++){
                                   digitalWrite(led_degrau, !digitalRead(led_degrau));
                                   tempo_100();
                                  }
                                  //digitalWrite(led_degrau,LOW);
                                  while(true){// inicio programação cena
                                              estado_enter = digitalRead(enter);
                                              estado_inc = digitalRead(inc); 
                                              estado_dec = digitalRead(dec);
                                              digitalWrite(led_degrau,HIGH);// led aceso, escolho o tempo  

//=====================================================
                            if ( estado_inc == 0) {
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             var_degrau = var_degrau + 30;//1
                             Serial.println(var_degrau);
                             pixels.clear();
                             tempo_500();
//
// MOSTRO A QUANTIDADE DE LEDS OU COMPRIMENTO DA ESCADA OU CORRIMÃO

for (soma = 0; soma <= var_degrau; soma ++){
                              pixels.setPixelColor(soma, pixels.Color(50,50,50));
                              pixels.show();
                              Serial.println(soma);
                              delay(50);
                                           }
//
                                                 }//inc
//=====================================================                                  
                            if ( estado_dec == 0) {
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
                             var_degrau = var_degrau - 30;//1
                             pixels.clear();
                             Serial.println("DECREMENTO");
                             Serial.println(var_degrau);
                             tempo_200();
//


if (var_degrau <= 30){
                    var_degrau = 30;//1
digitalWrite(buzzer,HIGH);
tempo_500();
tempo_500();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);
tempo_100();
digitalWrite(buzzer,HIGH);
tempo_100();
digitalWrite(buzzer,LOW);  
                    }


// MOSTRO A QUANTIDADE DE LEDS OU COMPRIMENTO DA ESCADA OU CORRIMÃO

for (soma = 0; soma <= var_degrau; soma ++){
  Serial.println("DECREMENTA");
  Serial.println(var_degrau);
                              pixels.setPixelColor(soma, pixels.Color(50,50,50));
                              pixels.show();
                              delay(50);
                                           }
//
                                                                                                    
                                                 }//dec
//=====================================================
                            if ( estado_enter == 0) {// grava na memoria e sai da cor
digitalWrite(buzzer,HIGH);
tempo_500();
digitalWrite(buzzer,LOW);
tempo_50();
digitalWrite(buzzer,HIGH);
tempo_50();
digitalWrite(buzzer,LOW);
tempo_50();
digitalWrite(buzzer,HIGH);
tempo_50();
digitalWrite(buzzer,LOW);
tempo_50();
digitalWrite(buzzer,HIGH);
tempo_50();
digitalWrite(buzzer,LOW);
                              // posição 03 cena
                              total = var_degrau; // total = 30 * var_degrau;
                                                     EEPROM.write(1,total);// posição 01 na EEPROM
                                                     Serial.println("VALOR DO DEGRAU");
                                                     Serial.println(total); 
                                                     digitalWrite(led_cor,LOW);
                                                     digitalWrite(led_cena,LOW);
                                                     digitalWrite(led_degrau,LOW);
                                                     pixels.clear();

// APAGAR OS LEDS QUE FORAM LIGADOS

for (soma = 0; soma <= var_degrau; soma ++){
                              pixels.setPixelColor(soma, pixels.Color(0,0,0));
                              pixels.show();
                              delay(20);
                                           }

// APAGAR OS LEDS QUE FORA LIGADOS

                                                     
                                                     tempo_10();
                                                     break;
                                                    }

                                  }
//===================================================   
//*******
//FIM DEGRAUS
//**********************************************************************************************
                     
                                }// fim da programação======================================================================================================================================
//FIM MODO PROGRAMAÇÃO

  while (true){ 
////#############################################################################################  
// WHILE PROGRAMA CONTÍNUO            RODA CONSTANTE  
////############################################################################################# 
//pisca led apenas
    if ( millis() - tempo_anterior >= 1000){
                                            digitalWrite(led_status, !digitalRead(led_status));
                                            tempo_anterior = millis();
                                           }

                                   
//==============================================================================================  
//         AQUI ENTRO COM AS CORES, CENAS E COMPRIMENTO DO DEGRAU

estado_sens_alto = digitalRead(sens_alto);
estado_sens_baixo = digitalRead(sens_baixo); 
Serial.println(estado_sens_baixo);
if ( estado_sens_alto == 0) {// acionamento de baixo para cima//---------3

//
int valor_e1 = EEPROM.read(1);// comprimento degrau
int valor_e2 = EEPROM.read(2);//cor
int valor_e3 = EEPROM.read(3);//cena
//
// ESCOLHER A CENA - POIS AQUI DENTRO ESCOLHO COR E QTIDADE DE DEGRAU
//------------------------------------------
switch(valor_e3){// cena 0-1-2
  
case 0:// cena 8
//cena 8
//int valor_e2 = EEPROM.read(2);//cor
//inicio cor
// ROTINAS CASE PARA MOSTRAR A COR

/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;

              }// FIM DO SWITCH CASE 

//fim cor
  for(int i=0; i<valor_e1; i++) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_50();
  pixels.clear();        
                         }                                
// MENOR
for(int i=valor_e1; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(r, g,b));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_100(); // Pause before next pass through loop
                          }

tempo_espera(); // ESPERA ANTES DE APAGAR TODO O CORRIMÃO
 
//pixels.clear();
for(int i=valor_e1; i>-1; i--) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_200(); // Pause before next pass through loop
                               }

//cena 8 
  
break;
//----------------------------------------------------------------------------------------------
case 1:
//CENA 9
// ROTINAS CASE PARA MOSTRAR A COR
/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;
              }// FIM DO SWITCH CASE
// IMPRIMI AS CORES NO CORRIMAO
for(int i=0; i<=valor_e1; i++) { // For each pixel...
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_50();

soma = soma + 1;
if (soma == valor_e1/6) {
  soma = 0;
  pixels.clear(); 
  
                         }
        
                         }
                         tempo_500();
                                
// MENOR

for(int i=valor_e1; i>-1; i--) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(r,g, b));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_200(); // Pause before next pass through loop
                                
                         }

 // apagar um por um

tempo_espera(); // TEMPO DE ESPERA COM LED ACESOS 
//pixels.clear(); 


for(int i=valor_e1; i>-1; i--) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(0,0, 0));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_200(); // Pause before next pass through loop
                                
                         }

             
//
//CENA 9
break;
//---------------------------------------------------------------------------------------------
case 2:
//CENA 7
// ROTINAS CASE PARA MOSTRAR A COR
/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;
              }// FIM DO SWITCH CASE
// IMPRIMI AS CORES NO CORRIMAO
  for(int i=0; i<((valor_e1/2) + 1); i++) { // For each pixel...9
    //((total/2) + 1)
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  delay(50);
                                 }
                                
// MENOR

for(int i=valor_e1; i>(valor_e1/2); i--) {  //16 - 8
  //i = total
  //i > (total/2)
                                pixels.setPixelColor(i, pixels.Color(r, g, b));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                delay(50); // Pause before next pass through loop
                                }

 // apagar um por um
tempo_espera(); // tempo de espera


for(int i=0; i<=valor_e1; i++) { //16
  //i = total   
                                pixels.setPixelColor(i, pixels.Color(0,0, 0));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                delay(200); // Pause before next pass through loop
                             }
//
break;

               }// FIM SWITCH CASE
               
//------------------------------------------                            
                            }// sens_alto

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

//
if ( estado_sens_baixo == 0 ){// acionamento do alto para baixo //---------9

//
int valor_e1 = EEPROM.read(1);// comprimento degrau
int valor_e2 = EEPROM.read(2);//cor
int valor_e3 = EEPROM.read(3);//cena
//
///=============================================================================================
switch(valor_e3){// cena 0-1-2
  
case 0:// cena 8
//cena 8
//int valor_e2 = EEPROM.read(2);//cor
//inicio cor
// ROTINAS CASE PARA MOSTRAR A COR

/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;

              }// FIM DO SWITCH CASE 
Serial.println("CENA 8");
//fim cor
  for(int i=valor_e1; i>=-1; i--) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_50();
  pixels.clear();        
                         }                                
// MENOR
for(int i=0; i<valor_e1; i++) {  
                          pixels.setPixelColor(i, pixels.Color(r, g,b));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_100(); // Pause before next pass through loop
                              }

tempo_espera(); // ESPERA ANTES DE APAGAR TODO O CORRIMÃO
 
//pixels.clear();
for(int i=0; i<=valor_e1; i++) {  
                          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                          pixels.show();   // Send the updated pixel colors to the hardware.
                          tempo_200(); // Pause before next pass through loop
                               }

//cena 8 
  
break;
//----------------------------------------------------------------------------------------------
case 1:
//CENA 9
// ROTINAS CASE PARA MOSTRAR A COR
/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;
              }// FIM DO SWITCH CASE
              Serial.println("CENA 9");
// IMPRIMI AS CORES NO CORRIMAO
for(int i=valor_e1; i>=-1; i--) { // For each pixel...
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_50();

soma = soma + 1;
if (soma == valor_e1/6) {
  soma = 0;
  pixels.clear(); 
  
                         }
        
                         }
                         tempo_500();
                                
// MENOR

for(int i= 0; i<=valor_e1; i++) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(r,g, b));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_200(); // Pause before next pass through loop
                                
                         }

 // apagar um por um

tempo_espera(); // TEMPO DE ESPERA COM LED ACESOS 
//pixels.clear(); 


for(int i=0; i<=valor_e1; i++) {  
  //int ran = random(16);   
                                pixels.setPixelColor(i, pixels.Color(0,0, 0));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_200(); // Pause before next pass through loop
                                
                         }

             
//
//CENA 9
break;
//---------------------------------------------------------------------------------------------
case 2:
//CENA 7
// ROTINAS CASE PARA MOSTRAR A COR
/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
 break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
 break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
 break;

  case 4:
  r = 255;
  g = 0;
  b = 255;
break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break;
              }// FIM DO SWITCH CASE
// IMPRIMI AS CORES NO CORRIMAO
Serial.println("CENA 7");
  for(int i=0; i<((valor_e1/2) + 1); i++) { // For each pixel...9
    //((total/2) + 1)
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_50();
                                 }
                                
// MENOR

for(int i=valor_e1; i>(valor_e1/2); i--) {  //16 - 8
  //i = total
  //i > (total/2)
                                pixels.setPixelColor(i, pixels.Color(r, g, b));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_50(); // Pause before next pass through loop
                                }

 // apagar um por um
tempo_espera(); // tempo de espera


for(int i=0; i<=valor_e1; i++) { //16
  //i = total   
                                pixels.setPixelColor(i, pixels.Color(0,0, 0));
                                pixels.show();   // Send the updated pixel colors to the hardware.
                                tempo_200(); // Pause before next pass through loop
                             }
//
break;

               }// FIM SWITCH CASE
               

  
///=============================================================================================
break;
}// sens_baixo
//===============================================================================================
//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
////#############################################################################################
//                                  FICA ACESO CONSTANTE 
////#############################################################################################
         
            estado_prog = digitalRead(enter); // pino 4            
            
            if (estado_prog == 0){// ACESO CONSTANTE
                    digitalWrite(buzzer,HIGH);
                    tempo_50();
                    digitalWrite(buzzer,LOW);
                    tempo_50();
                    digitalWrite(buzzer,HIGH);
                    tempo_50();
                    digitalWrite(buzzer,LOW);
                    tempo_50();
                    digitalWrite(led_status,LOW); // LATEREI ESTE ITEM 270322

for (soma = 0;soma<=pisca; soma++){
                                       
digitalWrite(led_cor, !digitalRead(led_cor));
digitalWrite(led_cena, !digitalRead(led_cena));
digitalWrite(led_degrau, !digitalRead(led_degrau));
tempo_100();
                               }
                    
int valor_e1 = EEPROM.read(1);
int valor_e2 = EEPROM.read(2);//cor
//cor
// ROTINAS CASE PARA MOSTRAR A COR

/*
 *r = 255;
 *g = 255;
 *b = 255;
 *0 = r,0,0
 *1 = g,0,0
 *2 = b,0,0
 *3 = r,g,0
 *4 = r,0,b
 *5 = 0,g,b
 *6 = r,g,b

*/
switch(valor_e2){
  
  case 0:
  r = 255;
  g = 0;
  b = 0;
  break;

  case 1:
  r = 0;
  g = 255;
  b = 0;
  break; 

  case 2:
  r = 0;
  g = 0;
  b = 255;
  break; 

  case 3:
  r = 255;
  g = 255;
  b = 0;
  break; 

  case 4:
  r = 255;
  g = 0;
  b = 255;
  break; 

  case 5:
  r = 0;
  g = 255;
  b = 255;
  break; 

  case 6:
  r = 255;
  g = 255;
  b = 255;
  break; 

              }// FIM DO SWITCH CASE

//cor
                    for(int i=0; i<valor_e1; i++) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(r, g, b));
                                  pixels.show();  
                                  tempo_10();         
                                  }
                                  delay(5000);
                    while(true){
                       estado_prog = digitalRead(enter); // pino 4            
            
            if (estado_prog == 0){// ACESO CONSTANTE
                    digitalWrite(buzzer,HIGH);
                    tempo_50();
                    digitalWrite(buzzer,LOW);
                    tempo_50();
                    digitalWrite(buzzer,HIGH);
                    tempo_50();
                    digitalWrite(buzzer,LOW);
                    tempo_50();

for (soma = 0;soma<=valor_e1; soma++){                                       
digitalWrite(led_cor, !digitalRead(led_cor));
digitalWrite(led_cena, !digitalRead(led_cena));
digitalWrite(led_degrau, !digitalRead(led_degrau));
tempo_100();
                               }

                    
int valor_e1 = EEPROM.read(1);
                    for(int i=0; i<valor_e1; i++) { // For each pixel...                                  
                                  pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                                  pixels.show();  
                                  tempo_10();         
                                                  }
                                  break;
                               }
                               }
            }

////#############################################################################################
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000  

}//WHILE PROGRAMA CONTÍNUO

}//LOOP
