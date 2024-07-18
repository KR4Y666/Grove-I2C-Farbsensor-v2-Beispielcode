#include "Wire.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup() {
  
 Serial.begin(9600);
 
 // Überprüfen, ob Color Sensor sich zurückmeldet
 if (tcs.begin()) {
 // Alles OK
 Serial.println("Sensor gefunden");
 } else {
 // Kein Sensor gefunden. Programm an dieser Stelle einfrieren
 Serial.println("TCS34725 nicht gefunden ... Ablauf gestoppt!");
 while (1); // Halt!
 } 
}

void loop() {
 
 // Der Sensor liefert Werte für R, G, B und einen Clear-Wert zurück
 uint16_t clearcol, red, green, blue;
 float average, r, g, b;
 delay(100); // Farbmessung dauert ca 50ms -> delay > 50ms wählen 
 tcs.getRawData(&red, &green, &blue, &clearcol);
 
 // Berechnung Farbwerte 
 average = (red+green+blue)/3; 
 r = red/average;
 g = green/average;
 b = blue/average;

 // Clear-Wert und r,g,b seriell ausgeben
 // r,g und b ca. zwischen 0,5 und 1,5 
 Serial.print("\tClear:"); Serial.print(clearcol);
 Serial.print("\tRed:"); Serial.print(r);
 Serial.print("\tGreen:"); Serial.print(g);
 Serial.print("\tBlue:"); Serial.print(b);

 // Farbfeststellung anhand der r,g,b-Werte.
 // Am besten mit Rot, Grün, Blau anfangen und die Schwellenwerte
 // mit der seriellen Ausgabe entsprechend anpassen
 if ((r > 1.4) && (g < 0.9) && (b < 0.9)) {
 Serial.print("\tROT");
 }
 else if ((r < 0.95) && (g > 1.4) && (b < 0.9)) {
 Serial.print("\tGRUEN");
 }
 else if ((r < 0.8) && (g < 1.2) && (b > 1.2)) {
 Serial.print("\tBLAU");
 }
 else {
 Serial.print("\tNICHT ERKANNT"); 
 }

 Serial.println(""); 
 delay(100);
}
