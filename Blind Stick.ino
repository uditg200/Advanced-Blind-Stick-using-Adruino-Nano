#include <Arduino.h>
#include <SoftwareSerial.h>

int const trigPin1 = 7;
int const echoPin1 = 6;
int const s_pin = 16;

int const trigPin2 = 12;
int const echoPin2 = 9;

SoftwareSerial mySerial(10, 11);
const int buttonNext=2;

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define ACTIVATED LOW
boolean isPlaying = false;

void setup () {
  pinMode(buttonNext, INPUT);
  digitalWrite(buttonNext,HIGH); 
  mySerial.begin (9600);
  //delay(1000);
  pinMode(trigPin1 , OUTPUT); 
  pinMode(echoPin1 , INPUT); 
  
  pinMode(trigPin2 , OUTPUT); 
  pinMode(echoPin2 , INPUT); 
  //playFirst();
  //isPlaying = true;
}

void loop ()
{ 

    static int flag1=0;
    static int flag2=0;
    static int flag3=0;
    static int flag4=0;
    static int flag5=0;
    
    int duration1, distance1;
    int duration2, distance2;
    digitalWrite(trigPin1, HIGH);
    delay(1);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1 / 2) / 29.1;

      digitalWrite(trigPin2, HIGH);
      delay(1);
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
      distance2 = duration2 / 58.3;

    if(distance1 <= 40 && analogRead(s_pin)!=LOW)
    {
        flag1=0;
        flag2=0;
        flag4=0;
        flag5=0;
        if(flag3==0)
        {
          play1(2);
          flag3++;
        }
        else
        {
          play();
        }
      }
  

    
      else if (distance1 <= 40) {
        flag2=0;
        flag3=0;
        flag4=0;
        flag5=0;
        if(flag1==0)
        {
           play1(1);
           flag1++;
        }
        else
           play();
      }
  
      
      else if(analogRead(s_pin)!=LOW)
      {
          flag1=0;
          flag3=0;
          flag4=0;
          flag5=0;
          if(flag2==0)
          {
            play1(5);
            flag2++;
          }
          else
          {
            play();
          }
      }

//       const distance that we want to set b/w floor and ultrasonic sensor is 28 cm
    
      else if(distance2 <=16)   // distance 18 - 18.5 cm
      {
          flag1=0;
          flag2=0;
          flag3=0;
          flag5=0;
          if(flag4==0)
          {
            play1(3);
            flag4++;
          }
          else
          {
            play();
          }
      }

      
      else if(distance2 >= 40)   // distance 38 cm approx(yet to confirm)
      {
          flag1=0;
          flag2=0;
          flag3=0;
          flag4=0;
          if(flag5==0)
          {
            play1(4);
            flag5++;
          }
          else
          {
            play();
          }
      }

      
      else
      {
        pause(); 
      }
    delay(60);
}


void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(20);
  delay(500);
  execute_CMD(0x11,0,1); 
  delay(500);
}


void pause()
{
  execute_CMD(0x0E,0,0);
  //delay(500);
}


void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}


void playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
}


void play1(int d)
{
  execute_CMD(0x03,(d >> 8) & 0xFF, d & 0xFF );
}


void playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
}


void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}


void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  
    // Calculate the checksum (2 bytes)
    word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
    
    
    // Build the command line
    byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                              Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
    
    
    //Send the command line to the module
    for (byte k=0; k<10; k++)
    {
      mySerial.write( Command_line[k]);
    }
}
