//libraries
#include <LiquidCrystal.h>
LiquidCrystal lcd(53,52,51,50,49,48);

//variables
const int switchNum = 13;
int on = digitalRead(switchNum);
int blueButPin = 12;
int redButPin = 11;
int greenButPin = 12;
int blueBut = digitalRead(blueButPin);
int redBut = digitalRead(redButPin);
int greenBut = digitalRead(greenButPin);
bool blueHit = false;
bool redHit = false;
bool greenHit = false;
int score = 0;

void setup() {

  //LCD stuff
  lcd.begin(16,2);

  //Serial Stuff
  Serial.begin(9600);

  //pins
  pinMode(blueButPin,INPUT);
  pinMode(redButPin,INPUT);
  pinMode(greenButPin,INPUT);
  
}

void loop() {

  //Variable Updates
  on = digitalRead(switchNum);
  blueBut = digitalRead(blueButPin);
  redBut = digitalRead(redButPin);
  greenBut = digitalRead(greenButPin);

  //Serial
  Serial.print("blue: " + String(blueBut));
  Serial.print("red: " + String(redBut));
  Serial.print("green: " + String(greenBut));
  Serial.print(blueHit);

  // //hit settings
  // if(blueButPin == 1){
  //   blueHit == true;
  // }
  // if(redButPin == 1){
  //   redHit == true;
  // }
  // if(greenButPin == 1){
  //   greenHit == true;
  // }
  


  //Bulk Code
  if(on == 1){

    lcd.setCursor(0,0);
    lcd.println("Score: ");

  }
  else{
    off();
  }

}



void off(){
  lcd.clear();
}
