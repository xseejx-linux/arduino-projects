// C++ code

const int ROW = 10;
const int COL = 7;


int contatore = 0;
int valore = 1;




int P1 = 9; // Pin Pulsante
int P2 = 10;

int Led = 12;

bool ButtonPressed;
int E = 2;
int D = 3;
int C = 4;
int G = 5;
int F = 6;
int A = 7;
int B = 8; //E  D  C  G  F  A  B 

int N0[COL]={1, 1, 1, 0, 1, 1, 1};



int matrice[ROW][COL] = {{1, 1, 1, 0, 1, 1, 1},
		       {0, 0, 1, 0, 0, 0, 1},
               {1, 1, 0, 1, 0, 1, 1},
               {0, 1, 1, 1, 0, 1, 1},
               {0, 0, 1, 1, 1, 0, 1},
               {0, 1, 1, 1, 1, 1, 0},
               {1, 1, 1, 1, 1, 1, 0},
               {0, 0, 1, 0, 0, 1, 1},
		       {1, 1, 1, 1, 1, 1, 1},
		       {0, 1, 1, 1, 1, 1, 1}
  		       };


void setup()
{
  int j=2;
  for(int i=0; i<COL; i++){
  	pinMode(j, OUTPUT);
    j++;
    
  }
  
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(Led, OUTPUT);
  Serial.begin(9600);

}



const unsigned long interval = 1000; 
unsigned long previousMillis = 0;
int AddTime = 0; 
bool Counting = false;
int currentDigit = 0;
bool Event = false;


void Countdown() {
  if (currentDigit >= 0) {
    int l = 2; // Pin Number

    for (int j = 0; j < COL; j++) {
      digitalWrite(l, matrice[currentDigit][j]);
      l++;
    }
  } else {
    
  }
  if(currentDigit==0){
    // Countdown Reachs 0
    Event = true;
    AddTime = 0;
    
  }
}

void DisplayTime() {

  if (AddTime >= 0 && AddTime < ROW) {
  
    int l = 2; // Pin Number

    for (int j = 0; j < COL; j++) {
      digitalWrite(l, matrice[AddTime][j]);
      l++;
    }

    
  } else {
    AddTime = 0;
    
  }
}

void loop() {
  unsigned long currentMillis = millis();

  
  if (digitalRead(P1) == HIGH) {
    
    AddTime++;
    DisplayTime();
 	Counting = (Counting==true) ? false:false;
    Event = (Event==true) ? false:false;
    delay(100);  
  }

  if (digitalRead(P2) == HIGH) {
    
    currentDigit = AddTime;

    Counting = true;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    
    if (currentDigit > 0 && Counting == true) {
      currentDigit--;
      Countdown();
    } else {
      if(Counting){
        Counting = false;
      }       
    }
  }
  // Led Actives
  if(Event==true){
    digitalWrite(Led, true);
  }else{
    digitalWrite(Led, false);
  }
}









