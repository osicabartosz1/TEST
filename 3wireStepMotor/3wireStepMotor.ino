const int yellowWire = 10;     
const int redWire = 11;     
const int blackWire = 12;     
const int orangeWire = 13;     

int count=-1;
void setup() {
    Serial.begin(9600);
    pinMode(yellowWire, OUTPUT);
    pinMode(redWire, OUTPUT);
    pinMode(blackWire, OUTPUT);
    pinMode(orangeWire, OUTPUT);

}

void loop() {
     delay(50);
     count+=1;
     if(count==5){count=1;}
     Serial.println(count);

  switch(count){
    case 1:
      digitalWrite(yellowWire, HIGH);
      digitalWrite(redWire, LOW);
      digitalWrite(blackWire, LOW);
      digitalWrite(orangeWire, LOW);

      break;
    case 2:
      digitalWrite(yellowWire, LOW);
      digitalWrite(redWire, HIGH);
      digitalWrite(blackWire, LOW);
      digitalWrite(orangeWire, LOW);

      break;
    case 3: 
      digitalWrite(yellowWire, LOW);
      digitalWrite(redWire, LOW);
      digitalWrite(blackWire, HIGH);
      digitalWrite(orangeWire, LOW);

      break;
    case 4: 
      digitalWrite(yellowWire, LOW);
      digitalWrite(redWire, LOW);
      digitalWrite(blackWire, LOW);
      digitalWrite(orangeWire, HIGH);

      break;  
    }        
}
