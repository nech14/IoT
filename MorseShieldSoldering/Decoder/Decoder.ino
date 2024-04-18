
// Latch pin (ST_CP) of 74HC595 to pin 5
int latchPin = 3;      
// Latch pin (SH_CP) of 74HC595 to pin 6
int clockPin = 2;
// Data pin (DS of 74HC595 to pin 6
int dataPin = 4;       
// Make sure MR is HIGH (connect ot Vcc)

int potPin = A0;
int ledData = 12;

int checkData = 0;

int frequency = 1;

bool startSetting = 0;
int countTimeSetting = 0;

int countTime = 0;
int lastState = 0;
int missState = 0;

bool startData = 0;
String data = "";
int lenData = 0;
int lastSymbol = 0;

unsigned long lastCheckSetting = millis();
unsigned long lastCheck = millis();
unsigned long nowTime = millis();


bool digits[37][8] = {
  {1,1,1,0,1,1,1,0}, //  A
  {0,0,1,1,1,1,1,0}, //  B
  {1,0,0,1,1,0,1,0}, //  C
  {0,1,1,1,1,1,0,0}, //  D
  {1,0,0,1,1,1,1,0}, //  E
  {1,0,0,0,1,1,1,0}, //  F
  {1,0,1,1,1,0,1,0}, //  G
  {0,0,1,0,1,1,1,0}, //  H
  {0,0,1,0,0,0,0,0}, //  I
  {0,1,1,1,1,0,0,0}, //  J
  {1,0,1,0,1,1,1,0}, //  K
  {0,1,1,1,0,0,0,0}, //  L
  {1,0,1,0,1,1,0,0}, //  M
  {0,0,1,0,1,1,0,0}, //  N
  {0,0,1,1,1,1,0,0}, //  O
  {1,1,0,0,1,1,1,0}, //  P 
  {1,1,1,0,0,1,1,0}, //  Q
  {0,0,0,0,1,1,0,0}, //  R
  {1,0,1,1,0,1,1,0}, //  S
  {0,0,0,1,1,1,1,0}, //  T
  {0,1,1,1,1,0,1,0}, //  U
  {0,0,1,1,1,0,0,0}, //  V
  {0,1,0,1,0,1,1,0}, //  W
  {0,1,1,0,1,1,1,0}, //  X
  {0,1,1,1,0,1,1,0}, //  Y
  {1,1,0,1,1,1,0,0}, //  Z
  {1,1,1,1,1,0,1,0}, //  0
  {0,1,1,0,0,0,0,0}, //  1
  {1,1,0,1,1,1,0,0}, //  2
  {1,1,1,1,0,1,0,0}, //  3
  {0,1,1,0,0,1,1,0}, //  4
  {1,0,1,1,0,1,1,0}, //  5
  {1,0,1,1,1,1,1,0}, //  6
  {1,1,1,0,0,0,0,0}, //  7
  {1,1,1,1,1,1,1,0}, //  8
  {1,1,1,0,0,1,1,0}, //  9
  {0,0,0,0,0,0,0,0}, //Empty Space
};

String morseAlphabet[] = {
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--..",
  "-----",
  ".----",
  "..---",
  "...--",
  "....-",
  ".....",
  "-....",
  "--...",
  "---..",
  "----."
};



bool resultArray[8] = {0,0,0,0,0,0,0,0};

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
  pinMode(ledData, INPUT);
  
  digitalWrite(clockPin, LOW);
  //digitalWrite(latchPin, HIGH);
  Serial.begin(9600);
  //for(int i=5; i < 10; i++){    
  //  show_number(i);
  //	delay(500);
  //}
  show_number(36);
}

void loop() 
{
  
  nowTime = millis();
  
  if(nowTime - lastCheckSetting >= 1000){
    checkData = digitalRead(ledData);
    frequency = int(analogRead(potPin)/100)+1;
    
    if(checkData != 0 and countTimeSetting<10){
      countTimeSetting += 1;
    } else if(countTimeSetting > 0 and !(checkData != 0)){
      countTimeSetting = 0;
      startSetting = 0;
    }
    
    if(countTimeSetting >= 10){
      startSetting = 1;       
      countTime = 0;
      missState = 0;
    }
    
    if(startSetting){
      Serial.print("Potentiometer Value: ");
      Serial.println(frequency);
      Serial.println(nowTime);
    }
    
    lastCheckSetting = nowTime;
  }
  else if(nowTime - lastCheck >= 100*frequency){
    checkData = digitalRead(ledData);
    lastState = countTime;
    
    if(checkData != 0){
        countTime += 1;
      	missState = 0;
      	startData = 1;
    } else if(countTime != 0) {
    	countTime = 0;
    } else{
      	missState += 1;
    }
    
    if (startData && countTime==0){
      if (lastState == 1){
      	data += '.';
        lenData += 1;
      }else if(lastState >= 2){
      	data += '-';
        lenData += 1;
      } else if(missState == 3){
        
        String symbol = "";
        
        for(int i=lastSymbol; i<lenData; i++){
        	symbol += data[i];
        }
        
        show_number(checkSymbol(symbol));
        
      	data += ' ';
        lenData += 1;
        lastSymbol = lenData;
        //Serial.println(lastSymbol);
        //Serial.print(" g ");
        //Serial.print(symbol);
        //Serial.println(" ");
        
      } else if(missState == 7 || missState == 10){
      	data += '/';
        lenData += 1;
        lastSymbol += 1;
        show_number(36);
      }
    }
    if (lenData > 0){
      Serial.println(lenData);
      Serial.println(data);
    }
    lastCheck = nowTime;  	
  }
  
}


int checkSymbol(String symbol){
  show_number(36);  
  for(int i=0; i<37; i++){
    if(symbol == morseAlphabet[i]){
    	return i;
    }
  }
  
}


void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  if(digit <0 or digit >36) {
    return;
  }
  
  rearrangeArray(digits[digit], resultArray);
  
  for(int i = 7; i >=0; i--) {
    shift_and_set(
      resultArray[i]
    );
  }
  digitalWrite(latchPin, HIGH);
}


void shift_and_set(bool val) {
  digitalWrite(dataPin, val);
  digitalWrite(clockPin, HIGH);
  delay(10);
  digitalWrite(clockPin, LOW);
}


void rearrangeArray(bool input[], bool output[]) {
    int newOrder[8] = {3,1,4,6,7,0,2,5};
    //int newOrder[8] = {1,1,1,1,1,1,1,1};

    for (int i = 0; i < 8; ++i) {
        output[newOrder[i]] = !input[i];
    }
}



