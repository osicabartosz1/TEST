int counter=0;
int MAX=128;
int table[2][128];

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  // print out the value you read:
  static long lastUpdate;
  static long sampleTime;
  static long microsTime;
 delay(2);
  microsTime=micros();
  table[1][counter] = analogRead(A0);
  sampleTime=microsTime - lastUpdate;
  lastUpdate = microsTime;
  table[0][counter] =sampleTime;
  
  counter++;
  if(counter==MAX){
     counter=0;
     //check sampleTime's
    int samplesTable[2];
    theLongestPartWithoutChange(samplesTable);
    //Serial.println(table[0][samplesTable[0]]);
    plotFFT(samplesTable);
    while(true){continue;}
  }
}

void theLongestPartWithoutChange(int samples[]){
      int lengthOfSamples=0;
      int startPosition=0;
      int maxLengthOfSamples=0;
      int maxStartPosition=0;
      int value=-1;
      for(int i=0;i<128;i++){
          if(table[0][i]!=value){
            if(lengthOfSamples>maxLengthOfSamples){
                maxLengthOfSamples=lengthOfSamples;
                maxStartPosition=startPosition;
              }
            value=table[0][i];
            lengthOfSamples=1;
            startPosition=i; 
            continue;           
          }
          lengthOfSamples++;
          if(lengthOfSamples>maxLengthOfSamples){
                maxLengthOfSamples=lengthOfSamples;
                maxStartPosition=startPosition;
          }
        }
        //Serial.println(maxStartPosition);
        //Serial.println(maxLengthOfSamples);

        samples[0]=maxStartPosition;
        samples[1]=pow(2,log2(maxLengthOfSamples));
        //samples[1]=maxLengthOfSamples;

       // return out;
    }
int log2(int N)    /*function to calculate the log2(.) of int numbers*/
{
  int k = N, i = 0;
  while(k) {
    k=(k-k%2)/2;
    i++;
  }
  return i - 1;
}
void plotFFT(int samplesTableTemp[]){
        int n=samplesTableTemp[1];
        //Serial.println(samplesTableTemp[0]);
        //Serial.println(samplesTableTemp[1]);

        double vec[MAX];
        double sum=0;
        double averyge=0;
  for(int i = 0; i <= n; i++) {vec[i]=table[1][samplesTableTemp[0]+i];
    sum+=vec[i];
  }
//  Serial.println(sum);
//  Serial.println(n);
  averyge=sum/(n+1);
//  Serial.println(averyge);
  //FFT(vec, n, d);
      //Serial.println(vec[j]);
      int xRe=0;
      int xIm=0;
      for(int k=0;k<(n+2)/2;k++){
          for(int n1=0;n1<n;n++){
            xRe+=vec[n]*cos(-2*PI*n1*k/n);
            xIm+=vec[n]*sin(-2*PI*n1*k/n);
            
            }
            Serial.println(sqrt(pow(xRe,2)+pow(xIm,2)));
            xRe=0;
            xIm=0;
        }
}
      
