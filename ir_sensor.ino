int ir_sensor = 7;
int buzzer = 6;

void setup() {
  // put your setup code here, to run once:
pinMode(ir_sensor,INPUT);
pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int data = digitalRead(ir_sensor);
Serial.println(data);
if(data==0){
  digitalWrite(buzzer, HIGH);

}
else{
  digitalWrite(buzzer,LOW);
}
}
