#include "bible.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//6499
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int buttonPin2 = 3;  
const int buttonPin = 2;  

const int pin1=27;
const int pin2=24;
const int pin3=28;
const int pin4=5; 
const int pinA=26;
const int pinB=4;
const int pinC=7;
const int pinD=9;
const int pinE=10;
const int pinF=25;
const int pinG=6;
const int pinDP=8;

int grid[32][32];
int vectors[4];
int seed[4];
//0000 :198 gen,, 5697 is a loop of three at above 500. plan for this, 5393 310 gen, 1147 gen352, 1156 g314beautiful
//1146, 3141 extrordanaraly low 19 gen
int arraysize=0;
int perlin;
int topa;
int bota;
int driver=0;
//gameoflifevar
int di2[32][32][2]=  {0};
int scannerx[8]={-1,0,1,-1,1,-1,0,1};
int scannery[8]={1,1,1,0,0,-1,-1,-1};
int ncount=0.0;
int mclock=0;
int lifecount=0;
int populationdata[32][8];
int stagnation=0;
//dialvar


int tickerplacement=0;
int tickercount=-1;

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int buttonState2;            // the current reading from the input pin
int lastButtonState2 = HIGH;  // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0; 
unsigned long debounceDelay = 35;

char bib[31][90][12];
int letterout;
int mastx=0;
int masty=0;
int wide=0;

int conversionarray[10]={1, 79, 18, 6, 76, 36, 32, 15, 0, 4};

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  460 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMID 280
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(19200);
pinMode(buttonPin, INPUT);
 pinMode(buttonPin2, INPUT);

 pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  pinMode(pinD, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinDP, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinE, OUTPUT);
 genesisgenesis();
   pwm.begin();
    pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
 
arraysize=32;
}

void loop() {
  // put your main code here, to run repeatedly:



  //seed to vector
  if(driver==0){
    dial(); 
    display();
  if(tickerplacement==4){
     for(int b=0; b<4; b++){
    int between;
    between=(1000*seed[b]);
    //attempts at adding dependance between variables have not proven positive
    vectors[b]=between%360;
  
  }
  for(int i=0; i<500; i++){
    display();
  }
        loading();
    loading();
    loading();

    loading();

  driver++;
  }}

  //main
  if(driver==1){
    delay(250);
  pnoise();
}

if(driver==2){
  life();
  lifecount++;
  //Serial.print("generation:");
 // Serial.println(lifecount);

  for(int x=0; x<arraysize; x++){
    int holder=0;
    for(int y=0; y<arraysize; y++){
      holder=holder+di2[x][y][0];

      if(di2[x][y][0]==1){
        mastx=mastx+x;
        masty=masty+y;
        //point of interpretation, make the pattern more present
      }
          }
    populationdata[x][lifecount%8]=holder;
  }
//Serial.print("       ");
//Serial.print(mastx);
//Serial.print(",");
//Serial.print(masty);

//reads a word from the points
scripture();



stagnation=0;
for(int k=0; k<arraysize; k++){
  
if(populationdata[k][0]==populationdata[k][1] && populationdata[k][2]==populationdata[k][3]){
  stagnation++;
 // Serial.print(stagnation);
 //   Serial.print(",");

}
if(stagnation==32&&lifecount>8){
  driver++;
 Serial.print(".");

}}
stagnation=0;
 //Serial.println();
for(int j=0; j<arraysize; j++){
if(populationdata[j][0]==populationdata[j][2] && populationdata[j][2]==populationdata[j][4]&&populationdata[j][6]==populationdata[j][4]){
  stagnation++;
 //   Serial.print(stagnation);
 //   Serial.print(",");

}
if(stagnation==32&&lifecount>8){
  driver++;
Serial.print(".");

}}


}
if (driver == 3||driver==4){
  driver=0 ;
  tickerplacement=0;
  lifecount=0;
  stagnation=0;
}
}
















void pnoise(){
  for(int x=0; x<arraysize; x++){
  for (int y=0; y<arraysize; y++){
    int keeper[4];


 
      keeper[0]=(x*cos(vectors[0]))+((arraysize-y)*sin(vectors[0]));
      keeper[1]=((arraysize-x)*cos(vectors[1]))+((arraysize-y)*sin(vectors[1]));
      keeper[2]=(x*cos(vectors[2]))+(y*sin(vectors[2]));
      keeper[3]=((arraysize-x)*cos(vectors[3]))+(y*sin(vectors[3]));
      



    topa=((32-x)*keeper[0])+(x*keeper[1]);
    bota=((32-x)*keeper[2])+(x*keeper[3]);
    perlin=((32-y)*topa)+(y*bota);
    grid[x][y]=perlin;


    Serial.print(grid[x][y]);
   Serial.print(",");
   if(grid[x][y]>8000||grid[x][y]<-8000){
    di2[x][y][0]=1;
   }
   else{
   di2[x][y][0]=0;
   }

  }
  Serial.println();
}
driver++;
Serial.print(driver);
Serial.println("<<driver#");
Serial.println();
Serial.println();
Serial.println();
Serial.println();
Serial.println();
Serial.println();
}





