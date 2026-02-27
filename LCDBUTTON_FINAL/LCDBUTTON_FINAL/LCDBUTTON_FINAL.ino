//libraries
#include <LiquidCrystal.h>
LiquidCrystal lcd(53,52,51,50,49,48);

//variables
const int switchNum = 13;
int on = digitalRead(switchNum);
int bluePin = 12;
int redPin = 11;
int greenPin = 10;
int speakerPin = 9;
int led1 = 8;
int led2 = 7;
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
  pinMode(led2, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  
}

void loop() {

  //Variable Updates
  on = digitalRead(switchNum);
  blueButton = digitalRead(bluePin);
  redButton = digitalRead(redPin);
  greenButton = digitalRead(greenPin);
  int frequecy = getFrequency('g');
  int duration = 1500/8;

  //Serial
  Serial.println("blue: " + String(blueButton));
  Serial.println("red: " + String(redButton));
  Serial.println("green: " + String(greenButton));


  //Bulk Code
  if(on == 1){

    //LCD
    lcd.setCursor(0,0);
    lcd.println("Score: ");

    //LED
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);

    //Speaker
    tone(speakerPin,255,duration);
    delay(1000);

  }
  else{
    off();
  }

}



void off(){
  lcd.clear();
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  noTone(speakerPin);
}

int getFrequency(char note){ //this is an int because there is no decimal

  //the function can only return one time, so only one of gabcde
  if(note == 'g') return 392;
  if(note == 'a') return 440;
  if(note == 'b') return 494;
  if(note == 'C') return 523;
  if(note == 'd') return 587;
  if(note == 'E') return 659;
  if(note == 'e') return 330;
  if(note == 'f') return 370;
  if(note == 'E') return 659;
  if(note == 'c') return 262;
  return 0; // this part is for pauses in the song

}

