#include <Wire.h>
#include <Keypad.h>
int order =0;
int ingame =0;
int button1Pin = 10; //The SW1 button is connect to pin 2 of the Arduino.
char key = '0';
byte y = 0;
int score=0;
int randomnumber;
char num;
char password[5];
int passwordcheck;
byte x =0;
int rotationPin = A1;//Rotation dial is connected to pin A1 of the arduino.
int buzzerPin =11;

/*
The keypad setup I used was from:
Pattabiraman, K. (2023, April 28). How to set up a keypad on an Arduino. Circuit Basics. 
https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/ 
with a few modifications to the some of the variable names
*/

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
Wire.begin(5); // join i2c bus (address optional for master)
Wire.onReceive(receiveEvent); // register event
randomSeed(analogRead(0));// sets a seed for my RGB LED light show  
Serial.begin(9600);//start the serial monitor
pinMode(rotationPin,INPUT);//setup the rotation dial as an input
pinMode(button1Pin, INPUT); //Setup button1 pin as an input pin.
pinMode(buzzerPin, OUTPUT); //Setup red LED pin as an output pin.
}

void loop(){ 
  start();//start up function
}

void start(){//start function
   order = 0;//make order 0
  passwordcheck =0;//make passwordcheck 0
  ingame =0;//make ingame 0
   delay(250);//delay 250 milliseconds
while(order ==0){//while order is 0
  Serial.println("Hit The Power Button To Start");// print a startup message
  order = 1;//make order 1
  }
 while(order == 1){//while order is 1
if (digitalRead(button1Pin)==HIGH){// make the buttons on the remote work
  Wire.beginTransmission(4); // transmit to device #4
  x++; //add one to x 
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  menu1();// menu 1 function 
	}
  }
}
  
void menu1(){//menu 1 function
  order=2;//make order 2 
  Serial.println("Welcome To Ty's Bomb Shop");//print a simple menu
 Serial.println("In This Shop We Have Two Difficulties");
   Serial.println("Please Select One Of These Options Using The Keypad");
   Serial.println("1. Easy Mode");
  Serial.println("2. Medium Mode");
    while(order==2){//while order is 2
     key = keypad.getKey();//make key the keypads value
   if (key == '4' || key == '5' || key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'|| key == '*'|| key == '#'){
  Serial.println("Invaild Input Please Try Again!");//if any other key is pressed say its invalid
     menu1();//loop the menu
  }
  else if(key == '1'){//if 1 is pressed 
  order = 3;//make order 3
  Easy();//go to easy function
  }else if(key == '2'){//if 2 is pressed 
    order = 4;//make order 4 
  Medium();//go to Medium function
  }
   Powerdown();//powerdown function
  }
}

void Easy(){//Easy Function Print a simple menu
Serial.println("Welcome to Easy Mode");
Serial.println("Have you Played This Before?");
Serial.println("Please Pick One Of The Options Below Using The Keypad!");
Serial.println("1.Yes");
Serial.println("2.No");
 while(order == 3){//while order is 3 
   Powerdown();//Powerdown function
  key = keypad.getKey();//make key equal to the keypad inputs
   if (key == '3'|| key == '4' || key == '5' || key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'|| key == '*'|| key == '#'){
  Serial.println("Invaild Input Please Try Again!");// if key is not 1 or 2 tell user its invalid
    Easy();//loop easy menu
  }else if(key == '1'){//if key is one 
 order=6;//make order 6
     Wire.beginTransmission(4); // transmit to device #4
  x++; //add to x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
   ingame =1;//make ingame 1
     EasyGame();//Easy Game function
  }else if(key == '2'){//if key is 2
     order=5;//make order 5
  EasyGameDescription();//Easy Game Description 
  }
 }
}

