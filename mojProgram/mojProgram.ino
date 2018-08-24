unsigned long time=0;
unsigned long previousTime=0;
//int counter=0;
int sampleTime=5;
int loopTime;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //counter++;
  
  //int sensorValue = analogRead(A0);
  // print out the value you read:
  
  time=millis();
  loopTime=time-previousTime;
  
  if(loopTime==sampleTime){
    //Serial.println(loopTime);
    //counter=0;
    Serial.println(analogRead(A0));
    previousTime=time;
    }
  if(loopTime>sampleTime){
    Serial.println(0);
    previousTime=time;
    while(true){continue;}
    }
  //delay(1000);        // delay in between reads for stability

  
}
