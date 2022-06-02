
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Szerokość ekranu w pixelach 
#define SCREEN_HEIGHT 64 // Wysokość ekranu w pixelach

#define OLED_RESET     -1 // Reset pin (-1 jeśli korzysta z tego wbudowanego w Arduino)
#define SCREEN_ADDRESS 0x3C ///0x3D dla 128x64, 0x3C dla 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oledSetup(){
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  welcomeScreen();
  display.clearDisplay();
}

void welcomeScreen(void) {
  display.clearDisplay(); //Wyczyszczenie buforu ekranu
  display.setTextSize(2); //Zmiana skali tekstu
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Start"));
  display.println(F("Program"));
  display.display();      //Przeniesienie informacji z buforu na ekran
  delay(2000);
}
void waitForInput(){
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Waiting "); 
  display.println("for kbd");
  display.println("input...");
  display.display();      
}
void clearScreen(){
  display.clearDisplay();
}

void encScreenSend(){
  if(encoderButtonCounter == 0){
    display.setCursor(28, 0);
    display.setTextSize(2); // Draw 2X-scale text
    display.print("Offset:"); 
    display.println(encoderPos);
  }
}

void noteScreenSend(byte note, byte pitch, byte velocity) { 
  if(encoderButtonCounter == 0){            //Funkcja wysyła na ekran tekst
    display.clearDisplay();                 //zawierający informacje dotyczące
    display.setTextSize(2);                 //tego która nuta została ostatnio wysłana
    display.setTextColor(SSD1306_WHITE);    //z jaką prędkością oraz jakim tonem
    display.setCursor(0, 0);
    
    display.print("Note:"); 
    if(note == noteON)
      display.println("ON");
    else
      display.println("OFF");
    
    display.print("Pitch:"); 
    display.println(pitch);
    
    display.setTextSize(1); 
    display.print("Offset:"); 
    display.println(encoderPos);
  
    display.setTextSize(2); 
    display.print("Vel:");
    display.println(velocity);
    
    display.display();      
  }
}
// Wyświetlanie wiadomości channel control
void controlScreenSend(byte channel, byte number, byte value) {
  if(encoderButtonCounter == 1){
    display.fillRect(0, 4 +(number-1)*display.height()/4, display.width(), display.height()/8, SSD1306_BLACK);
    display.drawRect(0, 4 +(number-1)*display.height()/4, value, display.height()/8, SSD1306_WHITE);
    display.display();      // Show initial text
  }
}
