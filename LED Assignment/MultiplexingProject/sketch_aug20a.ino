int R1 = 2;
int R2 = 3;
int R3 = 4;

int C1 = 5;
int C2 = 6;
int C3 = 7;

int currentCol = 0;
int currentRow = 0;
int current2Col = 0;
int current2Row = 0;

int thisRow = 0;
int thisCol = 0;
int this2Row = 0;
int this2Col = 0;

int breakToggle = 0;
int break2Toggle = 0;

const int row[3] = {
  2, 3, 4
};

const int col[3] = {
  8, 9, 10
};

int pixels[3][3]; // pixel matrix for refesher to turn on/off certain leds
int select[3][3]; // selector matrix for selecting
int loopX = 0;
int loopY = 0;
long me = 0;
int button1Pressed = 0; // make sure only button press is registered once
int button2Pressed = 0;

void setup() {
  Serial.begin(9600);
  digitalWrite(13, HIGH);
  
  for (int thisPin = 0; thisPin < 3; thisPin++) {
    // initialize the output pins
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins high to ensure that the LEDS are off
    digitalWrite(col[thisPin], HIGH);
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      pixels[x][y] = HIGH;
    }
  }

}

void loop() {
  if (digitalRead(13) == HIGH) {
   if(button1Pressed != 1){
    toggle();
    Serial.println("Button 1");
   }

   button1Pressed = 1;
  }
  else{
    button1Pressed = 0;
  }
  
  if (digitalRead(12) == HIGH) {
   if(button2Pressed != 1){
    turnOff();
    Serial.println("Button 2");
   }

   button2Pressed = 1;
  }
  else{
    button2Pressed = 0;
  }
  
  refreshScreen();
}


 void turnOff(){
  if(current2Row < 3){
    for(this2Row = 0; this2Row < 3; this2Row++){
      if(current2Col < 3){
        for (this2Col = 0; this2Col <3; this2Col++){
          if(pixels[this2Row][this2Col] == LOW) {
            Serial.println(pixels[this2Row][this2Col]);
            pixels[this2Row][this2Col] = 1;
            current2Col++;
            break2Toggle = 1;
            Serial.println("turning off");
            Serial.println(pixels[this2Row][this2Col]);
            break;
          }
        }
      }
      else{
        current2Col = 0;
        //toggle();
      }
      if(break2Toggle ==1) {
         break;
      }     
    }
    break2Toggle = 0;
  }
  else{
    current2Row = 0;
    toggle();
  }
 }


void toggle()
{
  if(currentRow < 3){
    for(thisRow = 0; thisRow < 3; thisRow++){
      if(currentCol < 3){
        for (thisCol = 0; thisCol <3; thisCol++){
          if(pixels[thisRow][thisCol] != LOW) {
            pixels[thisRow][thisCol] = LOW;
            currentCol++;
            breakToggle = 1;
            break;
          }
        }
      }
      else{
        currentCol = 0;
        //toggle();
      }
      if(breakToggle ==1) {
         break;
      }     
    }
    breakToggle = 0;
  }
  else{
    currentRow = 0;
    toggle();
  }
  //pixels[col][row] = !pixels[col][row];
}

void refreshScreen() {
  for (int thisRow = 0; thisRow < 3; thisRow++) {
    digitalWrite(row[thisRow], HIGH); // Turn on Row
    for (int thisCol = 0; thisCol < 3; thisCol++) {
      int thisPixel = pixels[thisRow][thisCol]; //Get what LED should be from array
      digitalWrite(col[thisCol], thisPixel); // Turns on LED
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH); // Turns LED off
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}