void Medium(){//Medium function, print a simple menu
Serial.println("Welcome to Medium Mode");
Serial.println("Have You Played This Before?");
Serial.println("Please Pick One Of The Options Below Using The Keypad!");
Serial.println("1.Yes");
Serial.println("2.No");
  while(order == 4){//while order is 4
    Powerdown();//Powerdown function	
  key = keypad.getKey();//make key equal to keypad input
  if (key == '3' || key == '4' || key == '5' || key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'|| key == '*'|| key == '#'){
  Serial.println("Invaild Input Please Try Again!");// if key is anything other than 1 or 2 tell user its invalid 
     Medium();//loop the Medium 
  } else if(key == '1'){// if key is 1 
 order=7;//make order 7
      Wire.beginTransmission(4); // transmit to device #4
  x++; //add to x
  x++;//add to x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
   MediumGame();//Medium Game function
  }else if(key == '2'){//if key is 2
     order=8;//make order 8
  MediumGameDescription();//MediumGameDescription function
  }
 }
}

void EasyGameDescription(){// EasyGameDescription function, print a simple description of the game
Serial.println("Welcome to Your First Bomb Defusal!");
Serial.println("Your Goal Is To Stop The Bomb Before It Goes Off");
Serial.println("To Do That You Must Read The Password That Is Given To You On The Monitor");
Serial.println("And You Have To Enter The Password Into The Keypad Before Time Runs Out");
Serial.println("Do You Understand?");
Serial.println("1.Yes");
Serial.println("2.no");
  while(order==5){//while order is 5 
    Powerdown();//powerdown function
    key = keypad.getKey();//make key equal to the keypad's input
   if (key == '3'|| key == '4' || key == '5' || key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'|| key == '*'|| key == '#'){
  Serial.println("Invaild Input Please Try Again!");//if user pressed anything other than 1 or 2 tell them it was an invalid input
    EasyGameDescription();//loop the function
  } else if(key == '1'){//if key is 1
      order=6;//make order 6
  Wire.beginTransmission(4); // transmit to device #4
  x++; //add 1 to x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
      ingame =1;//make ingame 1
    EasyGame();//Easygame function
    } else if(key== '2'){//if key is 2
    EasyGameDescription();//loop the Description
    }
  }
}

void EasyGame(){//Easy game function
Serial.println("In Easy Game");//tell user they are in game
  while(order==6){//while order is 6
   makepassword();//makepassword function
    Serial.print("Your Password is: ");//print what their password is 
    Serial.print(password[0]);
      Serial.print(password[1]);
      Serial.print(password[2]);
      Serial.print(password[3]);
      Serial.println(password[4]);
     while(ingame ==1){//while ingame is 1
      key = keypad.getKey();//make key equal to keypad
    if (key == password[0]){//if key equals password 1
     passwordcheck = 1;//make passwordcheck 1
      while (passwordcheck==1){//while passwordcheck is one
         if(y==1){//if y is 1 
       Endgame();//Endgame function
       }
        Powerdown2();//Powerdown2 function
        key = keypad.getKey();//make key equal to keypad
        if (key ==password[1]){//if key equals password 2
          passwordcheck =2;//make passwordcheck 2 
          while(passwordcheck==2){//while passwordcheck is 2 
             if(y==1){//if y is 1 endgame
      		 Endgame();//endgame function
     		 }
            Powerdown2();//powerdown 2 function
           key = keypad.getKey();//make key equal to keypad
            if (key ==password[2]){//if key equals password 3
            passwordcheck =3;//make passwordcheck 3
              while(passwordcheck==3){//while password check is 3 
                 if(y==1){//if y is 1
      			 Endgame();//endgame function
      			 }
                Powerdown2();//powerdown 2 function
                key = keypad.getKey();//make key equal to keypad
                if(key ==password[3]){//if key equals password 4
                  passwordcheck =4;//make passwordcheck 4
                  while(passwordcheck ==4){//while passwordcheck is 4
                      if(y==1){//if y is 1
       		 		  Endgame();//endgame function
                      }
                    Powerdown2();//powerdown 2 function
                   key = keypad.getKey();//make key equal to keypad
                    if(key==password[4]){//if key equals password 5
                    Serial.println("Winner!!");
   					Wire.beginTransmission(4); // transmit to device #4
   					x++;//add to x 
   				    x++;//add to x
  					Wire.write(x);              // sends one byte  
  					Wire.endTransmission();    // stop transmitting
				    delay(5000);//delay 5 seconds 
  				    Wire.beginTransmission(4); // transmit to device #4
   					x--;//take away from x
    				x--;//take away from x
   					x--;//take away from x
  					Wire.write(x);              // sends one byte  
  					Wire.endTransmission();    // stop transmitting
    				menu1();//menu1 function
                    }
                  }
                }
              }
            }
          }
        }
      } 
    }
      Powerdown2();
       if(y==1){//if y equals 1
      Endgame();//end game function
       }
}
}
}

