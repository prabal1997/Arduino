
#include<LiquidCrystal.h>

//OBJECT CREATION
LiquidCrystal lcd(12,11,5,4,3,2);
const int switchPin=6;
int j=0;
signed int i=0;
byte happy[8]     = { B00000, B01010, B00000, B00000, B10001, B01110, B00000 };
byte sad[8]       = { B00000, B01010, B00000, B00000, B01110, B10001, B00000 };
byte tick[8]      = { B00000, B00000, B00001, B10010, B10100, B11000, B10000 };
byte cross[8]     = { B10001, B10001, B01010, B00100, B01010, B10001, B10001 };
byte template1[8]
={
B00100,
B01100,
B01100,
B01100,
B01110,
B11111,
B11111
};
//byte template2[8] = { B00000, B00000, B00001, B10010, B10100, B11000, B10000 };
//byte template3[8] = { B10001, B10001, B01010, B00100, B01010, B10001, B10001 };

//CONFIGURATION
String input_data=""; //USE ESCAPE CHARACTERS TO ACCESS LETTERS I.E \1 WILL PRINT 'HAPPY' ICON (WARNING: \0 DOES NOT PRINT ANYTHING!)
const int PRINT_DELAY=15;

void setup() {
  pinMode(switchPin, INPUT); 
  lcd.createChar(1, happy);
  lcd.createChar(2, sad);
  lcd.createChar(3, cross);
  lcd.createChar(4, tick);
  lcd.createChar(5, template1);
//  lcd.createChar(6, template1);
//  lcd.createChar(7, template1);
  lcd.clear();
  lcd.begin(16,2);
  Serial.begin(9600);
}

//DATA-PRINTING
void print_lcd(String& input) {
static int counter=0;
  lcd.setCursor(0,0);
  input.trim();
  //EXCEPTION HANDLING FOR WHEN A BLANK INPUT IS RECEIVED
  if (input=="") {
    input=" ";
  }
  for (j=0; j<=(input.length()/16); ++j) {
    
    //CHOOSING APPROPRIATE ROW TO PRINT ON
    if ((j%2)==0) {
      lcd.clear();
      lcd.setCursor(0,0);
    }
    else {
      lcd.setCursor(0,1);
    }
    //FIRST PART OF THE 'FOR LOOP'
    i=0;
    
     if(input[(j*16)+i]==' ') {
      ++i;
      }
    
    //SECOND AND THIRD PART OF THE 'FOR LOOP'
    for (; i<= ((j==(input.length()/16))?((input.length()%16)-1):(15)) ; ++i) {
      //CHECKING FOR SPECIAL SYMBOLS
      if (input[(j*16)+i]=='|') {
        i+=1;
        if (input[(j*16)+i]=='1') {
          lcd.print('\1');
        }
        else if (input[(j*16)+i]=='2'){
          lcd.print('\2');
        }
        else if (input[(j*16)+i]=='3') {
          lcd.print('\3');          
        }
        else if (input[(j*16)+i]=='4') {
          lcd.print('\4');
        }
        else if (input[(j*16)+i]=='5') {
          lcd.print('\5');
        }
  //      else if (input[(j*16)+i]=='6') {
  //        lcd.print('\6');
  //      }
  //      else if (input[(j*16)+i]=='7') {
  //        lcd.print('\7');
  //      }
      }
      else {
      //PRINTING NORMAL TEXT
      lcd.print(input[(j*16)+i]);
    }
  delay(PRINT_DELAY);
  }
 }
}

void loop() {
  
  static int repeat=0;
  
  //RECEVING INPUT FROM THE SERIAL
  while(Serial.available()) {
    input_data+=(char)Serial.read();
  }
  
  //PRINTING DATA
  if(!Serial.available()) {
    if(input_data!="") {
      Serial.print(input_data);
      Serial.print("\n");
      print_lcd(input_data);
    }
  }
  input_data="";
  
  delay(3000);
}

