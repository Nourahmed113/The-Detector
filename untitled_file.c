#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define outPin 8
#define s0 9
#define s1 10
#define s2 11
#define s3 12


// Variables
int red, grn, blu;
String color ="";


void setup(){
  Serial.begin(9600);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); //out from sensor becomes input to arduino

  // Setting frequency scaling to 100%
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor (3,0);
  lcd.print("Welcome To");
  lcd.setCursor (1,1);
  lcd.print("Color Detector");
  delay(2000);  
  lcd.clear();  
}

void loop(){
  getColor();
   printData();
   showDataLCD();
}

/* read RGB components */
void readRGB(){
  red = 0, grn=0, blu=0;
  
  int n = 10;
  for (int i = 0; i < n; ++i){
    //read red component
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
  
   //read green component
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    
   //read blue component
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red/n;
  grn = grn/n;
  blu = blu/n;
}

/*****************
* Showing captured data at Serial Monitor
******************/
void printData(void){
  Serial.print("red= ");
  Serial.print(red);
  Serial.print("   green= ");
  Serial.print(grn);
  Serial.print("   blue= ");
  Serial.print(blu);
  Serial.print (" - ");
  Serial.print (color);
  Serial.println (" detected!");
}

///*****************
//* Showing capured data at LCD
//******************/
void showDataLCD(void){
lcd.clear();
lcd.setCursor (0,0);
lcd.print("R");
lcd.print(red);
lcd.setCursor (6,0);
lcd.print("G");
lcd.print(grn);
lcd.setCursor (12,0);
lcd.print("B");
lcd.print(blu);  

lcd.setCursor (0,1);
lcd.print("Color: ");  
lcd.print(color);  
}



void getColor(){  
  readRGB();

     if(red>9  && red<15  && grn>20 && grn<23 && blu>15 && blu<18) color = "RED";
//else if(red>16 && red<29  && grn>20 && grn<24 && blu>19 && blu<24) color = "ORANGE";
else if(red>17 && red<20  && grn>16 && grn<20 && blu>15 && blu<19) color = "GREEN";
else if(red>12 && red<15  && grn>14 && grn<17 && blu>12 && blu<16) color = "BEIGE";
else if(red>11 && red<14  && grn>9 && grn<12 && blu>7 && blu<9) color = "DARKGREEN";
else if(red>21 && red<27  && grn>17 && grn<20 && blu>10  && blu<14) color = "BLUE";
else if(red>9 && red<13   && grn>11  && grn<15 && blu>13  && blu<16) color = "YELLOW";
else if(red>10  && red<14 && grn>11  && grn<15  && blu>7  && blu<12)  color = "WHITE";
else if(red>22 && red<26 && grn>22 && grn<26 && blu>17 && blu<20) color = "BLACK";
else  color = "NO_COLOR";
}