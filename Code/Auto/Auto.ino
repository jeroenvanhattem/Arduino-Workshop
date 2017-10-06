#include <IRremote.h>

const int motorA = 2;
const int motorB = 3;
const int RECV_PIN = 7;
const int rgb_red = 11;
const int rgb_green = 12;
const int rgb_blue = 13;

int led_toggle;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  Serial.begin(9600);
  
  pinMode(motorA, OUTPUT); 
  pinMode(motorB, OUTPUT); 
  pinMode(rgb_red, OUTPUT); 
  pinMode(rgb_green, OUTPUT); 
  pinMode(rgb_blue, OUTPUT); 
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

void loop()
{
  //Even wachten, zodat je niet 5 IR-codes binnen 1 seconde krijgt.
//  delay(500);
  
//  switch_colors();
  
  // Ontvangen van IR signaal
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

  Serial.println("Value: ");
  Serial.println(results.value);
  
  // Groepen
  //Toets Prog Up -> Vooruit
  if(results.value == 0xFF){
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, HIGH);
  }
  //Toets Prog Down -> Stop
  else if(results.value == 0x00){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, LOW);
  }
  //Toets Vol Up -> Links
  if(results.value == 144){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
  }
  //Toets Vol Down -> Rechts
  else if(results.value == 2192){
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
  }
  
  // Toets 0 -> LCD legen
  else if(results.value == 2320){
  
  }  
 
 results.value = 0;
 
       
}