void MediumGameDescription(){//MediumGame Description, simple description of what to do 
Serial.println("Welcome to your first bomb defusal!");
Serial.println("Your goal is to stop the bomb before it goes off");
Serial.println("First you must find the sweet spot on the dial once you do it'll click.");
Serial.println("Once it clicks you must wait until the screen prompts you with a password for the keypad");
Serial.println("And you have to enter the password into the keypad before time runs out");
Serial.println("Do you understand?");
Serial.println("1.Yes");
Serial.println("2.no");
while(order==8){//while order is 8
  Powerdown();//powerdown function
    key = keypad.getKey();//make key equal to keypads inputs
   if (key == '3'|| key == '4' || key == '5' || key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'|| key == '*'|| key == '#'){
  Serial.println("Invaild Input Please Try Again!");//if anything other than 1 or 2 is pressed tell user it was an invalid input
    MediumGameDescription();//loop the function
  } else if(key == '1'){//if key is 1 
     order=7;//make order 7
       Wire.beginTransmission(4); // transmit to device #4
  x++; //add to x
  x++;// add to x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
    MediumGame();//Medium game function
    } else if(key== '2'){//if key is 2 
    MediumGameDescription();//loop the function
    }
  }
}

void MediumGame(){//medium game function
Serial.println("In Medium Game");//let user know they are in game 
  int randomlock =random(0,26);//make a random lock
  while(order==7){//while order is 7
    if (y==1){//if y is 1
        Endgame2();//end game2 function
        }
    Powerdown3();//Powerdown3 function
     makepassword();//make password function
    int data=(analogRead(rotationPin)); //make data the rotation pin
int lock = map(data,0,1023,0,25); //map data from 0-1023 to 0-25
    if(randomlock==lock){//random lock equals lock
   tone(buzzerPin, 600, 200);//turn on buzzer 
  delay(200);//delay 200 milliseconds
  noTone(buzzerPin);//turn off buzzer
    delay(1000);//delay 1 second
      Serial.print("Your Password is: ");//let user know their password
    Serial.print(password[0]);
      Serial.print(password[1]);
      Serial.print(password[2]);
      Serial.print(password[3]);
      Serial.println(password[4]);
      ingame =1;//make ingame 1
      while(ingame==1){//while ingame is 1
      key = keypad.getKey();//make key equal to keypad
    if (key == password[0]){//if key equals password 1
     passwordcheck = 1;//makepasswordcheck 1
      while (passwordcheck==1){//while passwordcheck is 1
        if(y==1){//if y is one
       Endgame2();//Endgame 2 function
       }
         Powerdown3();//powerdown 3 function
         key = keypad.getKey();//make key equal to keypad
        if (key ==password[1]){//if key equals password 2
       	   passwordcheck =2;//make passwordcheck 2
          while(passwordcheck==2){//while passwordcheck is 2
            if(y==1){//if y is 1
      	      Endgame2();//Endgame 2 function
       			}
             Powerdown3();//powerdown 3 function
           key = keypad.getKey();//make key equal to keypad
            if (key ==password[2]){//if key equals password 3
            passwordcheck =3;//make passwordcheck 3
              while(passwordcheck==3){//while passwordcheck is 3
               if(y==1){//if y is 1
      		 	Endgame2();//Endgame 2 function
       			}
                 Powerdown3();//powerdown 3 function
               key = keypad.getKey();//make key equal to keypad
                if(key ==password[3]){//if key equals password 4
                passwordcheck =4;//make passwordcheck 4
                  while(passwordcheck ==4){//while passwordcheck is 4
                   if(y==1){//if y is 1
      				 Endgame2();//Endgame 2 function
       					}
                     Powerdown3();//powerdown 3 function
                   key = keypad.getKey();//make key equal to keypad
                    if(key==password[4]){//if key equals password 5
                   Serial.println("Winner!!");//print that they won
    			Wire.beginTransmission(4); // transmit to device #4
   				x++;//add to x
   				x++;//add to x
  				Wire.write(x);              // sends one byte  
  				Wire.endTransmission();    // stop transmitting
 				 delay(5000);
 				Wire.beginTransmission(4); // transmit to device #4
 				for(int i=0; i<4; i++){//for 5 times  
 				x--;//take away from x
 				}
  				Wire.write(x);              // sends one byte  
  				Wire.endTransmission();    // stop transmitting
    			menu1();//menu 1 function
                    }
                  }
                }
              }
            }
          }
        }
      } 
    }
        Powerdown3();//powerdown 3 function
        if (y==1){//if y is 1 
        Endgame();//endgame function
        }
      }
      }
  }
}

