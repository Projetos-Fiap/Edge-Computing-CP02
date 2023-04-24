#include <LiquidCrystal.h>

//CP02 - EDGE COMPUTING - 24-04-2023

// OBS: IF YELLOW LED & BUZZER ARE ON, TEMP AND/OR HUMIDITY
// ARE OUTSIDE IDEAL PARAMENTER (10-15C, 60-80%)

// Pin definitions
const int BUZZER_PIN = 10; 
const int GREEN_LED_PIN = 11; 
const int YELLOW_LED_PIN = 12; 
const int RED_LED_PIN = 13; 
const int LDR_PIN = A2;  
const int TEMP_SENSOR_PIN = A0;
const int HUMIDITY_SENSOR_PIN = A1;

// Light level thresholds
const int LDR_OK_LEVEL = 900; 
const int LDR_ALERT_LEVEL = 950;  

// Humidity level thresholds
const int HUM_OK_MIN_LEVEL = 60;
const int HUM_OK_MAX_LEVEL = 80;

// Temperature level thresholds
const float TEMP_OK_MIN_LEVEL = 10;
const float TEMP_OK_MAX_LEVEL = 15;

// LCD settings
const int RS = 9, EN = 8, DB4 = 5, DB5 = 4, DB6 = 3, DB7 = 2;
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

// Variables to store sensor readings
int ldrValue = 0;
int rawTempValue = 0;
int rawHumidityValue = 0;


// Variables to store measurements 
float humidityMeasurements[6] = {0,0,0,0,0,0};
float tempMeasurements[6] = {0,0,0,0,0,0};
float luminosityMeasurements[6] = {0,0,0,0,0,0};

// Variable to interact with millis() and change LCD information
int order = 0;

void setup() {
// Configure pins
pinMode(LDR_PIN, INPUT);
pinMode(GREEN_LED_PIN, OUTPUT);
pinMode(YELLOW_LED_PIN, OUTPUT);
pinMode(RED_LED_PIN, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);
  
// Turn off LEDs and buzzer
digitalWrite(GREEN_LED_PIN, LOW);
digitalWrite(YELLOW_LED_PIN, LOW);
digitalWrite(RED_LED_PIN, LOW);
noTone(BUZZER_PIN);
  
// Setup serial communication
Serial.begin(9600);
pinMode(HUMIDITY_SENSOR_PIN, INPUT);
  
// Initialize LCD
lcd.begin(16,2);
}





