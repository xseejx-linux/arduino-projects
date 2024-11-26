#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;

// Bus //
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); // 16 x 2  
  lcd.setCursor(0,0);
  lcd.print("[+] TEMP: ");
  lcd.setCursor(0,1);
  lcd.print("[+] SP: ");
  // PIN MOTOR //
  pinMode(6,OUTPUT);
  
  Serial.begin(9600);
}

// Function to make Spaces on Display //
void Space(int space){
  for(int s = 0; s<space; s++){
    	lcd.print(" ");
    }
}
// Function to clear Display //
void Clear(){  
  for(int i = 0; i<16; i++){
    lcd.print(" ");
  }
}

// Variables //
int sp;
int temp;
int diff = 0;

// MAIN //
void loop(){  
  
  sp = analogRead(A0);
  temp = analogRead(A1);
  temp/=20;
  sp/=20;
  diff = temp-sp;
  // LCD //
  Clear();
  lcd.setCursor(9,0);	
  lcd.print(temp);
  Clear();
  lcd.setCursor(9,1);
  lcd.print(sp);
  
  analogWrite(6,(diff>0) ? ((diff*25>255) ? 255:diff*25):0);
  /*if(diff>0){
    	// Increase RMP Fan by 10%
        analogWrite(6,(diff*25>255) ? 255:diff*25);

  }else{
    	// Set RMP Fan to 0
    	analogWrite(6,0);
  }*/   
}
