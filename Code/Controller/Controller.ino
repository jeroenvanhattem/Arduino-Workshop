#include <IRremote.h>

const int joystick_x = 0;
const int joystick_y = 1;
const int joystick_button = 2;
const int ir_led = 7;

int x_value = 0;
int y_value = 0;

IRsend irsend;

void setup() {
  // put your setup code here, to run once:
//  pinMode(joystick_x, INPUT);
//  pinMode(joystick_y, INPUT);
  pinMode(joystick_button, INPUT);
  Serial.begin(9600);
}
int convert_value(int data) {
  return (data * 9 / 1024) + 48;
 }

void loop() {
  // put your main code here, to run repeatedly:

//  x_value = digitalRead(joystick_x);
//  y_value = digitalRead(joystick_y);
  
//  Serial.println("X: ");
//  Serial.println(x_value);
//  Serial.println("Y: "); 
//  Serial.println(y_value);
//  Serial.println("Button: ");
//  Serial.println(digitalRead(joystick_button));
  
  for (int i = 0; i < 3; i++) {
    irsend.sendSony(0xFF, ir_led);
    Serial.println("Sending '0xFF'");
    delay(40);
  }

//  delay(500);
  
  for (int i = 0; i < 3; i++) {
    irsend.sendSony(0x00, ir_led);
    Serial.println("Sending '0x00'");
    delay(40);
  }

//  delay(1000);
}
