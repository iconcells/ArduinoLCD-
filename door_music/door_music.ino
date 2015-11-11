int buttonPin = 4;
int buzzerPin = 8;
int length = 40; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1,1,1,1,1,1,2,1,1,1,1,1,1,2,4 };
int tempo = 300;
void playTone(int tone, int duration) {
 for (long i = 0; i < duration * 700L; i += tone * 2) {
 digitalWrite(buzzerPin, HIGH);
 delayMicroseconds(tone);
 digitalWrite(buzzerPin, LOW);
 delayMicroseconds(tone);
 }
}
void playNote(char note, int duration) {
 char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
 int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

 // play the tone corresponding to the note name 
// Copyright by Seeedstudio
 for (int i = 0; i < 8; i++) {
 if (names[i] == note) {
 playTone(tones[i], duration);
 }
 }
}
void setup() {
 pinMode(buzzerPin, OUTPUT);
 pinMode(buttonPin,INPUT);
}
void loop() {
 if(digitalRead(buttonPin))
 {
 for (int i = 0; i < length; i++) {
 if (notes[i] == ' ') {
 delay(beats[i] * tempo); // rest
 } else {
 playNote(notes[i], beats[i] * tempo);
 }

 // pause between notes
 delay(tempo / 20);
 }
 }
} 