void loop() {
  int inicio = millis();
	while(true) { // Loop infinito 
  
  // Read sensor values
  ldrValue = analogRead(LDR_PIN);
  rawTempValue = analogRead(TEMP_SENSOR_PIN);
  rawHumidityValue = analogRead(HUMIDITY_SENSOR_PIN);
  
  // Convert temperature sensor value to Celsius
  float voltage = (rawTempValue / 1023.0) * 5000.0;
  float temperatureC = (voltage - 500.0) * 0.1;
  
  // Convert humidity sensor value to percentage
  int humidityPercentage = map(rawHumidityValue, 0, 1023, 10, 70);
  
      
  // Humidity measurements
  humidityMeasurements[int(humidityMeasurements[0])+1] = float(humidityPercentage);
    
  if(humidityMeasurements[0] < 4){
    humidityMeasurements[0]++;
  } else {
  	humidityMeasurements[0] = 0;	
  }
      
  // Temp measurements
  tempMeasurements[int(tempMeasurements[0])+1] = float(temperatureC);
  if(tempMeasurements[0] < 4){
    tempMeasurements[0]++;
  } else {
  	tempMeasurements[0] = 0;	
  }
      
  // luminosity measurements  luminosityMeasurements
  luminosityMeasurements[int(luminosityMeasurements[0])+1] = float(ldrValue);
  if(luminosityMeasurements[0] < 4){
    luminosityMeasurements[0]++;
    continue;
  } else {
  	luminosityMeasurements[0] = 0;	
  }  
                  
//////// S E R I A L  M O N I T O R ////////////      
      
  // Print sensor values to serial monitor
  Serial.print(" | Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print("C | Humidity: ");
  Serial.print(humidityPercentage);
  Serial.println("%");
      
/////// L E D  &  B U Z Z E R //////////////////      
  
  // Check light level and control LEDs
  if (ldrValue <= LDR_OK_LEVEL) {
    // Good light level -> Green led
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN); 
  }
  else if (ldrValue <= LDR_ALERT_LEVEL) {
    // Alert light level -> Yellow LED
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN); 
  }
  else {
    // Danger light level -> Red LED
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // Turn on buzzer 
  }
                   
   // If temperature isn't ideal, turn on yellow LED & Buzzer
   if (temperatureC < TEMP_OK_MIN_LEVEL || temperatureC > TEMP_OK_MAX_LEVEL) {
     digitalWrite(GREEN_LED_PIN, LOW);
     digitalWrite(YELLOW_LED_PIN, HIGH);
     digitalWrite(RED_LED_PIN, LOW);
     tone(BUZZER_PIN, 1000); 
   }

   // If humidity isn't ideal, turn on yellow LED & Buzzer
   if (humidityPercentage < HUM_OK_MIN_LEVEL || humidityPercentage > HUM_OK_MAX_LEVEL) {
     digitalWrite(GREEN_LED_PIN, LOW);
     digitalWrite(YELLOW_LED_PIN, HIGH);
     digitalWrite(RED_LED_PIN, LOW);
     tone(BUZZER_PIN, 1000); 
   }                       
  
///////////// L C D //////////////////////////      
      
  //Serial.print("order: "); 
  //Serial.println(order);
   int agora = millis();
  if(agora - inicio > 5000){
    Serial.print("order: "); 
  	Serial.println(order);
    if(order < 3){
    	order++;
    } else {
    	order = 0;
    }
    inicio = millis();       
  }
      
      
      if(order == 0) {  
        // Gets average light level
        float averageLight = (luminosityMeasurements[1] + luminosityMeasurements[2] + luminosityMeasurements[3] + luminosityMeasurements[4] + luminosityMeasurements[5])/5;
        // Prints light level to LCD
        if (averageLight <= LDR_OK_LEVEL) {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Light level: OK");
        }
        else if (averageLight <= LDR_ALERT_LEVEL) {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Light level:");
          lcd.setCursor(0,1);
          lcd.print("CAUTION");
        }
        else {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Light level:");
          lcd.setCursor(0,1);
          lcd.print("CRITICAL");
  		}
      }

      if(order == 1){
        // Gets average temperature level
        float tempAverage = (tempMeasurements[1] + tempMeasurements[2] + tempMeasurements[3] + tempMeasurements[4] + tempMeasurements[5])/5;
        
        // Prints temperature to LCD
        if (TEMP_OK_MIN_LEVEL <= tempAverage && tempAverage <= TEMP_OK_MAX_LEVEL) {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Temperature:");
          lcd.setCursor(0,1);
          lcd.print(tempAverage, 1);
          lcd.print("C  OK");
        }
        else {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Temperature:");
          lcd.setCursor(0,1);
          lcd.print(tempAverage, 1);
          lcd.print("C  ");
          if (tempAverage < TEMP_OK_MIN_LEVEL) {
            lcd.print("TOO LOW");
          }
          else {
            lcd.print("TOO HIGH");
          }
        }
      }

      if(order == 2) {
        // Gets Average humidity percentage
        float humidityAverage = (humidityMeasurements[1] + humidityMeasurements[2] + humidityMeasurements[3] + humidityMeasurements[4] + humidityMeasurements[5])/5;
        
      	// Prints humidity to LCD
        if (HUM_OK_MIN_LEVEL <= humidityAverage && humidityAverage <= HUM_OK_MAX_LEVEL) {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Humidity:");
          lcd.setCursor(0,1);
          lcd.print(humidityAverage, 1);
          lcd.print("%  OK");
        }
        else {
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Humidity:");
          lcd.setCursor(0,1);
          lcd.print(humidityAverage, 1);
          lcd.print("%  ");
          if (humidityAverage < HUM_OK_MIN_LEVEL) {
            lcd.print("TOO LOW");
          }
          else {
            lcd.print("TOO HIGH");
          }
        } 
      }

 } 
}
