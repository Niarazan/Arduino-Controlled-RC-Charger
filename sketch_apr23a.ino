
#define analogPin 0    // analog pin used to measure the voltage of the capacitor 
#define chargePin 13   // capacitor charging pin 
#define dischargePin 11   // capacitor discharge pin
#define ledChargingPin 4  // LED for capacitor charging
#define ledDisChargingPin 5  // // LED for capacitor discharging

unsigned long startTime;
unsigned long dischargeStartTime;
unsigned int readSensor;

void  setup () {
	pinMode (chargePin, OUTPUT );      // load set pin as output 
	digitalWrite (chargePin, LOW );  
        pinMode(ledChargingPin, OUTPUT);  // load LED Charging pin as output 
        digitalWrite (ledChargingPin, LOW );
        
        pinMode(ledDisChargingPin, OUTPUT);  // load LED DisCharging pin as output 
        digitalWrite (ledDisChargingPin, LOW );
        
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
		Serial.println ( millis () - dischargeStartTime); // print the elapsed discharging time 
  	pinMode (dischargePin, INPUT );             // set discharge pin as input (high impedance)

  	Serial.println ( "------------------------" ); // indicator for discharging completion

	digitalWrite (chargePin, HIGH );   // charge the capacitor 
	startTime = millis();            // start time 
	readSensor = analogRead (analogPin);   // read sensor
        digitalWrite(ledDisChargingPin, LOW);
        
	while (readSensor <900) {        // 1016 is the expected value at 5 TC 
                digitalWrite(ledChargingPin, HIGH);
                        
	    readSensor = analogRead (analogPin);   // read the sensor value
            //Serial.println (readSensor); 
  }
  Serial.print ("TIME for Charging ");
		Serial.println ( millis () - startTime);   // print the elapsed charging time 
		//Serial.print ( "sensor data after charging: " ); 
		//Serial.println (readSensor) ,  
  Serial.println ( "/////////////////////////////////////////" ); // indicator for charging completion

}
