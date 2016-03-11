int LightSrc [4] = {0,1,2,3}; // The adress of the pins to which the photoresistor are connected
int preIndex, currentLength;

const double UnitToMM = 1; // For calibration later

int binPow ( int index ) // Our much better POW funciton 
{
  int total = 1;
  for(int i = 0; i < index; i ++)
  {
    total *= 2;
  }
  return total;
}

int BinToDec ( int* lights ) // Binary to decimel decoder 
{
  int currentTotal = 0;
  
  for( int i = 0 ; i < 4; i ++ )
  {
    currentTotal += (lights[i] * binPow(i));//pow(2,i));
  }
  
  return currentTotal;
}

void setup() // The first run of the code, you may may want to raise the baud rate 
{
    Serial.begin(9600); // This is where you change the rate, there are only certain values to pick from 
    
    int Lights [4];
     for(int i = 0; i < 4; i ++) // The loop here gets the alanog ( raw ) values and if they are over 600 then the light is said to be "Seen"
     {
       int tempInt =  analogRead(LightSrc[i]);
       if(tempInt > 600 )
       {
          Lights [i] = 1; 
       }
       else
       {
          Lights [i] = 0; 
       }
     }
     preIndex  = BinToDec(Lights); // Set up the intial location 
     currentLength = 0; // yeah 
}

void loop() // What runs and runs
{
   int Lights [4]; 
   int tempInt;
   
   for( int i = 0; i < 4; i ++) // Same loop as above
   {
      tempInt =  analogRead(LightSrc[i]);
      if(tempInt > 600 )
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
   if( currentIndex > preIndex ) 
    {
      currentLength += currentIndex - preIndex;
    }
    else if ( preIndex == 15 && currentIndex < 5)
     {
       currentLength += currentIndex + 1 ;
     } 
    else if ( currentIndex < preIndex)
    {
      currentLength -= preIndex - currentIndex;
    }
 
     //End of the forementioned logic
     
     //Debugging code
   Serial.println(currentLength * UnitToMM);  
   //Will output if its 0 or 1 
   Serial.println(Lights[0]);
   Serial.println(Lights[1]);
   Serial.println(Lights[2]);
   Serial.println(Lights[3]);
   Serial.println(currentIndex); // Outputs the current state 

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
  
   delay(1000); // this is in milllisecond
}
