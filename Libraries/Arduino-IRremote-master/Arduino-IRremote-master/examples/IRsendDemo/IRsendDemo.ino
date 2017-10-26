/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

void setup() {
  Serial.begin(9600);
}

void loop() {
	for (int i = 0; i < 3; i++) {
		irsend.sendNEC(0xFF00FF00, 32);
		delay(40);
    Serial.println("Sending signal");
	}
	delay(100);
}
