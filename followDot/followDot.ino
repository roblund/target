const int targetOne = 9;
const int targetTwo = 10;
const int targetThree = 11;
const int buzzerPin = 12;

int numLoops = 0;
int runFor = 12;
int currentRun = 0;
int prevRun = 0;
int duplicateCounter = 0;

void setup() 
{
  Serial.begin(9600);

  //initialize pins
  pinMode(targetOne, OUTPUT);
  pinMode(targetTwo, OUTPUT);
  pinMode(targetThree, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  //wait for 20 seconds
  delay(12000);
}

void loop() 
{  
  if(numLoops < runFor)
  {
    followDotMode();
  }
  else
  {
    soundBuzzer(2, 500);
    targetReset();
  }
}

void followDotMode()
{
  prevRun = currentRun;
  //will be truncated to int between 0 - 2
  currentRun = random(1, 30000) / 10000;

  Serial.println(currentRun);
  
  //check on duplicates
  if(prevRun == currentRun)
  {
    duplicateCounter += 1;
  }
  else
  {
    duplicateCounter = 0;
  }

  Serial.print("# dupes - ");
  Serial.println(duplicateCounter);

  //only update the target if we are below the max number of dupes 
  if(duplicateCounter < 2)
  {
    soundBuzzer(1, 0);
    Serial.println("Target Updated");
  
    if(currentRun == 1)
    {
      //just targetOne
      digitalWrite(targetOne, HIGH);
      digitalWrite(targetTwo, LOW);
      digitalWrite(targetThree, LOW);
    }
    else if(currentRun == 1)
    {
      //just targetTwo
      digitalWrite(targetOne, LOW); 
      digitalWrite(targetTwo, HIGH);
      digitalWrite(targetThree, LOW); 
    }
    else
    {
      //just targetThree
      digitalWrite(targetOne, LOW); 
      digitalWrite(targetTwo, LOW);
      digitalWrite(targetThree, HIGH);
    }
      
    //wait a random amount of time before cycling
    delay(random(1500, 2500));
    numLoops += 1;
  }
}

void soundBuzzer(int numberOfBuzzes, int interval)
{
  for(int i = 0; i < numberOfBuzzes; i++)
  {
    tone(buzzerPin, 4000, 400);
    delay(interval);
  }
}

void targetReset()
{
    //reset pins
    digitalWrite(targetOne, LOW);
    digitalWrite(targetTwo, LOW);
    digitalWrite(targetThree, LOW);
    
    numLoops = 0;
    currentRun = 0;
    prevRun = 0;
    duplicateCounter = 0;
    
    //wait for 20 seconds
    delay(12000); 
}

