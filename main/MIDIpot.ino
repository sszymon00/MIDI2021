// 

const int PIN_PORT[4] = {17, 16, 15, 14}; //14 - A0, 15 - A1, 16 - A2, 17 - A3

int potVal[4] = {0};      //Wartości z przetwornika A/C
int prevPotVal[4] = {0};  //Poprzednie wartości z przetwornika A/C
int potValdiff = 0;
int potMax = 1023;        //Maksymalna wartość przyjmowa przez przetwornik A/C
bool isUpdatedPotScreen = 0;    //Zmienna sprawdzająca czy ekran był aktualizowany po przełączeniu
bool isUpdatedPotMin[4] = {0};  //Zmienna sprawdzająca czy osiągnięto maksymalną wartość na przetworniku
bool isUpdatedPotMax[4] = {0};  //Zmienna sprawdzająca czy osiągnięto minimalną wartość na przetworniku

void readPots() { //Funkcja odczytująca wartości z potencjometrów
  const int diff = 8; //Przyjęta różnica w zmierzonych wartościach 1024/128 = 8

  if(encoderButtonCounter == 1){        //Jednorazowa aktualizacja ekranu obecnymi wartościami z przetworników
    if(isUpdatedPotScreen == 0){        //przy przełączaniu trybu ekranu
        clearScreen();
        for(int i = 0; i < 4; i++){
          controlScreenSend(controlC, i + 1, map(potVal[i], 0, potMax, 0, 127));
        }
        isUpdatedPotScreen = 1;
    }
  } 

  if(encoderButtonCounter != 1)
    isUpdatedPotScreen = 0;
  
  for(int i = 0; i < 4; i++){
    potVal[i] = analogRead(PIN_PORT[i]);    //Odczytanie wartości z przetwornika A/C
    potValdiff = potVal[i] - prevPotVal[i]; //Obliczenie różnicy między wartością odczytaną i obecną
    
    if (abs(potValdiff) > diff) {             //Jeśli wartość bezwzględna z różnicy jest większa niż przyjęta
      if(potVal[i] > potMax-16){              //Przyjęcie wartości maksymalnej dla odczytanych blisko wartości maksymalnej 
        if(isUpdatedPotMax[i] == 0){ 
          MIDImessage(controlC, i + 1 , 127);     //Wysłanie wiadomości MIDI typu control change
          controlScreenSend(controlC, i + 1, 127);//oraz informacji do ekranu OLED
          prevPotVal[i] = potVal[i];          //Zapisanie odczytanej wartości jako poprzednia
          isUpdatedPotMax[i] = 1;
        }
      } else
      if(potVal[i] > 16){                     //Jeśli odczytana wartość nie jest blisko 0
        MIDImessage(controlC, i + 1 , map(potVal[i], 0, potMax, 0, 127));     //Zmapowanie odczytanej wartości
        controlScreenSend(controlC, i + 1, map(potVal[i], 0, potMax, 0, 127));//wysłanie wiadomo
        prevPotVal[i] = potVal[i];          //Przyjęcie wartości maksymalnej dla odczytanych blisko wartości maksymalnej 
        isUpdatedPotMin[i] = 0;
        isUpdatedPotMax[i] = 0;
      } else 
       if(isUpdatedPotMin[i] == 0){             //Pozostały przypadek - wartość odczytana z przetwornika jest bliska 0
          MIDImessage(controlC, i + 1 , 0);     //Przyjęcie wartości minimalnej dla odczytu blisko 0, wysłanie wiadomości MIDI
          controlScreenSend(controlC, i + 1, 0);//oraz informacji do ekranu OLED
          prevPotVal[i] = potVal[i];
          isUpdatedPotMin[i] = 1;
      }
    }
  }
  delay(10);    //Wprowadzono niewielkie opóźnienie zby ustabilizować następny odczyt
}
