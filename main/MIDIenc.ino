// Można było ustawic jeden pin z enkondera na interrupt a drugi dac na przycisk, ale wtedy tracimy dokładność sprawdzania encodera
// Zmiana ekranu nie musi byc sprawdzana asynchronicznie wiec wrzucono na pin 4

#include <Rotary.h>

#define encoderPinA  2  // Pin obsługujący przerwania
#define encoderPinB  3  // Pin obsługujący przerwania
#define encoderButtonPin  4 //Pin do którego dołączony jest przycisk wbudowany w enkoder

Rotary rotary = Rotary(encoderPinA, encoderPinB); // Obiekt klasy Rotary

volatile int encoderPos = 0;  // Zmienna w ISR typu volatile
unsigned int encoderButtonCounter = 0;  // Licznik przyciśnięć przycisku

int buttonState = 0;         // Stan przycisku
int lastButtonState = 0;     // Poprzedni stan przycisku

void encSetup()
{
  pinMode(encoderButtonPin, INPUT_PULLUP);
  attachInterrupt(0, doEncoder, CHANGE);  // Dołączenie ISR do pinu 2 (interrupt 0) 
  attachInterrupt(1, doEncoder, CHANGE);  // Dołączenie ISR do pinu 3 (interrupt 1) 
}

void doEncoder() {
  unsigned char result = rotary.process();
  
 if (encoderPos > -59) {    // Dolny zakres zmiany tonu  
    if (result == DIR_CW) { // Jeśli obrót zgodnie z ruchem wskazówek zegara
      encoderPos--;
    } 
  }
   if (encoderPos < 52) {  // Górny zakres zmiany tonu  
      if (result == DIR_CCW) {// Jeśli obrót przciwnie z ruchem wskazówek zegara
        encoderPos++;
    }
  }
}

void readEncButton() {
  buttonState = digitalRead(encoderButtonPin);// Odczyt stanu przycisku
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
        if (buttonState != lastButtonState) { // W przypadku zbocza opadającego, zmienia wartość 
          encoderButtonCounter++;             // licznika. Na jego podstawie funkcje w pliku OLED
            switch(encoderButtonCounter){     // określają co należy wyświetlić na ekranie
              case 0:
                clearScreen();
              break;
              case 1:
                clearScreen();
              break;
              case 2:
                clearScreen();
                waitForInput();
                encoderButtonCounter = 0;   // Rest licznika 
              break;
            }
          }
        }
      }
    lastButtonState = buttonState;
}
