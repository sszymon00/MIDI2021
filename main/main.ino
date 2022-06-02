/*
Szymon Sierakowski Elektrotechnika semestr 7
Praca dyplomowa I stopień
"Kontroler MIDI do cyfrowej obróbki dzwięku"
 */
#define controlC 0xB0 // Bajt statusu informujący o funkcji channel control kanał 1 - 176
#define noteON 0x90 // Bajt statusu NoteON  wartość kanał 1 - 144
#define noteOFF 0x80 // Bajt statusu NoteOFF  wartość kanał 1 - 128

int noteC = 60; // Nuta C 

// Jednokrotna inicjalizacja wyświetlacza OLED oraz ISR enkodera
void setup() {
  oledSetup();  //Rozpoczęcie pracy ekranu OLED
  encSetup();   //Rozpoczęcie pracy Enkodera
  Serial.begin(115200); //Ustawienie prędkości przesyłu danych przez port szeregowy
}

// Pętla która sprawdza synchronicznie stan na potencjometrach i przyciskach
void loop() {
  readPots(); //Odczytywanie potencjometrów
  readKpd();  //Odczytywanie klawiatury
  readEncButton();  //Odczytywanie przycisku enkodera
}
