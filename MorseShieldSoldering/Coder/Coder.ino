
int dataPin = 0;  
int potPin = A0;


const char letterMap[] = {
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z',
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  ' '
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
  "----.",
  "/"
};

int lenMorseAlphabet[] = {
  2,
  4,
  4,
  3,
  1,
  4,
  3,
  4,
  2,
  4,
  3,
  4,
  2,
  2,
  3,
  4,
  4,
  3,
  3,
  1,
  3,
  4,
  3,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  1
};


int frequency = 1;
int time = 100*frequency;

int lenText = 7;
String text = "SOS GG1";

String data = "";
int lenData = 0;
String data1 = "-... .- -.-./.-";


void setup()
{
  pinMode(dataPin, OUTPUT);
  
  frequency = int(analogRead(potPin)/100)+1;
  time = 100*frequency;
  
  for(int i=0; i<lenText; i++){
  	
    for(int j=0; j<38; j++){
      if(text[i] == letterMap[j]){
      	data += morseAlphabet[j];
        data += ' ';
        lenData += lenMorseAlphabet[j]+1;
      }
      
    }
  }
  
  Serial.println(data);
  Serial.println(lenData);
  
  for(int i=0; i < lenData; i++){
  	Serial.println(lenData);
  	digitalWrite(dataPin, LOW);
    delay(time);
    if (data[i] == '.'){
      	digitalWrite(dataPin, HIGH);
    	delay(time);
    } else if(data[i] == '-'){
      	digitalWrite(dataPin, HIGH);
    	delay(time*2);
    } else if(data[i] == ' '){
    	delay(time*3);
    } else if(data[i] == '/'){
    	delay(time*7);
    }
  }
  
  //Serial.begin(9600);
}

void loop()
{
  
  
}