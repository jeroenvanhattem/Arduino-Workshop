void setup() {    //  (1)
  Serial.begin(9600); //  (2)
}

void loop() {     //  (3)
  Serial.println("Hello world");  //  (4)
  delay(10 * 1000); //  (5)
}

