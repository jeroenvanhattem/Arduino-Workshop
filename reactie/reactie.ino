const int firstButton = 7;
const int secondButton = 6;
const int led = 5;
int timer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(firstButton, INPUT_PULLUP);
  pinMode(secondButton, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  Serial.println("Wacht tot de LED brandt en druk dan snel op de knop!");
  
}

void loop() {
  delay(random(400, 2000));
  digitalWrite(led, HIGH);
  Serial.println("GO");

  while((digitalRead(firstButton) == HIGH) && (digitalRead(secondButton) == HIGH)) {
    delay(1);
    timer++;
  }
  
  if(digitalRead(firstButton) == LOW ) {
    Serial.println("De winnaar is gebruiker 1: ");
    Serial.println(timer);
    Serial.println("ms");
    
    digitalWrite(led, LOW);
    timer = 0;
    while(1);
  }

  else if(digitalRead(secondButton) == LOW) {
    Serial.println("De winnaar is gebruiker 2: ");
    Serial.println(timer);
    Serial.println("ms");
    
    digitalWrite(led, LOW);
    timer = 0;
    while(1);
  }
}
