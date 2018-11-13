#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//later vervangen door password van monitor
char keyCode[] = {'1', '2', '3', '8'}; //hard coded password

//user input
char keyInput[] = {'0', '0', '0', '0'};
String keyInput2;
String password = "0000";
int keyCount = 0;//counter key input from pad
bool correct = false;
bool enterNewPassword = false;
String newPassword = "";
String input = "testttt";
String hexpad = "hexpad";
String reset = "reset";
bool hexpadOn = false;

int led1 = 10; // Green led
int led2 = 11; // Orange led
int led3 = 12; // Red led



byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void Hexpad()
{
  char key = keypad.getKey();
  // Serial.println("hij komt wel bij hexpad buiten de loop.");

  if (key)
  {
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led3, HIGH);
    //Serial.println(key);        //laat zien op monitor
    keyInput[keyCount] = key; //
    keyCount++;                   //add to count
    keyInput2 = keyInput2 + key;  //add input to string
    Serial.println(keyInput2);    //input string

    if (keyInput2 == password)
    {
      correct = true;
    }
    else
    {
      correct = false;
    }


    if (keyCount == 4)
    {
      if (correct == true)
      {
        Serial.println("Password correct! Welcome!");
        correct = false;
        keyCount = 0;
        keyInput2 = "";
        digitalWrite(led1, HIGH); //turn on 1 (green)
        digitalWrite(led2, LOW); //turn off orange
        digitalWrite(led3, LOW); //turn off red
      }
      else
      {
        Serial.println("Password incorrect. Please try again.");
        keyCount = 0;
        keyInput2 = "";
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led3, LOW);
        delay(100);
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led3, LOW);
        delay(100);
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led3, LOW);
        delay(100);
        digitalWrite(led3, HIGH);
      }
    }
    if (keyCount != 0 && keyCount < 4)
    {

      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
    }
  }


}

void ResetPassword()
{
  Serial.println("Password erased. Please enter a new password.");
  String password = "";
  NewPassword();
}

void NewPassword()
{
  enterNewPassword = true;
  char key = keypad.getKey();
}

void Invalid()
{
  Serial.println("Invalid input. Please try again.");
}



void setup()
{

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led2, HIGH); //turn on 2 (orange) always.

  Serial.begin(9600);
  // welcome message
  Serial.println("Welcome.");
  delay(1000); // wait 1 seconds
  Serial.println("Type 'hexpad' to use this device.");
  delay(500); // wait 1/2 second
  Serial.println("or");
  delay(1000); // wait 1 seconds
  Serial.println("Type 'reset' to change the password.");
}

void loop()
{
  while (Serial.available() == 0)
  { } //wait

  input = Serial.readString(); //store input string

  Serial.println(input);


  //Hexpad();

  if (input == hexpad)
  {
    hexpadOn = true;
    Serial.println("You can now access the hexpad.");
  }
  else if (input == reset)
  {
    ResetPassword();
    hexpadOn = false;
  }
  else
  {
    hexpadOn = false;
  }

  while (hexpadOn)
  {
    Hexpad();
  }

  if (enterNewPassword)
  {
    while (Serial.available() == 0)
    { }   // wait
    newPassword = Serial.readString();
    password = newPassword;
    enterNewPassword = false;
    hexpadOn = true;
    Serial.println("New password has been set.");
    delay(1500);
    Serial.println("Type 'hexpad' to use this device.");
     while (Serial.available() == 0)
    { }   // wait
  }

}
