#include <IRremote.h>

const int joystick_x = A0;
const int joystick_y = A1;
const int joystick_button = 2;
const int ir_led = 7;

int x_value = 0;
int y_value = 0;

IRsend irsend;

void setup() {
  // put your setup code here, to run once:
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
  pinMode(joystick_button, INPUT);
  digitalWrite(joystick_button, HIGH);
  pinMode(ir_led, OUTPUT);
  Serial.begin(9600);
}

int convert_value(int data) {
  return (data * 12 / 1024);
}

void send_data(long int data) {
//    irsend.sendNEC(0xFF00FF00, 32);
    irsend.sendNEC(data, 32);
//    Serial.println("Sending '00000011`11111100`11111111`00000000'");
    Serial.println("Sending");
    Serial.println(data);
    delay(40);
}

void loop() {
  // put your main code here, to run repeatedly:

  x_value = convert_value(analogRead(joystick_x));
  y_value = convert_value(analogRead(joystick_y));
   
  if(!digitalRead(joystick_button)) {
    
//    send_data(66849015);
    Serial.print("Sending joystick button\n");
  }

  if(x_value < 5) {
    send_data(
  }
//  for (int i = 0; i < 3; i++) {
//    irsend.sendNEC(0xFF00FF00, 32);
//    Serial.println("Sending '00000011`11111100`11111111`00000000'");
//    delay(40);
//  }
}