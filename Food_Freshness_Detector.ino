#include "ph_grav.h"                       
#include "LiquidCrystal.h" 

#define moisture_pin A0
#define gas_pin A1
#define Gravity_pH A3

String inputstring = "";                              
boolean input_string_complete = false;                
char inputstring_array[10];                                                            

void setup() {
  Serial.begin(9600);          
  pH.begin();
}

void loop() {

/*******************moisture sensor******************/

  int moisture_value = analogRead(moisture_pin);
  Serial.print("M: ");
  Serial.print(moisture_value);
  Serial.print("\t");
  
/****************************************************/
/*******************GAS sensor***********************/

  int gas_value = analogRead(gas_pin);  
  Serial.print("G: ");
  Serial.print(gas_value);  
  Serial.print("\t");
  
/****************************************************/
/*******************PH sensor************************/

  if (input_string_complete == true) {                
    inputstring.toCharArray(inputstring_array, 30);   
    parse_cmd(inputstring_array);                     
    input_string_complete = false;                    
    inputstring = "";                                
  }
  Serial.print("pH: ");
  Serial.println(pH.read_ph());    
                                           
/****************************************************/
  delay(100);
}

void serialEvent() {                            
  inputstring = Serial.readStringUntil(13);           
  input_string_complete = true;                       
}

void parse_cmd(char* string) {                  
  strupr(string);                                  

  if (strcmp(string, "CAL,4") == 0) {               
    pH.cal_low();                                   
    Serial.println("LOW CALIBRATED");
  }
  else if (strcmp(string, "CAL,7") == 0) {          
    pH.cal_mid();                                   
    Serial.println("MID CALIBRATED");
  }
  else if (strcmp(string, "CAL,10") == 0) {         
    pH.cal_high();                                 
    Serial.println("HIGH CALIBRATED");
  }
  else if (strcmp(string, "CAL,CLEAR") == 0) {     
    pH.cal_clear();                                 
    Serial.println("CALIBRATION CLEARED");
  }
}
