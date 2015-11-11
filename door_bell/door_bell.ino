int buttonPin = 4; 
//Copyright by Seeedstudio
int buzzerPin = 8;
void setup()
{
 pinMode(buttonPin,INPUT);//set button as digital input
 pinMode(buzzerPin,OUTPUT);//as buzzer as digital output
}
void loop()
{
 if(digitalRead(buttonPin))//check button is pressed or not
 {
 digitalWrite(buzzerPin,HIGH);//pressed，then buzzer buzzes
 }
 else
 {
 digitalWrite(buzzerPin, LOW);//not pressed，then buzzer remains silent
 }
}
//Ultimate Result：Press the doorbell, and the buzzer will Buzz “B”