void life() {
   
 for(int x=0; x<arraysize; x++){
  for (int y=0; y<arraysize; y++){
    
    //scanner 
    for(int k=0; k<8; k++){
        if(di2[x+scannerx[k]][y+scannery[k]][0]==1){
          ncount=ncount+1;
        }
      }
    
    //overpopulation underpopulation script due toncount counting subject ncountneeds to be ncount-1
    if(di2[x][y][0]==1 && (ncount)<2){
      di2[x][y][1]=0;

    }
    // this if isnt needed but ||&&|&|&|||&|&|& gets hazy
    if(di2[x][y][0]==1 && (ncount)>3){
      di2[x][y][1]=0;

    }

    if(ncount==3){
      di2[x][y][1]=1;
    }
    if(di2[x][y][0]==1 && ncount==2){
            di2[x][y][1]=1;
    }
   // if(mclock<5){
   // Serial.print(ncount);
   // Serial.print(",");
   // }
    
        ncount=0;
   
  }    
  //if(mclock<5){
  // Serial.println(",ncount: ");
 // }
  }
 //Serial.print(driverNumberX);
//Serial.println(",");


    ncount=0;




//  Serial.println();
 // Serial.println();
//  Serial.println();
    for(int x=0; x<arraysize; x++){
      for(int y=0; y<arraysize; y++){
        di2[x][y][0]=di2[x][y][1];
        //ONCE FIXED COME BACK HERE THIS IS THE PRINTER
        if(di2[x][y][0]==0){
       //   Serial.print("_");
        }
        else{
       //Serial.print(di2[x][y][0]);
        }
       // Serial.print(", ");
      }
    // Serial.println( );
    }
}


void dial() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  int reading2 = digitalRead(buttonPin2);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        tickercount++;
        if(tickercount==10){
          tickercount=0;
        }

        seed[(tickerplacement%4)]=tickercount;
        Serial.println();
        Serial.print(seed[0]);
         Serial.print(seed[1]);
          Serial.print(seed[2]);
           Serial.print(seed[3]);
      }
    }
  }

  //alternateinfo

    if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:


    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        tickerplacement++;
         Serial.print(",");
         tickercount=0;

        Serial.print(tickerplacement);
      }
    }
  }
  

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  lastButtonState2 =reading2;
}

void genesisgenesis(){
  int letter=0;
  int word=0;
  int line=0;

  for(int b=0; b<4126; b++){
    bib[line][word][letter]=genesis[b];
    //return letter++ here to restore babbel
    if(genesis[b]==100){
      letter=0;
      word++;
      
    }
    
    if(genesis[b]==200){
      letter=0;
      word=0;
      line++;
    }
    letter++; 
  }

  }

  void decoder(){
    //now its num-num perhaps array organise 
    int serv=12;
    bool di=1;

if (letterout != 0){
    if(letterout==1){
      Serial.print("a");
       serv=4;
       di=0;
   
      wide++;
      
    }
    if(letterout==2){
      Serial.print("b");
      serv=2;
      di=1;
      wide++;
    }
    if(letterout==3){
      Serial.print("c");
      serv=0;
      di=1;
     wide++;
    }
    if(letterout==4){
      Serial.print("d");
      serv=9;
      di=1;
      wide++;
    }
    if(letterout==5){
      Serial.print("e");
      serv=5;
      di=0;
      wide++;
    }
    if(letterout==6){
      Serial.print("f");
      serv=1;
      di=0;
      wide++;
    }
    if(letterout==7){
      Serial.print("g");
      serv=10;
      di=1;
      wide++;
    }
    if(letterout==8){
      Serial.print("h");
      serv=2;
      di=1;
      wide++;
    }
    if(letterout==9){
      Serial.print("i");
      di=0;
      serv=12;
      wide++;
    }
    if(letterout==10){
      Serial.print("j");
      serv=3;
      di=0;
      wide++;
    }
    if(letterout==11){
      Serial.print("k");
      serv=7;
      di=0;
      wide++;
    }
    if(letterout==12){
      Serial.print("l");
      serv=13;
      di=0;
      wide++;
    }
    if(letterout==13){
      Serial.print("m");
      serv=3;
      di=1;
    
      wide++;
    }
    if(letterout==14){
      Serial.print("n");
      serv=11;
      di=1;
      wide++;
    }
    if(letterout==15){
      Serial.print("o");
      serv=7;
      di=1;
      wide++;
    }
    if(letterout==16){
      Serial.print("p");
      serv=13;
      di=1;
      wide++;
    }
    if(letterout==17){
      Serial.print("q");
     serv=8;
     di=0;  
          
      wide++;
    }
    if(letterout==18){
      Serial.print("r");
      serv=10;
      di=0;
      wide++;
    }
    if(letterout==19){
      Serial.print("s");
     serv=8;
     di=1;
      wide++;
    }

    if(letterout==20){
      Serial.print("t");
      serv=11;
      di=0;
      wide++;
    }
    if(letterout==21){
      Serial.print("u");
      serv=6;
      di=0;
      wide++;
    }
    if(letterout==22){
      Serial.print("v");
      serv=5;
      di=1;
      wide++;
    }
    if(letterout==23){
      Serial.print("w");
     serv=9;
     di=0;
      wide++;
    }
    if(letterout==24){
      Serial.print("x");
     serv=4;
     di=1;
      wide++;
    }
    if(letterout==25){
      Serial.print("y");
      serv=2;
      di=0;
      wide++;
    }
    if(letterout==26){
      Serial.print("z");
      serv=0;
      di=0;
      wide++;
    }
    if(letterout==100){
      Serial.print(" ");
      serv=12;
      di=1;
 
      wide++;
    }





      if(di==1){
              for (uint16_t pulselen = SERVOMID; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(serv, 0, pulselen);
  }
    delay(50);


  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMID; pulselen++) {
    pwm.setPWM(serv, 0, pulselen);
  }
      delay(200);
      }
      else{
         for (uint16_t pulselen = SERVOMID; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(serv, 0, pulselen);
  }
    delay(50);


  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMID; pulselen--) {
    pwm.setPWM(serv, 0, pulselen);
  }
      delay(200);

      }

      if(wide>74){
        Serial.println();
      //RETURN KEY
               for (uint16_t pulselen = SERVOMID; pulselen > 10; pulselen--) {
    pwm.setPWM(6, 0, pulselen);
  }
    delay(50);


  for (uint16_t pulselen = 10; pulselen < SERVOMID; pulselen++) {
    pwm.setPWM(6, 0, pulselen);
  }
      delay(500);
        wide=0;
      }
  }

