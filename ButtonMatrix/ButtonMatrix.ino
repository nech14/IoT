
#define RPIN_2 6
#define RPIN_1 7
#define WPIN_2 8
#define WPIN_1 9

int writingPins[] = {WPIN_1,WPIN_2};

int readingPins[] = {RPIN_1, RPIN_2};

int state = 0;
int maxState = 2;

bool states[][2] = {
  {0, 1},
  {1, 0}
};

int buttons[2][2] = {
  {1, 2},
  {3, 4}
};

bool buttonsState[] = {0, 0, 0, 0};

int coutButtons = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(RPIN_2, INPUT_PULLUP);
  pinMode(RPIN_1, INPUT_PULLUP);
  pinMode(WPIN_2, OUTPUT);
  pinMode(WPIN_1, OUTPUT); 
   
}

void loop()
{
  state = stateSwitch(state, maxState);
  magick(writingPins, states[state]);
  checkPins(readingPins, state);
  printButtonsState(coutButtons);
  delay(100);
}



void magick(int* pins, bool* state){
  for(int pin=0; pin<2; pin++){
      digitalWrite(pins[pin], state[pin]);
    }
  
}

void checkPins(int* pins, int state){
  for(int i=0; i<2; i++){
    buttonsState[buttons[state][i]-1] = digitalRead(pins[i]) == 0;
    //if(digitalRead(pins[i]) == 0){
    //  Serial.println(buttons[state][i]);
    //}
  } 
}

void printButtonsState(int count){
  bool flag = 0;
  for(int i=0; i<count; i++){
    if(buttonsState[i] == 1){
      Serial.print(i+1);      
  	  flag = 1;
    }
  }
  if(flag==1){
    Serial.println("\n--------\n");
  }
}

int stateSwitch(int stateNow, int maxState){
  stateNow++;
  if(stateNow >= maxState){
    return 0;
  }
  return stateNow;
}



