
enum State{
  IDLE,
  READY,
  THROWING,
  SHAKE1,
  SHAKE2,
  SHAKE3,
  CAUGHT,
  ESCAPED
};


const int redLed = 11;
const int greenLed = 6;


void setup(){
  pinMode(11, OUTPUT); //red led
  pinMode(6, OUTPUT); //green LED
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  digitalWrite(greenLed, HIGH);

}




int roll;
int catchRate = 35;



bool previousButton = false;
bool currentButton = false;
enum State pokeballState = IDLE;
bool ledOn = false;


void startingSequence(State newState, bool ledOn){

  
  if(currentButton && !previousButton){
          
    Serial.println("pressed");
    pokeballState = newState;  
    previousButton = currentButton;
      
    delay(60);

  }else if(!currentButton && previousButton){     
      previousButton = false;
  }
  
  ledControl(ledOn);
}



void ledControl(bool state){
  if(state){
    digitalWrite(redLed, LOW);
  }else{
    digitalWrite(redLed, HIGH);
  }
}




void fadeInAnimation(int time, int pin){

  for(int i = 0; i <= 255 ; i++){
    
    analogWrite(pin, i);
    delay(time);
  }
}

void fadeOutAnimation(int time, int pin){

  for(int i = 255; i >= 0 ;i--){

    analogWrite(pin, i);
    delay(time);
  }
}

void loop(){

  
  currentButton = !digitalRead(4);

 

  switch (pokeballState){

    case IDLE:
      
      startingSequence(READY, false);
      Serial.println("IDLE");
      break;

    case READY:

      startingSequence(THROWING, true);
      Serial.println("READY TO THROW");
      break;

    case THROWING:

     fadeInAnimation(15, redLed); // (delay, pin)
     pokeballState = SHAKE1;
     delay(1000);
      Serial.println("THROWING");
      break;

    case SHAKE1:
      fadeInAnimation(5, redLed);
      Serial.println("SHAKE1");
      pokeballState = SHAKE2;
      break;

    case SHAKE2:
      fadeInAnimation(3, redLed);
      pokeballState = SHAKE3;
      Serial.println("SHAKE 2");
      break;
    
    case SHAKE3:
      
      fadeInAnimation(8, redLed);
      Serial.println("SHAKE 3");
      roll = random(100);
      

      
      if(roll < catchRate){
        
        pokeballState = CAUGHT;

      }else{
        Serial.println("Escaped and fled");
        
        pokeballState = ESCAPED;

        
        
      }

      break;
    
    case CAUGHT:
      Serial.println(roll);
      Serial.println("Catch");

      fadeOutAnimation(1000, greenLed);
      break;

    case ESCAPED:
      
      break;
      

      
  }
  
}

