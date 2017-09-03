unsigned long timePressed, timeReleased, timeHeld; // time variables to record ampunt of time pressed
int inputPin = 2;                       // button reading pin
int ledPin = 4;                         //led output pin
String code =  "";
void setup() {
  Serial.begin(9600);      // serial monitor initialize
  pinMode(inputPin,INPUT_PULLUP);
  
  
  pinMode(ledPin, OUTPUT);
 
}
// determines based on the amount of tome the button is pressed whether the input was a dot or dash
char readDotDash(){
  if (timeHeld >50 && timeHeld < 600) { // if the pressing time is less than half a second
                                        // return a dot
    return '.';
  }
  else if (timeHeld > 600){                  // if pressing time is more, return a dash
  return '-';
}

}



void DotDashToLetters() // takes the strings to dots and dash and converts it to letters based on morse code
{
  int i = 0;
 
  static String morseAlphabet[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
                            }; // array of letters in morse representation, 0th element is error
                              // 0th element  is 'A', 1st element is 'B', 2nd is 'C' etc
                            
     String period  = ".-.-.-" ;// period/Full Stop in morse code 

     if (code  == period){
      Serial.print (".");
      
     }

     else {
        while (morseAlphabet[i] != "E")  //E is the last element, iteratign throught the array
                                  // to find a match for input 
    {
      if (morseAlphabet[i] == code)
      {
        Serial.print(char(65 + i)); // converts ith element of array and prints corresponding
                                    // ascii character
        break;
      }
      i++;
    }
    if (morseAlphabet[i] == "E")
    {
      Serial.println("(Unable to Read)");  //if input code doesn't match any letter, error
    }
      
     }
     code = ""; // reset to blank string
          
}


void loop() {
  NextDotDash:
  while (digitalRead(inputPin) == HIGH) {}
  timePressed = millis();                            //time at button press
  digitalWrite(ledPin, HIGH);               //LED on while button pressed
  while (digitalRead(inputPin) == LOW) {}
  timeReleased = millis();                            //time at button release
  digitalWrite(ledPin, LOW);                //LED off on button release
  timeHeld = timeReleased - timePressed;                     //time for which button is pressed
  if (timeHeld > 50)                      //to account for switch debouncing
  {
    code += readDotDash();                       //function to read dot or dash
  }
  while ((millis() - timeReleased) < 500)           //if time between button press greater than 0.5sec, skip loop and go to next alphabet
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextDotDash;
    }
  }
  DotDashToLetters();
  

}
