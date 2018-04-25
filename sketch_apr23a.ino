
#define analogPin 0    // analog pin used to measure the voltage of the capacitor 
#define chargePin 13   // capacitor charging pin 
#define dischargePin 11   // capacitor discharge pin
#define ledChargingPin 4  // LED for capacitor charging
#define ledDisChargingPin 5  // // LED for capacitor discharging

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
unsigned long dischargeStartTime;
unsigned int readSensor;
float CurrentVoltage;

void  setup () {
	pinMode (chargePin, OUTPUT );      // load set pin as output 
	digitalWrite (chargePin, LOW );  
        pinMode(ledChargingPin, OUTPUT);  // load LED Charging pin as output       
        pinMode(ledDisChargingPin, OUTPUT);  // load LED DisCharging pin as output 
	Serial.begin (9600);              // initialize serial communication
}

void loop(){

	/* Discharge capacitor */ 
	digitalWrite (chargePin, LOW );             
	pinMode (dischargePin, OUTPUT );            
	digitalWrite (dischargePin, LOW );  
        dischargeStartTime = millis(); 
	//readSensor = analogRead (analogPin);   // read the sensor value
        //Serial.print ( "sensor data while discharging: " ); 
        //Serial.println (readSensor); 
        digitalWrite(ledChargingPin, LOW);
	while (readSensor> 0) {   // wait until the capacitor is fully discharged 
            digitalWrite(ledDisChargingPin, HIGH);
	   readSensor = analogRead (analogPin);   // read the sensor value
            //Serial.println (readSensor); 
	}
        Serial.print ("TIME for Discharge ");
        Serial.print( millis () - dischargeStartTime); // print the elapsed discharging time 
        Serial.println(" mS    "); 
  	pinMode (dischargePin, INPUT );             // set discharge pin as input (high impedance)

  	Serial.println ( "------------------------" ); // indicator for discharging completion

	digitalWrite (chargePin, HIGH );   // charge the capacitor 
	           
	readSensor = analogRead (analogPin);   // read sensor
        digitalWrite(ledDisChargingPin, LOW);
        startTime = millis(); // start time 
	while (readSensor < 648) {        // 648 is the expected value at 5 TC 
                digitalWrite(ledChargingPin, HIGH);
                        
	    readSensor = analogRead (analogPin);   // read the sensor value
            CurrentVoltage = (float(analogRead(analogPin))/1024.00)*5.0; //calculate the current voltage of the capacitor while charging
            Serial.print(CurrentVoltage);       // print the voltage to serial port
            
            Serial.println (" V "); 
  }
      elapsedTime= millis() - startTime;
      Serial.print ("TIME for Charging ");
      Serial.print( millis () - startTime);   // print the elapsed charging time 
      Serial.println(" mS    "); 
      
      microFarads = ((float)elapsedTime / 10000) * 1000; // calculate capacitance with the formula T = RC

      Serial.print (microFarads); 
      Serial.println (" uF") ,  
      Serial.println ( "/////////////////////////////////////////" ); // indicator for charging completion

}
