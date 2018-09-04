int count=0;
String previousMessage="@";
unsigned long timeMillis=0;
int onPulseDuration=15;
int offPulseDuration=15;
//encoder Wires
//const int YellowWire = 16;     
const int OrangeWire = 6;     
const int WhiteWire = 5;     
const int VioletWire = 7;     
//Motor Control
const int IN1 = 4;     
const int IN2 = 10;     
const int IN3 = 11;     
const int IN4 = 12;
const int powerControlPin = 3;
const int pulseFrontWheelsPin = 3;
const int pulseBackWheelsPin = 9;

int frontWheels=0;
int backWheels=0;

bool rigth=true;
void setup() {
    Serial.begin(9600);
   
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
//    pinMode(powerControlPin, OUTPUT);
    pinMode(pulseFrontWheelsPin, OUTPUT);
    pinMode(pulseBackWheelsPin, OUTPUT);
    analogWrite(pulseFrontWheelsPin, 120);
    analogWrite(pulseBackWheelsPin, 80);

//    pinMode(YellowWire, INPUT);
    pinMode(OrangeWire, INPUT);
    pinMode(WhiteWire, INPUT);
    pinMode(VioletWire, INPUT);

    pinMode(PIN_A0, OUTPUT);
    pinMode(PIN_A1, OUTPUT);
    pinMode(PIN_A2, INPUT);
    pinMode(PIN_A3, INPUT);
    pinMode(PIN_A4, INPUT);
    pinMode(PIN_A5, INPUT);
    pinMode(PIN_A6, INPUT);
    digitalWrite(PIN_A0, LOW);
    digitalWrite(PIN_A1, HIGH);

    
}
void stopFrontWheels(int delayValue){
          delay(delayValue);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);  
  }
void stopBackWheels(int delayValue){
          backWheels=0;
          delay(delayValue);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);  
          //Serial.println("stopBackWheels");
  }
void goForward(){
          backWheels=1;
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
  }

void goBack(){
          backWheels=-1;
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
  }
void straigh(int whiteWireState,int violetWireState){
    frontWheels=2;
    if(whiteWireState){
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    if(violetWireState){
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
}
void turnLeft(int violetWireState){
    frontWheels=1;
    Serial.println("turnLeft");

    if(violetWireState){
    Serial.println("nothing");
      }
      else{
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        }
  }

void turnRight(int whiteWireState){
     frontWheels=3;
     Serial.println("turnRight");
     if(whiteWireState){
    Serial.println("nothing");
      }
      else{
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        }
  }
void loop() {
       //digitalWrite(pulseFrontWheelsPin, HIGH);  
       //digitalWrite(pulseBackWheelsPin, HIGH);

      if((millis()-timeMillis)>250){
          stopBackWheels(0);
          stopFrontWheels(0);
        }
      /*if(millis()>(timeMillis+offPulseDuration)){
        digitalWrite(pulseFrontWheelsPin, HIGH);  
        digitalWrite(pulseBackWheelsPin, HIGH); 
      }
      if(millis()>(timeMillis+onPulseDuration+offPulseDuration)){
              timeMillis=millis();
              digitalWrite(pulseFrontWheelsPin, LOW);  
              digitalWrite(pulseBackWheelsPin, LOW); 
      }  */
      
      int orangeWireState = digitalRead(OrangeWire);
      int violetWireState = digitalRead(VioletWire);
      int whiteWireState = digitalRead(WhiteWire);
      String message="";
      if(whiteWireState){message+="Prawo";}
      if(violetWireState){message+="Lewo";}
      if(orangeWireState){message+=" lekko";}
      if(message==""){message="Prosto";}

      if(previousMessage!=message){Serial.println(message);}
      previousMessage=message;
      if(message=="Prosto"&&frontWheels==2){stopFrontWheels(0);}
      if(violetWireState&&frontWheels==1){stopFrontWheels(200);}
      if(whiteWireState&&frontWheels==3){stopFrontWheels(200);}

      //Serial.println("A"); // typ nadajnika

if (digitalRead(PIN_A2)) {
        count+=1;
        timeMillis=millis();
          Serial.println("Wcisnieto klawisz dwa/prosto");
          goForward();       
        }
if (digitalRead(PIN_A3)) {
        count+=1;
        timeMillis=millis();
          Serial.println("Wcisnieto klawisz cztery/lewo");
          Serial.print("orangeWireState: ");
          Serial.println(orangeWireState);
          Serial.print("violetWireState");
          Serial.println(violetWireState);
          Serial.print("whiteWireState");
          Serial.println(whiteWireState);

          turnLeft(violetWireState);        
        }
if (digitalRead(PIN_A4)) {
        count+=1;
        timeMillis=millis();
          Serial.println("Wcisnieto klawisz szesc/prawo ");
          turnRight(whiteWireState);
        }
if (digitalRead(PIN_A5)) {
        count+=1;
        timeMillis=millis();
          Serial.println("Wcisnieto klawisz 8/w tyl");
          goBack();          
       }
if((!(digitalRead(PIN_A3)))&&(!(digitalRead(PIN_A4)))){straigh(whiteWireState,violetWireState);}
if((!(digitalRead(PIN_A2)))&&(!(digitalRead(PIN_A5)))){stopBackWheels(0);}

}

