#include <IRremote.h>

const int joystick_x = A0;
const int joystick_y = A1;
const int joystick_button = 2;
const int ir_led = 7;

int x_value = 0;
int y_value = 0;

IRsend irsend;

void setup() {
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
    irsend.sendNEC(data, 32);
    Serial.println("Sending");
    Serial.println(data);
    delay(40);
}

void loop() {

  x_value = convert_value(analogRead(joystick_x));
  y_value = convert_value(analogRead(joystick_y));
   
  if(!digitalRead(joystick_button)) {
    send_data(66849015);
    Serial.print("Sending joystick button\n");
  }

  if(x_value > 6) {
    // Forward
    // 00000011 11111100 11111100 00000011
    send_data(66911235);
    Serial.print("Sending Forward\n");
  }
  else if(x_value < 4) {
    // Backwards
    // 00000011 11111100 00000011 11111100
    send_data(66847740);
    Serial.print("Sending Backwards\n");
  }
  
  if(y_value < 4) {
    // Left
    // 00000011 11111100 00110000 11001111
    send_data(66859215);
    Serial.print("Sending Left\n");
  }
  else if(y_value > 6) {
    // Right
    // 00000011 11111100 00001100 11110011
    send_data(66850035);
    Serial.print("Sending Right\n");
  }
 
  if ((x_value > 4 && x_value < 6) && (y_value > 4 && y_value < 6)) {
    // Don't move
    // 00000011 11111100 00000000 11111111
    send_data(66846975);
    Serial.print("Sending Don't move\n");
  }
//  for (int i = 0; i < 3; i++) {
//    irsend.sendNEC(0xFF00FF00, 32);
//    Serial.println("Sending '00000011`11111100`11111111`00000000'");
//    delay(40);
//  }
}
