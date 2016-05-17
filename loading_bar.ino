#include<LiquidCrystal.h>

//OBJECT CREATION
LiquidCrystal lcd(12,11,5,4,3,2);
const int switchPin=6;

//BYTES
byte first[8]   = { B10000, B10000, B10000, B10000, B10000, B10000, B10000, 16};
byte second[8]  = { B11000, B11000, B11000, B11000, B11000, B11000, B11000, 24};
byte third[8]   = { B11100, B11100, B11100, B11100, B11100, B11100, B11100, 28};
byte fourth[8]  = { B11110, B11110, B11110, B11110, B11110, B11110, B11110, 30};
byte full[8]    = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, 31};

void setup() {
  //CONFIGURATION
  pinMode(switchPin, INPUT);
  lcd.clear();
  lcd.begin(16,2);
  Serial.begin(9600);
  //LETTERS SETUP
  lcd.createChar(1, first);
  lcd.createChar(2, second);
  lcd.createChar(3, third);
  lcd.createChar(4, fourth);
  lcd.createChar(5, full);
}

void show_loading(int time) {
  time*=1000;
  time/=80;
  
  //PRINTING LETTERS
  lcd.setCursor(0,0);
  lcd.print("Progress: ");
    
  //PRINTING LOADING BAR AND THE PERCENTAGE
  float value=0;
  for (int j=0; j<=15; ++j) {
    lcd.setCursor(j,1);
    for (int i=1; i<=5; ++i) {
      lcd.setCursor(j,1);
      lcd.write(byte(i));
      delay(time);
      
      lcd.setCursor(10,0);
      value+=(((float)5)/4);
      lcd.print(value);

      if (value>=99.99) {
        lcd.setCursor(15,0);
      }
      lcd.print("%");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  show_loading(5); //NOTE: Input is in seconds
  delay(5000);
  lcd.clear();
}
