#include <LiquidCrystal.h>
#include <DHT.h>
#include <Servo.h>

LiquidCrystal lcd(53, 52, 51, 50, 49, 48);
DHT dht(4, DHT11);
Servo fanServo;
//setup
const int bluePin = 12;
const int redPin = 11;
const int greenPin = 10;
const int speakerPin = 9;
const int led1 = 8;
const int led2 = 7;
const int led3 = 6;
const int flipSwitch = 13;
const int dhtPin = 4;
const int servoPin = 5;
//bring in notes (prolly wont use all tho)
int getFrequency(char note) {
  if (note == 'g') return 392;
  if (note == 'a') return 440;
  if (note == 'b') return 494;
  if (note == 'C') return 523;
  if (note == 'd') return 587;
  if (note == 'E') return 659;
  if (note == 'e') return 330;
  if (note == 'f') return 370;
  if (note == 'c') return 262;
  return 0;
}
//set up array
const char colourNote[3] = { 'g', 'E', 'b' };
const int colourPin[3] = { greenPin, redPin, bluePin };
const char* colourName[3] = { "GREEN", "RED", "BLUE" };
//init
int score = 0;
bool gameRunning = false;
bool lcdMode = false;
//fan fnc by temp / humidity
void updateFan() {
  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("DHT read failed");
    return;
  }
//conversion, printing to serial for debugging
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  Serial.print("Temp: ");
  Serial.print(tempF);
  Serial.print("F  Humidity: ");
  Serial.println(humidity);

  if (tempF > 73.5) {
    int angle = map((int)humidity, 0, 100, 0, 180);
    fanServo.write(angle);
    Serial.print("Servo angle: ");
    Serial.println(angle);
  } else {
    fanServo.write(0);
    Serial.println("Fan OFF (servo at 0)");
  }
//switch type
  if (!lcdMode) {
    float tempC = dht.readTemperature();
    float humidity = dht.readHumidity();
    float tempF = tempC * 9.0 / 5.0 + 32.0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempF, 1);
    lcd.print("F");
    lcd.setCursor(0, 1);
    lcd.print("Humid: ");
    lcd.print(humidity, 1);
    lcd.print("%");
  }
}
//if game lost, run thru the light show
void lightShow() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    tone(speakerPin, 100, 80);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    tone(speakerPin, 200, 80);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    tone(speakerPin, 300, 80);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    tone(speakerPin, 400, 80);
    delay(100);
  }
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  noTone(speakerPin);
}
//womp womp
void showGameOver() {
  if (lcdMode) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  GAME  OVER  ");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
  }
  lightShow();
  delay(2000);
}
//game init
void startGame() {
  score = 0;
  gameRunning = true;
  if (lcdMode) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  BOP  IT!  ");
  }
  delay(1500);
}
//correntIndex as wfb fnc param, allows tracking of bops 
bool waitForButton(int correctIndex) {
  unsigned long start = millis();
  while (millis() - start < 4000) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(colourPin[i]) == LOW) {
        Serial.print("Button pressed: ");
        Serial.println(i);
        Serial.print("Correct index: ");
        Serial.println(correctIndex);
        return (i == correctIndex);
      }
    }
  }
  return false;
}
//yap stuff
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  dht.begin();
  fanServo.attach(servoPin);

  pinMode(bluePin, INPUT_PULLUP);
  pinMode(redPin, INPUT_PULLUP);
  pinMode(greenPin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(flipSwitch, INPUT);
}
//beef
void loop() {
  lcdMode = (digitalRead(flipSwitch) == HIGH);
  updateFan();
//game run init
  if (lcdMode) {
    if (!gameRunning) {
      startGame();
      Serial.println("Starting game...");
    }
//cmd crucial for game funcion, allows to cycle through the possibilities randomly
    int cmd = random(0, 3);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BOP IT!");
    lcd.setCursor(0, 1);
    lcd.print(colourName[cmd]);
    Serial.println(cmd);
//speaker command
    tone(speakerPin, getFrequency(colourNote[cmd]), 300);
    delay(1500);
    noTone(speakerPin);

    bool correct = waitForButton(cmd);
//big fnc, needs debugging ?
    if (correct) {
      score++;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nice! Score:");
      lcd.setCursor(0, 1);
      lcd.print(score);
      Serial.print("Score: ");
      Serial.println(score);
      tone(speakerPin, getFrequency('C'), 150);
      delay(400);
      noTone(speakerPin);
    } else {
      gameRunning = false;
      showGameOver();
    }

  } else {
    gameRunning = false;
  }
}