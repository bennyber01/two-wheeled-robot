const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

const int MAX_VALUE_FOR_SENSOR_POLLING_COUNTER = 20;
const int MAX_VALUE_FOR_SENSOR_CURRENT_COUNTER = 15;

// filter vars
int biggerValCounter = 0;
int smallerValCounter = 0;
int currentValCounter = 0;
int sensorPollingCounter = 0;
int sensorDataVariance = 3;
int returnVal = -1;
int waitCounterTime = 6;

float alpha = 0.7;

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

int isBigger(int v, int c, int delta)
{
  return v > c + delta;
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  if (returnVal < 0)
    returnVal = sensorValue;
  
  if (abs(sensorValue - returnVal) < sensorDataVariance)
    currentValCounter++;
  else if (sensorValue < returnVal)
    smallerValCounter++;
  else
    biggerValCounter++;

  sensorPollingCounter++;

  int isValBigger = isBigger(biggerValCounter, currentValCounter, sensorDataVariance);
  int isValSmaller = isBigger(smallerValCounter, currentValCounter, sensorDataVariance);
  int isUpdateVal = sensorPollingCounter > waitCounterTime && (isValBigger || isValSmaller);
  if (isUpdateVal)
  {
      returnVal = sensorValue * alpha + returnVal * (1.0 - alpha);
  }
  
  if (isUpdateVal || sensorPollingCounter > MAX_VALUE_FOR_SENSOR_POLLING_COUNTER || currentValCounter > MAX_VALUE_FOR_SENSOR_CURRENT_COUNTER)
  {
      biggerValCounter = 0;
      currentValCounter = 0;
      smallerValCounter = 0;
      sensorPollingCounter = 0;
  }

  if (1)
  {
    // print the results to the serial monitor:
    Serial.print("sensor = " );
    Serial.println(returnVal);                 
  }

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
