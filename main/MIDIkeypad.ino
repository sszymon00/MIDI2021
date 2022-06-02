#include <Keypad.h>

#define ROWS 4 //Liczba rzędów
#define COLS 4 //Liczba kolumn
//Definicja symboli dla każdego przycisku 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS] = {12, 11, 10, 9};  //Piny mikrokontrolera do których należy podłączyć każdy rząd
byte colPins[COLS] = {8, 7, 6, 5};    //Piny mikrokontrolera do których należy podłączyć każdą kolumnę

//Inicjalizacja obiektu klasy Keypad
Keypad kpd = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void readKpd()  //Funkcja odpowiedzialna za odczytywanie stanu przycisków i wysyłanie wiadomości NoteON i NoteOFF
{
  if (kpd.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) //Skanowanie wszystkich przycisków
    {
      if ( kpd.key[i].stateChanged)   //Szukanie przycisku, którego stan się zmienił
      {
        if (kpd.key[i].kstate == PRESSED) //Jeśli przycisk jest naciśnięty
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(noteON, noteC + encoderPos + 0, 127);     //Wysłanie wiadomości midi
              noteScreenSend(noteON, noteC + encoderPos + 0, 127);  //Wysłanie wiadomości do ekranu OLED
              break;
            case '2':
              MIDImessage(noteON, noteC + encoderPos + 1, 127);
              noteScreenSend(noteON, noteC + encoderPos + 1, 127);
              break;
            case '3':
              MIDImessage(noteON, noteC + encoderPos + 2, 127);
              noteScreenSend(noteON, noteC + encoderPos + 2, 127);
              break;
            case 'A':
              MIDImessage(noteON, noteC + encoderPos + 3, 127);
              noteScreenSend(noteON, noteC + encoderPos + 3, 127);
              break;
            case '4':
              MIDImessage(noteON, noteC + encoderPos + 4, 127);
              noteScreenSend(noteON, noteC + encoderPos + 4, 127);
              break;
            case '5':
              MIDImessage(noteON, noteC + encoderPos + 5, 127);
              noteScreenSend(noteON, noteC + encoderPos + 5, 127);
              break;
            case '6':
              MIDImessage(noteON, noteC + encoderPos + 6, 127);
              noteScreenSend(noteON, noteC + encoderPos + 6, 127);
              break;
            case 'B':
              MIDImessage(noteON, noteC + encoderPos + 7, 127);
              noteScreenSend(noteON, noteC + encoderPos + 7, 127);
              break;
            case '7':
              MIDImessage(noteON, noteC + encoderPos + 8, 127);
              noteScreenSend(noteON, noteC + encoderPos + 8, 127);
              break;
            case '8':
              MIDImessage(noteON, noteC + encoderPos + 9, 127);
              noteScreenSend(noteON, noteC + encoderPos + 9, 127);
              break;
            case '9':
              MIDImessage(noteON, noteC + encoderPos + 10, 127);
              noteScreenSend(noteON, noteC + encoderPos + 10, 127);
              break;
            case 'C':
              MIDImessage(noteON, noteC + encoderPos + 11, 127);
              noteScreenSend(noteON, noteC + encoderPos + 11, 127);
              break;
            case '*':
              MIDImessage(noteON, noteC + encoderPos + 12, 127);
              noteScreenSend(noteON, noteC + encoderPos + 12, 127);
              break;
            case '0':
              MIDImessage(noteON, noteC + encoderPos + 13, 127);
              noteScreenSend(noteON, noteC + encoderPos + 13, 127);
              break;
            case '#':
              MIDImessage(noteON, noteC + encoderPos + 14, 127);
              noteScreenSend(noteON, noteC + encoderPos + 14, 127);
              break;
            case 'D':
              MIDImessage(noteON, noteC + encoderPos + 15, 127);
              noteScreenSend(noteON, noteC + encoderPos + 15, 127);
          }
        }

        if (kpd.key[i].kstate == RELEASED)  // sends MIDI off message when keys are released
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(noteOFF, noteC + encoderPos + 0, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 0, 0);
              break;
            case '2':
              MIDImessage(noteOFF, noteC + encoderPos + 1, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 1, 0);
              break;
            case '3':
              MIDImessage(noteOFF, noteC + encoderPos + 2, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 2, 0);
              break;
            case 'A':
              MIDImessage(noteOFF, noteC + encoderPos + 3, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 3, 0);
              break;
            case '4':
              MIDImessage(noteOFF, noteC + encoderPos + 4, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 4, 0);
              break;
            case '5':
              MIDImessage(noteOFF, noteC + encoderPos + 5, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 5, 0);
              break;
            case '6':
              MIDImessage(noteOFF, noteC + encoderPos + 6, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 6, 0);
              break;
            case 'B':
              MIDImessage(noteOFF, noteC + encoderPos + 7, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 7, 0);
              break;
            case '7':
              MIDImessage(noteOFF, noteC + encoderPos + 8, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 8, 0);
              break;
            case '8':
              MIDImessage(noteOFF, noteC + encoderPos + 9, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 9, 0);
              break;
            case '9':
              MIDImessage(noteOFF, noteC + encoderPos + 10, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 10, 0);
              break;
            case 'C':
              MIDImessage(noteOFF, noteC + encoderPos + 11, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 11, 0);
              break;
            case '*':
              MIDImessage(noteOFF, noteC + encoderPos + 12, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 12, 0);
              break;
            case '0':
              MIDImessage(noteOFF, noteC + encoderPos + 13, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 13, 0);
              break;
            case '#':
              MIDImessage(noteOFF, noteC + encoderPos + 14, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 14, 0);
              break;
            case 'D':
              MIDImessage(noteOFF, noteC + encoderPos + 15, 0);
              noteScreenSend(noteOFF, noteC + encoderPos + 15, 0);
          }
        }
      }
    }
  }
}
