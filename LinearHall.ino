/* Michael Le
 * Tachometer using Arduino and Linear Hall Sensor that tracks speed of rotating magnetic object
 */

#include <LiquidCrystal.h> //Includes the code for LCD

//Declaration of Arduino ports used
const int hall_Sensor = A0;
int led = 6;

//Declaration of ports used for LCD
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Declaration of global variables
double inputVal = 0;
double time;
double rpm;
double oldtime = 0;
int count = -2;
double totaltime = 0;
int detection = 0;

//Calibrating the initial voltage outputted by the linear hall sensor
double initialVoltage = 2.68;
double max = initialVoltage + 0.02;
double min = initialVoltage - 0.02;

void setup() 
{ 
  //Defining ports as input or output               
  pinMode(led, OUTPUT);
  pinMode(hall_Sensor,INPUT);

  //Starts output stream on serial and lcd
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() 
{
  //Delay of 100 milliseconds before next detection
  delay(100);

  //If voltage outputted by linear hall is not in the initial range
  if ((inputVal < min) || (inputVal > max)) {
    
    count++; //Used to ensure only the first detection in a rotation is used to track rpm

    //If the first detection of a rotation is detected, start timer for rotation. Then print the time elapsed since last detection. Then saves the new time.
    if (count == 1) {
      time = millis() - oldtime;
      totaltime = (time + oldtime) / 1000;
      detection++;
      rpm = 60000/time;

      //Printing for LCD
      lcd.setCursor(0, 0);
      lcd.print("RPM: ");
      lcd.print(rpm);
      lcd.setCursor(0, 1);
      lcd.print("Time(ms): ");
      lcd.print((int)time);
      
      oldtime = millis();

      //Output for easy analysis
      Serial.print(detection);
      Serial.print(" ");
      Serial.print(totaltime);
      Serial.print(" ");
      Serial.println(rpm);
    }

    //Outputs detection the form of led light blinking
    digitalWrite(led, HIGH);
    delay(25);
    digitalWrite(led, LOW);
    delay(25);
  }

  //If the voltage passed through is normal, reset the count back to 0
  if ((inputVal < max) && (inputVal > min)) {
    count = 0;
  }

  //Converts the voltage passed through and printed on serial
  inputVal = (analogRead(hall_Sensor)) / 1024.0 * 5.0; 
  Serial.println(inputVal);
}
