// C++ code

#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;

// Bus 
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

const int P1 = 6;
const int P2 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); // 16 x 2
  
  // INIT //
  lcd.print(" << HH:MM:SS >> ");
  lcd.setCursor(0,1);
  lcd.print("    00:00:00  ");
  
  pinMode(P1, INPUT);
  pinMode(P2, INPUT); 
  
  Serial.begin(9600);
}


void Space(int space){
  for(int s = 0; s<space; s++){
    	lcd.print(" ");
    }
}

void Clear(int Line, int Col){
  lcd.setCursor(Col, Line);
  for(int j = 0; j<16; j++){
     lcd.print(" ");
  }
}

void SetZero(int p){
  if(p<10){
      lcd.print("0");
   }
}


// Buttons Variables
// P2 Button
int val = 0;
int count = 0;
int Pointer = 0;
// P1 Button
int valP1 = 0;
bool Modify = false;

// Time Variables
int i = 0;
int j = 0;
int s = 0;

void UpdateTime(){
  int Line = 1;
  int Col = 0;
  if(!Modify){
      if(i<24){
      lcd.setCursor(Col,Line);
      Space(4);
      SetZero(i);
      lcd.print(i);
      lcd.print(":");
      }else{
      i = 0;
      lcd.setCursor(Col,Line);
      Space(4);
      SetZero(i);
      lcd.print(i);
      lcd.print(":");
      }
      if(j < 60){
      lcd.setCursor(Col+7,Line);
      SetZero(j);
      lcd.print(j);
      lcd.print(":");
      }else{
      i++;
      j = 0;
      lcd.setCursor(Col+7,Line);
      SetZero(j);
      lcd.print(j);
      lcd.print(":");
      }
      if(s<60){
      lcd.setCursor(Col+10,Line);
      SetZero(s);
      lcd.print(s);
      }else{
      j++;
      s = 0;
      lcd.setCursor(Col+10,Line);

      SetZero(s);
      lcd.print(s);
      }
  }else{
    if(Pointer == 1){
      lcd.setCursor(Col,Line);
      i=(i>=0 && i<23) ? i + 1:0;
      Space(4);
      SetZero(i);
      lcd.print(i);
      lcd.print(":");
    }else if(Pointer == 2){
      lcd.setCursor(Col+7,Line);
      j=(j>=0 && j<59) ? j + 1:0;
      SetZero(j);
      lcd.print(j);
      lcd.print(":");
    }else if(Pointer == 3){
      lcd.setCursor(Col+10,Line);
      s=(s>=0 && s<59) ? s + 1:0;
      SetZero(s);
      lcd.print(s);
    }
  }
  
}

unsigned long previousTime = 0;
const unsigned long interval = 1000; // 1 second interval

void loop(){  
  unsigned long currentTime = millis();
  
  int Line = 1;
  int Col = 0;  
  
  // INIT LOOP //
  
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    // Update Time Every Second
    if(!Modify){
      s++;
      UpdateTime();
    }
    
  }

  // Button P2 [Controller]
  if (digitalRead(P2) && val == 0) {
    val = 1;
    count++;
    if(count%2!=0){
      Modify = true;
    }else{
      ;
    }
    if(Modify){
      Pointer=(Pointer>=0 && Pointer<3) ? Pointer + 1:0;
      Serial.println(Pointer);
      if(Pointer == 0){
        Modify = false;
      }
    }
  }else if(digitalRead(P2)==false){
        val=0;
  }
  
  // Button P1 [Increament]
  if (digitalRead(P1) && valP1 == 0) {
      valP1 = 1;    
      UpdateTime();

  }else if(digitalRead(P1)==false){
        valP1=0;
  }  
}
