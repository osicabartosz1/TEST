#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

//#include <RobotIRremote.h>
//#include <RobotIRremoteInt.h>
//#include <RobotIRremoteTools.h>

//#include <IRremote.h>
//#include <IRremoteInt.h>


int count=0;
String previousMessage="@";
unsigned long timeMillis=0;
int onPulseDuration=15;
int offPulseDuration=15;
//encoder Wires
const int YellowWire = 16;     
const int OrangeWire = 6;     
const int WhiteWire = 5;     
const int VioletWire = 7;     
//Motor Control
const int IN1 = 9;     
const int IN2 = 10;     
const int IN3 = 11;     
const int IN4 = 12;
const int powerControlPin = 3;
const int pulseFrontWheelsPin = 4;
const int pulseBackWheelsPin = 3;

//Remote Pilot
const int RC = 8;     
int frontWheels=0;
int backWheels=0;
IRrecv irrecv(RC);
decode_results signals;

bool rigth=true;
void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(powerControlPin, OUTPUT);
    pinMode(pulseFrontWheelsPin, OUTPUT);
    pinMode(pulseBackWheelsPin, OUTPUT);


    pinMode(YellowWire, INPUT);
    pinMode(OrangeWire, INPUT);
    pinMode(WhiteWire, INPUT);
    pinMode(VioletWire, INPUT);

    
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
          Serial.println("stopBackWheels");
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
    if(violetWireState){
      //nothing
      }
      else{
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        }
  }

void turnRight(int whiteWireState){
     frontWheels=3;
     if(whiteWireState){
      //nothing
      }
      else{
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        }
  }
void loop() {
       digitalWrite(pulseFrontWheelsPin, HIGH);  
       digitalWrite(pulseBackWheelsPin, HIGH);

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

if (irrecv.decode(&signals)) {
        count+=1;
        timeMillis=millis();

        //Serial.println(signals.decode_type); // typ nadajnika
       //Serial.print(F("wynik = 0x"));

       // Serial.println(signals.bits); // iloĹ›Ä‡ przesĹ‚anych danych
        irrecv.blink13(true); // mrugamy diodami w arduino
        
        // PrzykĹ‚adowe porĂłwnanie:
        
        if (signals.value != 0xFFFFFFFF)
        {
          Serial.print("IN "); // 
          Serial.println(count); //
          Serial.print("HEX: ");
          Serial.println(signals.value, HEX); // wynik w systemie szesnatkowym
          Serial.print("DEC: ");
          Serial.println(String(signals.value));
        }
        if (signals.value == 0xFFFFFFFF)
        {

          //Serial.println("Wcisnieto klawisz Overflow");
        }
        if (signals.value == 0xFF10EF)
        {
          Serial.println("Wcisnieto klawisz lewo");
        }
        if (signals.value == 0xFF18E7)
        {
          Serial.println("Wcisnieto klawisz gora");
          onPulseDuration+=5;
          //offPulseDuration+=1;
          Serial.print("onPulseDuration: ");
          Serial.println(onPulseDuration);
          Serial.print("offPulseDuration: ");
          Serial.println(offPulseDuration);
        }
        if (signals.value == 0xFF5AA5)
        {
          Serial.println("Wcisnieto klawisz prawo");
        }    
        //FF4AB5
        if (signals.value == 0xFF4AB5)
        {
          Serial.println("Wcisnieto klawisz dol");
          onPulseDuration-=1;
          if (onPulseDuration==3){onPulseDuration=4;}
          //offPulseDuration-=1;
          Serial.print("onPulseDuration: ");
          Serial.println(onPulseDuration);
          Serial.print("offPulseDuration: ");
          Serial.println(offPulseDuration);
        }    
        if (signals.value == 0xFFA25D)
        {
          Serial.println("Wcisnieto klawisz jeden/lewo i prosto");
          goForward();
          turnLeft(violetWireState);

        } 
                if (signals.value == 0xFF629D)
        {
          Serial.println("Wcisnieto klawisz dwa/prosto");
          goForward();
          straigh(whiteWireState,violetWireState);
        } 
                if (signals.value == 0xFFE21D)
        {
          Serial.println("Wcisnieto klawisz trzy/prawo i prosto");
          goForward();
          turnRight(whiteWireState);
        } 
        //FF22DD
        if (signals.value == 0xFF22DD)
        {
          Serial.println("Wcisnieto klawisz cztery/lewo");
          stopBackWheels(0);
          turnLeft(violetWireState);
        }
                if (signals.value == 0xFF02FD)
        {
          Serial.println("Wcisnieto klawisz piec/stop");
          stopBackWheels(0);
          straigh(whiteWireState,violetWireState);
        }     
        //FFC23D
        
        if (signals.value == 0xFFC23D)
        {
          Serial.println("Wcisnieto klawisz szesc/prawo ");
          stopBackWheels(0);
          turnRight(whiteWireState);

        }
        //FFE01F
        if (signals.value == 0xFFE01F)
        {
          Serial.println("Wcisnieto klawisz siedem/lewo i w tyl");
          goBack();
          turnLeft(violetWireState);

        }
        //FFA857
        if (signals.value == 0xFFA857)
        {
          Serial.println("Wcisnieto klawisz 8/w tyl");
          goBack();
          straigh(whiteWireState,violetWireState);
        }
        //FF906F

        if (signals.value == 0xFF906F)
        {
          Serial.println("Wcisnieto klawisz dziewiec/prawo i w tyl");
          goBack();
          turnRight(whiteWireState);
          }
        if (signals.value == 0xFF6897 || signals.value == 0xC101E57B)
        {
          Serial.println("Wcisnieto klawisz gwiazdka/stop");
          stopBackWheels(0);
          stopFrontWheels(0);
          frontWheels=0;
        }
        // ... i tak dalej
        
        irrecv.resume(); // nasĹ‚uchujemy na nastÄ™pne nadanie     
    }
}

