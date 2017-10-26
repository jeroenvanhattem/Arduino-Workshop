#include <IRremote.h>
#include <IRremoteInt.h>

const int motorA1 = 2;
const int motorA2 = 3;
const int motorB1 = 4;
const int motorB2 = 5;
const int RECV_PIN = 7;
const int rgb_red = 11;
const int rgb_green = 12;
const int rgb_blue = 13;

int led_toggle;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  
  pinMode(motorA1, OUTPUT); 
  pinMode(motorB1, OUTPUT); 
  pinMode(motorA2, OUTPUT); 
  pinMode(motorB2, OUTPUT); 
    
    pinMode(rgb_red, OUTPUT); 
    pinMode(rgb_green, OUTPUT); 
    pinMode(rgb_blue, OUTPUT); 
  
  pinMode(RECV_PIN, INPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void switch_colors() {
  // Zo komt de led_toggle niet boven de 6 uit, bij 7 gaat het terug naar 0
  led_toggle = (led_toggle + 1) % 7;
  switch(led_toggle){
    case 0:
      digitalWrite(rgb_red, HIGH); 
      digitalWrite(rgb_green, HIGH); 
      digitalWrite(rgb_blue, HIGH); 
      break;
    case 1:
      digitalWrite(rgb_red, LOW); 
      digitalWrite(rgb_green, HIGH); 
      digitalWrite(rgb_blue, HIGH); 
      break;
    case 2:
      digitalWrite(rgb_red, HIGH); 
      digitalWrite(rgb_green, LOW); 
      digitalWrite(rgb_blue, HIGH); 
      break;
    case 3:
      digitalWrite(rgb_red, HIGH); 
      digitalWrite(rgb_green, HIGH); 
      digitalWrite(rgb_blue, LOW); 
      break;
    case 4:
      digitalWrite(rgb_red, LOW); 
      digitalWrite(rgb_green, LOW); 
      digitalWrite(rgb_blue, HIGH); 
      break;
    case 5:
      digitalWrite(rgb_red, LOW); 
      digitalWrite(rgb_green, HIGH); 
      digitalWrite(rgb_blue, LOW); 
      break;
    case 6:
      digitalWrite(rgb_red, HIGH); 
      digitalWrite(rgb_green, LOW); 
      digitalWrite(rgb_blue, LOW); 
      break;
  }
}

void drive(int command) {
  // Vooruit
  if(results.value == 4278255360){
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB2, LOW);
    Serial.println("Forward");
  }
  // Achteruit
  else if(results.value == 30){
    digitalWrite(motorA1, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB2, HIGH);
  }
  // Stop
  else if(results.value == 0x00){
    digitalWrite(motorA1, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB2, LOW);
  }
  // Links
  if(results.value == 144){
    digitalWrite(motorA1, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB2, LOW);
  }
  // Rechts
  else if(results.value == 2192){
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB2, HIGH);
  }
  // Verander kleuren
  else if(results.value == 66849015) {
    switch_colors();
    Serial.println("Switching colors!");
  }
}

int receive_infrared() {
  // Ontvangen van IR signaal
  if (irrecv.decode(&results)) {
    Serial.println("VALUE");
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
  }

  return results.value;
}

void loop() {
  //Even wachten, zodat je niet 5 IR-codes binnen 1 seconde krijgt.
  delay(500);
  
//  Serial.println(results.value, HEX);
  // Hier roepen we de drive() functie aan, we geven de waarde mee, dit maakt alles een stuk overzichtelijker.
  drive(receive_infrared());
  
  results.value = 0;
   
}

