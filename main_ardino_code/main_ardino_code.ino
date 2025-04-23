
int Led_One = 2;

void setup(){

  pinMode(Led_One, OUTPUT);

  Serial.begin(115200);

}
void loop(){


  digitalWrite(Led_One, LOW);


  delay(1000);


  digitalWrite(Led_One, HIGH);


  delay(1000);
}