void Powerdown(){//powerdown function
if (digitalRead(button1Pin)==HIGH){// if power is pressed 
Serial.println("Powering off");// turn off
        Wire.beginTransmission(4); // transmit to device #4
  x--; //take away from x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
        delay(350);//delay 350 milliseconds
      start();//start function
    } 
}

void Powerdown2(){//powerdown 2 function
if (digitalRead(button1Pin)==HIGH){// if power is pressed 
Serial.println("Powering off");// turn off
 Wire.beginTransmission(4); // transmit to device #4
  x--; //take away from x
  x--;//take away from x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
      delay(350);//delay 350 milliseconds
      start();//start function
    } 

}

void Powerdown3(){//powerdown 3 function
if (digitalRead(button1Pin)==HIGH){// if power is pressed 
Serial.println("Powering off");// turn off
 Wire.beginTransmission(4); // transmit to device #4
  x--;//take away from x
  x--;//take away from x
  x--;//take away from x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
      delay(350);//delay 350 milliseconds
      start();//start function
    } 

}
  void Endgame(){//endgame function
   Serial.println("Game Over! Get Better.");//tell user that the game is over and to get better
      delay(350);//delay 350 milliseconds
   Wire.beginTransmission(4); // transmit to device #4
 	x--;//take away from x
  	x--;//take away from x
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
      start();//start function
       }
  

  void Endgame2(){//endgame 2 function
  Serial.println("Game Over! Get Better.");//tell user that the game is over and to get better
    delay(350);//delay 350 milliseconds
	Wire.beginTransmission(4); // transmit to device #4
  	x--;//take away from x
  	x--;//take away from x
  	x--;//take away from x
  	Wire.write(x);              // sends one byte  
  	Wire.endTransmission();    // stop transmitting
    start();//startfunction
  }
  
void makepassword(){//make password function
for (int i =0; i<=5; i++){//for 5 times
    randomnumber= random(0,10);//make a random number between 0 and 9
      if (randomnumber==0){//check if what random number was and make num equal to it as a char
      num = '0';
      } else if (randomnumber==1){
      num = '1';
      } else if (randomnumber==2){
      num = '2';
      } else if (randomnumber==3){
      num = '3';
      } else if (randomnumber==4){
      num = '4';
      } else if (randomnumber==5){
      num = '5';
      } else if (randomnumber==6){
      num = '6';
      } else if (randomnumber==7){
      num = '7';
      } else if (randomnumber==8){
      num = '8';
      } else if (randomnumber==9){
      num = '9';
      }
      password[0] = num;//make password1 equal to num
      if (i==1){//if i is 1
      password[1] = num;//make password2 equal to num
      }
      if (i==2){//if i is 2
      password[2] = num;//make password3 equal to num
      }
      if (i==3){//if i is 3
      password[3] = num;//make password4 equal to num
      }
      if (i==4){//if i is 4
      password[4] = num;//make password5 equal to num
      }
    }
}
      
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  y = Wire.read();    // receive byte as an integer
}