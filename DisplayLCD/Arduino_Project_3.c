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

// Function to make Spaces on Display //
void Space(int space){
  for(int s = 0; s<space; s++){
    	lcd.print(" ");
    }
}
// Not Used //
void Clear(){
  lcd.print(" ");
}

// if the number is not >10 it will print a 0 before it-->Ex.(01)
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

// Cursor Variable
int c = 0;

// Update The Time
void UpdateTime(){
  int Line = 1;
  int Col = 0;
  if(!Modify){
    // Mode = Normal Increasing of Time //
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
    // Mode = Modification of Time //
    if(Pointer == 1){
      lcd.setCursor(Col,Line);
      i=(i>=0 && i<23) ? i + 1:0;
      
      
    }else if(Pointer == 2){
      lcd.setCursor(Col+7,Line);
      j=(j>=0 && j<59) ? j + 1:0;
      
    }else if(Pointer == 3){
      lcd.setCursor(Col+10,Line);
      s=(s>=0 && s<59) ? s + 1:0;     
    }
  }
  
}
// For showing the cursor and the time during modifications 
void Modding(){
  int Line = 1;
  int Col = 0;
  c++;
      if(Pointer==1){
        
    	lcd.setCursor(Col+4,Line);        
          if(c%2==0){
            lcd.print("__");
            lcd.print(":");
          }else{
            lcd.setCursor(Col+4,Line);
            lcd.print(i/10);
            lcd.print(i%10);
            lcd.setCursor(Col+6,Line);
            lcd.print(":");
          }
        

      }else if(Pointer==2){
        
            lcd.setCursor(Col+4,Line);
            lcd.print(i/10);
            lcd.print(i%10);
            lcd.setCursor(Col+6,Line);
            lcd.print(":"); 
        
          if(c%2==0){
            lcd.setCursor(Col+7,Line);
            lcd.print("__");
            lcd.print(":");
          }else{
            lcd.setCursor(Col+7,Line);
            lcd.print(j/10);
            lcd.print(j%10);
            lcd.setCursor(Col+9,Line);
            lcd.print(":");
          }
      }else if(Pointer==3){
        	lcd.setCursor(Col+4,Line);
            lcd.print(i/10);
            lcd.print(i%10);
            lcd.setCursor(Col+6,Line);
            lcd.print(":");
        	lcd.setCursor(Col+7,Line);
            lcd.print(j/10);
            lcd.print(j%10);
            lcd.setCursor(Col+9,Line);
            lcd.print(":");     
        	if(c%2==0){
            	lcd.setCursor(Col+10,Line);
            	lcd.print("__");
            
       }else{
            lcd.setCursor(Col+10,Line);
            lcd.print(s/10);
            lcd.print(s%10);
            lcd.print(" ");
          }
  	  }
}

unsigned long previousTime = 0;
unsigned long previousTime1 = 0;
const unsigned long interval = 1000;// 1 second interval
const unsigned long cursorspeed = 100;// 0.1 seconds for cursor speed

void loop(){  
  unsigned long currentTime = millis();
  
  int Line = 1;
  int Col = 0;  
  
  // INIT LOOP //
  
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    // Update Time Every Second
    if(!Modify){
      // If not i Modification mode increase the time //
      if(i>=23 && j >= 59 && s >= 59){
        j++;
        i++;
      }
      s++;      
      UpdateTime();
    }
    
    
  }
  // For the Cursor Speed
  if (currentTime - previousTime1 >= cursorspeed) {
    previousTime1 = currentTime;
    // Update Time Every Second
    if(Modify){
      Modding();
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
