int LightSrc [4] = {3, 2, 1, 0}; // The adress of the pins to which the photoresistor are connected
int preIndex, currentLength, preRead, counter;

const double UnitToMM = 1.0687; // For calibration later

int binPow ( int index ) // Our much better POW funciton
{
  int total = 1;
  for (int i = 0; i < index; i ++)
  {
    total *= 2;
  }
  return total;
}

int BinToDec ( int* lights ) // Binary to decimel decoder
{
  int currentTotal = 0;

  for ( int i = 0 ; i < 4; i ++ )
  {
    currentTotal += (lights[i] * binPow(i));//pow(2,i));
  }
  
  if (currentTotal == preRead)
  {
    counter ++;
    if(counter == 4){
      counter = 0;
      return currentTotal;
    }
  }
  if (currentTotal != preRead)
  {
    counter = 0;
  }
  preRead = currentTotal;
  return preIndex;
}

void setup() // The first run of the code, you may may want to raise the baud rate
{
  Serial.begin(9600); // This is where you change the rate, there are only certain values to pick from

  int Lights [4];
  for (int i = 0; i < 4; i ++) // The loop here gets the alanog ( raw ) values and if they are over 600 then the light is said to be "Seen"
  {
    int tempInt =  analogRead(LightSrc[i]);
    if (tempInt > 600 )
    {
      Lights [i] = 1;
    }
    else
    {
      Lights [i] = 0;
    }
  }
  preIndex  = BinToDec(Lights); // Set up the intial location
  preRead = preIndex;
  currentLength = 0; // yeah
}

void loop() // What runs and runs
{
  int Lights [4];
  int tempInt;

  for ( int i = 0; i < 4; i ++) // Same loop as above
  {
    tempInt =  analogRead(LightSrc[i]);
    if ( tempInt > 600)
    {
      Lights [i] = 1;
    }
    else
    {
      Lights [i] = 0;
    }
  }

  int currentIndex = BinToDec(Lights); // Gets the current location
  // Logic defining the meansuremnet logic

  if ( (preIndex < 3) && (currentIndex > 12))
  {
    currentLength -= (preIndex + (16 - currentIndex));
  }
  else if ( (preIndex > 12) && (currentIndex < 3))
  {
    currentLength += (currentIndex + (16 - preIndex));
  }
  else if ( currentIndex >= preIndex )
  {
    currentLength += currentIndex - preIndex;
  }
  else if ( currentIndex < preIndex)
  {
    currentLength -= preIndex - currentIndex;
  }
  
  //End of the forementioned logic




  //Debugging code
  Serial.println(currentLength * UnitToMM);
  //Will output if its 0 or 1
  //Serial.println(Lights[0]);
  //Serial.println(Lights[1]);
  //Serial.println(Lights[2]);
  //Serial.println(Lights[3]);
  Serial.println(currentIndex); // Outputs the current state
  Serial.println(preIndex);
  Serial.println();

  // Outputs the raw values
  /*Serial.println(analogRead(LightSrc[0]));
    Serial.println(analogRead(LightSrc[1]));
    Serial.println(analogRead(LightSrc[2]));
    Serial.println(analogRead(LightSrc[3]));
  */
  //Serial.println(preIndex);
  //Serial.println();
  //Serial.println(currentLength);
  preIndex = currentIndex;

  delay(50);

}