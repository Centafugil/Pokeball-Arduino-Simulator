
enum State{
  IDLE,
  READY,
  THROWING,
  SHAKE1,
  SHAKE2,
  SHAKE3,
  CAUGHT,
  ESCAPED,
  RESULT
};

struct Color {
  int red;
  int green;
  int blue;
};


Color red;
Color green;
Color blue;
Color orange;
Color yellow;
Color purple;
Color white;


struct Pokemon{
  
  int spawnThreshold;
  int catchRate;
  int pokemonID;   //pokemonID is 0 to 4
  int rarity; // 0 - common, 1- uncommon , 2 - rare, 3- mythical
};

Pokemon bidoof;
Pokemon pikachu;
Pokemon beldum;
Pokemon garchomp;
Pokemon mewtwo;
Pokemon currentPokemon;


const int redLed = 11;  // physical pins
const int greenLed = 6;
const int blueLed = 9;


void setup(){
  pinMode(11, OUTPUT); //red led
  pinMode(6, OUTPUT); //green LED
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  digitalWrite(greenLed, HIGH);



  // orange colour RGB values
  orange.red = 255;
  orange.green = 35;
  orange.blue = 0;

  // Red colour RGB values
  red.red = 255;
  red.green = 0;
  red.blue = 0;

  // Green colour RGB values
  green.red = 0;
  green.green = 255;
  green.blue = 0;

  // blue colour RGB values
  
  blue.red = 0;
  blue.green = 0;
  blue.blue = 255;

  //Yellow color RGB values

  yellow.red = 255;
  yellow.green = 255;
  yellow.blue = 0;

  //White color RGB values

  white.red = 255;
  white.green = 255;
  white.blue = 255;

  //Purple color RGB values

  purple.red = 162;
  purple.green = 0;
  purple.blue = 255;


  // pokemon attributes

  bidoof.catchRate = 45;
  bidoof.spawnThreshold = 75;
  bidoof.pokemonID = 0;
  bidoof.rarity = 0;

  pikachu.catchRate = 45;
  pikachu.spawnThreshold = 85;
  pikachu.pokemonID = 1;
  pikachu.rarity = 1;

  beldum.catchRate = 45;
  beldum.spawnThreshold = 92;
  beldum.pokemonID = 2;
  beldum.rarity = 1;

  garchomp.catchRate = 45;
  garchomp.spawnThreshold = 97;
  garchomp.pokemonID = 3;
  garchomp.rarity = 2;

  mewtwo.catchRate = 45;
  mewtwo.spawnThreshold = 100;
  mewtwo.pokemonID = 4;
  mewtwo.rarity = 3;
}




int spawnRoll;  //Random value generator variables
int catchRoll;




bool previousButton = false;
bool currentButton = false;

enum State pokeballState = IDLE; //default state
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
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, HIGH);
  }
}




void fadeInAnimation(int time, Color colour){



  for(int brightness = 0; brightness <= 255 ; brightness++){
    
    int red = colour.red * brightness/255;
    int green = colour.green * brightness/255;
    int blue = colour.blue * brightness/255;


    analogWrite(redLed, 255 - red );
    analogWrite(greenLed, 255 -green);
    analogWrite(blueLed, 255 - blue);



    delay(time);
  }
}


void pokemonSpawner(){

  if(spawnRoll < bidoof.spawnThreshold){
    currentPokemon = bidoof;
  }else if(spawnRoll >= bidoof.spawnThreshold && spawnRoll <= pikachu.spawnThreshold){
    currentPokemon = pikachu;
  }else if(spawnRoll > pikachu.spawnThreshold && spawnRoll <= beldum.spawnThreshold){
    currentPokemon = beldum;
  }else if(spawnRoll > beldum.spawnThreshold && spawnRoll <= garchomp.spawnThreshold){
    currentPokemon = garchomp;
  }else if(spawnRoll > garchomp.spawnThreshold && spawnRoll <= mewtwo.spawnThreshold){
    currentPokemon = mewtwo;
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

     fadeInAnimation(8, red ); // (delay, Colour )
     pokeballState = SHAKE1;
     delay(1000);
      Serial.println("THROWING");
      break;

    case SHAKE1:
      fadeInAnimation(5, red);
      Serial.println("SHAKE1");
      pokeballState = SHAKE2;
      break;

    case SHAKE2:
      fadeInAnimation(5, red);
      pokeballState = SHAKE3;
      Serial.println("SHAKE 2");
      break;
    
    case SHAKE3:
      
      fadeInAnimation(6, red);
      Serial.println("SHAKE 3");
      spawnRoll = random(101);
      catchRoll = random(101);

      pokemonSpawner();


      Serial.println("Pokemon:");
      Serial.println(currentPokemon.pokemonID);



      if(catchRoll < currentPokemon.catchRate){
        pokeballState = CAUGHT;
      }else{
        pokeballState = ESCAPED;
      }
      
      break;

    case CAUGHT:
      Serial.println(catchRoll);
      Serial.println(spawnRoll);
      Serial.println("Catch");

      

      delay(500);

      pokeballState = RESULT;

      break;

    case ESCAPED:
      Serial.println("Escaped");
      fadeInAnimation(11, orange);
      
      Serial.println(catchRoll);
      Serial.println(spawnRoll);
      
      delay(500);

      pokeballState = IDLE;
      
      break;

    case RESULT:
      
      switch (currentPokemon.rarity){
        case 0 :

          fadeInAnimation(20, green);
          Serial.println("common");

          break;
        case 1 :

          fadeInAnimation(20, blue);
          Serial.println("Un common");
          break;
        case 2:

          fadeInAnimation(20, orange);
          Serial.println("RARE");
          break;
        case 3:

          fadeInAnimation(20, white);
          Serial.println("MYTHICAL");
          break;

        

      }

      delay(300);
      pokeballState = IDLE;
      
      break;
      
      
      
  }
  
}

