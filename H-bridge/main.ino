
#define row12 9
#define row11 11

int direction = 0;
int speed = 100;

int close = 255;

void setup(){
  
  pinMode(row11, OUTPUT);
  pinMode(row12, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Enter direction and speed (rl 40 or rr 50):");
  
  motor(0, 0);
}

void loop(){
  if (Serial.available() > 0) { // Проверка наличия данных в последовательном порту
    String receivedData = Serial.readStringUntil('\n');
    if (receivedData.indexOf("rl") != -1) {
      
      direction = -1;
      
    }else if (receivedData.indexOf("rr") != -1){ 
        direction = 1;
    } else{ 
      direction = 0;
      motor(direction, 255);  
    }
    
    int spaceIndex = receivedData.indexOf(' ');
      
      if (spaceIndex != -1) {
        String numberString = receivedData.substring(spaceIndex + 1);
        int speed = numberString.toInt();
        
        if (speed >= 0 and speed <= 255){
        	motor(direction, speed);          
        } else if (speed > 255) {
        	Serial.println("Speed > 255");
        } else{
          Serial.println("Speed < 0");
        }
      
      }
  } 
	
  
}


void motor(int direction, int speed){
  
  if (direction == 0){
    analogWrite(row11, close);
    analogWrite(row12, close);   
  } else if (direction == -1){    
  	analogWrite(row11, speed);
  	analogWrite(row12, close);
  } else if (direction == 1){    
  	analogWrite(row11, close);
  	analogWrite(row12, speed);    
  }

}