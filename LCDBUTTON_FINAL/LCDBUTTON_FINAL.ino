//libraries
#include <LiquidCrystal.h>
LiquidCrystal lcd(53,52,51,50,49,48);

//variables
const int switchNum = 13;
int on = digitalRead(switchNum);
int bluePin = 12;
int redPin = 11;
int greenPin = 12;
int speakerPin = 9;
int led1 = 9;
int led2 = 8;
int blueButton = digitalRead(bluePin);
int redButton = digitalRead(redPin);
int greenButton = digitalRead(greenPin);

int score = 0;

void setup() {

  //LCD stuff
  lcd.begin(16,2);

  //Serial Stuff
  Serial.begin(9600);

  //pins
  pinMode(bluePin,INPUT);
  pinMode(redPin,INPUT);
  pinMode(greenPin,INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
}

void loop() {

  //Variable Updates
  on = digitalRead(switchNum);
  blueButton = digitalRead(bluePin);
  redButton = digitalRead(redPin);
  greenButton = digitalRead(greenPin);
  pinMode(speakerPin, OUTPUT);

  //Serial
  Serial.print("blue: " + String(blueButton));
  Serial.print("red: " + String(redButton));
  Serial.print("green: " + String(greenButton));
  Serial.print(blueButton);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  // //hit settings
  // if(bluePin == 1){
  //   blueHit == true;
  // }
  // if(redPin == 1){
  //   redHit == true;
  // }
  // if(greenPin == 1){
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
