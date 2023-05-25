#include <dht.h>

dht DHT;
#define DHT11_PIN 7

const int ledPin = 13; 
const int ldrPin = A0;  
int temp;
int SensorPin1 = 9;
int SensorPin2 = 10;
int count = 0;
int p;

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);  
  pinMode(ldrPin, INPUT);  
  pinMode(2, OUTPUT);  
  pinMode(9, INPUT_PULLUP);  
  pinMode(10, INPUT_PULLUP);  
}

void loop() {
  Serial.println(count);

  if (digitalRead(9) == HIGH && digitalRead(10) == LOW) {
    count++;
    p=1;
    delay(300);
  }

  if (digitalRead(10) == HIGH && digitalRead(9) == LOW) {
    count--;
    p=2;
    delay(300);
  }

  Serial.println(count);

  if (count == 1) {
    int ldrStatus = analogRead(ldrPin);  

    if (ldrStatus <= 900) {
      digitalWrite(ledPin, HIGH);  
      Serial.println("LDR is dark. LED is on. Light intensity: " + String(ldrStatus));
    }
    else {
      digitalWrite(ledPin, LOW);  
      Serial.println("-------------");
    }

    int chk = DHT.read11(DHT11_PIN);
    temp = DHT.temperature;

    Serial.print("Temperature: ");
    Serial.println(temp);  

    if (temp > 27) {
      digitalWrite(2, HIGH); 
    }
    else if (temp < 27) {
      digitalWrite(2, 0);
    }

    delay(300);
  }
  else if (count == 0) {
    digitalWrite(ledPin, LOW); 
    digitalWrite(3, LOW);
    digitalWrite(2, 0);

  }
  if (count==1 && p==1){
    count++;
  }
  if (count==1 && p==2){
    count--;
  }
}
