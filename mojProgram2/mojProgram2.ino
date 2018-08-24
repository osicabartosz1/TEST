int counter=0;
int table[2][128];
int MAX=200;
double M_PI=3.1415926535897932384;
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

  microsTime=micros();
  table[1][counter] = analogRead(A0);
  sampleTime=microsTime - lastUpdate;
  lastUpdate = microsTime;
  table[0][counter] =sampleTime;
  
  counter++;
  if(counter==128){
     counter=0;
     //check sampleTime's
     if(check()){
       Serial.println("OK");
       while(true){continue;}
       }else{
        Serial.println("NOK");
        for(int i=0;i<128;i++){
          Serial.println(table[0][i]);
        }
        
        }

    int samplesTable[2];
    theLongestPartWithoutChange(samplesTable);
    
   // Serial.println(samplesTable[0]);
   // Serial.println(samplesTable[1]);
    plotFFT(samplesTable);

    
while(true){continue;}
    //plotFFT();
  }
}
bool check(){
  int sampleConst=table[0][2];
  Serial.print("sampleConst");Serial.println(sampleConst);
  for(int i=2;i<128;i++){
        if(sampleConst!=table[0][i]){return false;}
    }
  return true;
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
        samples[1]=maxLengthOfSamples;
       // return out;
    }

void plotFFT(int samplesTableTemp[]){
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
 
    // reverse-binary reindexing
    n = nn<<1;
    j=1;
    for (i=1; i<n; i+=2) {
        if (j>i) {
            swap(data[j-1], data[i-1]);
            swap(data[j], data[i]);
        }
        m = nn;
        while (m>=2 && j>m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };
 
    // here begins the Danielson-Lanczos section
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = -(2*M_PI/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr * data[j] + wi*data[j-1];
 
                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp=wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax=istep;
    }
      
}
      
