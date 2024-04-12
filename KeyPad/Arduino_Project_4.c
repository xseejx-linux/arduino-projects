// C++ code
#include <Keypad.h>

const int ROW = 4;
const int COL = 4;

const int LEN = 5;

// Keypad MAP //

char Keys[ROW][COL] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROW]={9, 8, 7, 6};
byte colPins[COL]={5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROW, COL);

void setup(){
  Serial.begin(9600);
}

int count = 5;
char pwd[5];
int digits = 0;
bool Check = false;

char pass[LEN] = {'1', '2', '3', '4', '5'};

bool strcmp(char v[]){
  for(int i = 0; i<LEN; i++){
    if(pass[i]!=v[i]){
      return false;
    }
  }
  return true;
}

void print(char v[], int co){
  for(int i = 0; i<co; i++){
    Serial.print('*');
  }
}
  
void loop(){
  if(count==0){
    Serial.println("THE VAULT WILL REMAIN LOCKED");
    return;
  }
  if(Check){
    Serial.println("THE VAULT IS OPEN");
    return;
  }
 
  char key = keypad.getKey();
  if((key and digits<=5) and (key !='#' or key!='*') ){
    if(key=='*' and digits>0){
    	pwd[digits-1]=8;
      	digits--;
      	Serial.println("/");
      	print(pwd, digits);
    }else if(key!='#' and key!='*'){      
      Serial.print('*');
      pwd[digits]=key;
      digits++;
    }
    
  }
  if(digits==5 and key == '#'){
    digits = 0;
    if(strcmp(pwd)){
      Serial.println("/");
      Serial.println("CORRECT");
      Check=true;      
      return;
    }else{
      count--;
      Serial.println("/");
      Serial.print("!NOT CORRECT!   ");    
      Serial.print(count);
      Serial.println(" attempts remains");
    }
  }else if(digits>5 and key!='#'){
    digits = 0;
  	Serial.println("/");
    Serial.println("!NOT CORRECT!   ");
  }
}
