const int analog_pin = A0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

// Variables need for operation
const int avgSamples = 10; // Number of samples to average the reading over
int sensorValue = 0;
// gain = I_in/(V_measured - Vref) - Use power supply to get known I_in, then see what the V_measured is from the sensor 
float gain = -2.56; // For 100mA/250mV
// Output voltage with no current: ~ 2500mV, determine by reading measurement values when no current is passing
float Vref = 2469.28; 

void loop() {

   // Read multiple samples
   for (int i = 0; i < avgSamples; i++){
    sensorValue += analogRead(analog_pin);
    delay(5);
  }

  // Get average of readings
  sensorValue = sensorValue / avgSamples;
  
  // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV
  // The voltage is in millivolts
  float voltage = (4.88 * sensorValue);
 
  // This will calculate the actual current (in mA)
  // Using the Vref and configured
  float current = (voltage - Vref)*gain; // Current range is 10mA - 5A

  // Print values
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" mV");
  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" mA");
  
  sensorValue = 0; // Reset the sensor value for the next reading
  delay(500);
}
