/*Connection
   Sensor Pin A0
*/
/*LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 7
   LCD D5 pin to digital pin 6
   LCD D6 pin to digital pin 5
   LCD D7 pin to digital pin 4
*/

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define sensorPin A0
int phase[3] = {8, 9, 10};
int lcdC[4] = {1, 3, 4, 1};
int lcdB[4] = {8, 11, 12, 0};
int lcdA[4] = {0, 3, 4, 0};

//*********************************************************
int calcDistance(int sensorValue) {
  if (sensorValue >= 890 && sensorValue < 920) {
    return 8;
  }
  else if (sensorValue >= 850 && sensorValue < 890) {
    return 6;
  }
  else if (sensorValue >= 750 && sensorValue < 850) {
    return 4;
  }
  else if (sensorValue >= 600 && sensorValue < 750) {
    return 2;
  }

  else return 0 ;

}
//*********************************************************

void scanPhase (int phaseIndex, int lcdArray[4], int faultDistanceValue) {
  digitalWrite(phase[phaseIndex], HIGH);
  delay(500);

  if (faultDistanceValue == 0) {
    lcd.setCursor(lcdArray[0], lcdArray[3]);
    lcd.write("R: ");
    lcd.setCursor(lcdArray[1], lcdArray[3]);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(lcdArray[0], lcdArray[3]);
    lcd.write("R: ");
    lcd.setCursor(lcdArray[1], lcdArray[3]);
    lcd.print(faultDistanceValue);
    lcd.setCursor(lcdArray[2], lcdArray[3]);
    lcd.write(" KM");
  }
  digitalWrite(phase[phaseIndex], LOW);

}

//*********************************************************
void setup() {
  // set pin mode for three phase relays
  for (int j = 0; j < 3; j++) {
    pinMode(phase[j], OUTPUT);
  }
  Serial.begin(9600); //sets serial port for communication
  lcd.begin(16, 2);
  lcd.print("UNDERGROUND CABLE");
  lcd.setCursor(0, 1);
  lcd.print("FAULT LOCATOR");
  delay(1000);
  delay(1000);
  lcd.clear();
}



void loop()
{
  
  int faultDistance = calcDistance(analogRead(A0));         //scan Red line
  scanPhase (0, lcdA, faultDistance);

  
  int faultDistance1 = calcDistance(analogRead(A0));        //scan Yellow line
  scanPhase (1, lcdA, faultDistance1);


  
  int faultDistance2 = calcDistance(analogRead(A0));        //scan Green line
  scanPhase (2, lcdA, faultDistance2);

}