//Serial.print(serv) ;
//Serial.print(",");
//Serial.print(letterout);
//Serial.print(",");

  }

void scripture(){
  
  for(int a=1; a<12; a++){
    letterout=bib[mastx%31][masty%80][a];
    decoder();
    if(letterout==100){
      a=12;
    }
  }
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void display(){
  bool digi1[7];//could be an issue later....
  char num;
   for(int k=0; k<4; k++){
    bool driverpin[4]={0,0,0,0};
    driverpin[k]=1;
digitalWrite(pin1, driverpin[0]);
digitalWrite(pin2, driverpin[1]);//??
digitalWrite(pin3, driverpin[2]);
digitalWrite(pin4, driverpin[3]);

   num = seed[k];
  for (int i=0; i<7; i++) {

    digi1[6-i] = bitRead(conversionarray[num], i);
    //Serial.print(digi1[i]);
  }
  

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, digi1[0]);
digitalWrite(pinB, digi1[1]);
digitalWrite(pinC, digi1[2]);
digitalWrite(pinD, digi1[3]);
digitalWrite(pinE, digi1[4]);
digitalWrite(pinF, digi1[5]);
digitalWrite(pinG, digi1[6]);
delay(1);
//Serial.println(",");
}

}

void loading(){
  
for(int k=0; k<4; k++){
  bool drivernumber[4]={0,0,0,0};
  drivernumber[k]=1;
digitalWrite(pin1, drivernumber[0]);
digitalWrite(pin2, drivernumber[1]);
digitalWrite(pin3, drivernumber[2]);
digitalWrite(pin4, drivernumber[3]);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, LOW);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
delay(60);
}
digitalWrite(pin1, LOW);
digitalWrite(pin2, LOW);
digitalWrite(pin3, LOW);
digitalWrite(pin4, HIGH);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, LOW);
digitalWrite(pinG, HIGH);
delay(60);

digitalWrite(pin1, LOW);
digitalWrite(pin2, LOW);
digitalWrite(pin3, LOW);
digitalWrite(pin4, HIGH);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, LOW);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
delay(60);

for(int k=3; k>-1; k--){
  bool drivernumber[4]={0,0,0,0};
  drivernumber[k]=1;
digitalWrite(pin1, drivernumber[0]);
digitalWrite(pin2, drivernumber[1]);
digitalWrite(pin3, drivernumber[2]);
digitalWrite(pin4, drivernumber[3]);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, LOW);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
delay(60);
}
digitalWrite(pin1, HIGH);
digitalWrite(pin2, LOW);
digitalWrite(pin3, LOW);
digitalWrite(pin4, LOW);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
delay(60);

digitalWrite(pin1, HIGH);
digitalWrite(pin2, LOW);
digitalWrite(pin3, LOW);
digitalWrite(pin4, LOW);

digitalWrite(pinDP, HIGH);
digitalWrite(pinA, HIGH);
digitalWrite(pinB, LOW);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
delay(60);


}



