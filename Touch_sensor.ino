const int touchPin = 7;

void setup(){
  Serial.begin(9600);
  pinMode(touchPin,INPUT);

}
void loop(){
  int touchValue = digitalRead(touchPin);

  if touchValue = digitalRead(touchPin);
  if(touchValue == HIGH){
    Serial.println("Touch detected!");

  }
  else {
    Serial.println("No Touch detected");

  }
  delay(1000);
}