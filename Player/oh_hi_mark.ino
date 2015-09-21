/***************************************************
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins.
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)


// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer =
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
/*
0 = boot
1 = hi mark
2 = know everything
3 = expert
4 = what a story
5 = shame
*/

#define NUM_FILES 8
char *tracks[NUM_FILES] = {"0.mp3", "1.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "glar.mp3","uffe.mp3"};

int relayL = 5;
int relayR = 6;

void setup() {
  pinMode(relayL, OUTPUT);
  pinMode(relayR, OUTPUT);
  digitalWrite(relayL, LOW);
  digitalWrite(relayR, LOW);


  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

  SD.begin(CARDCS);    // initialise the SD card

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  Serial.println(F("Playing boot"));
  musicPlayer.playFullFile(tracks[0]);

  digitalWrite(relayL, HIGH);
  digitalWrite(relayR, HIGH);
}

void loop() {

  if (Serial.available()) {
    int i = Serial.parseInt();
    Serial.println(i);
    if(i >= 0 && i < NUM_FILES){
    //  Serial.println("inside if");
      digitalWrite(relayL, LOW);
      digitalWrite(relayR, LOW);
      musicPlayer.playFullFile(tracks[i]);
      digitalWrite(relayL, HIGH);
      digitalWrite(relayR, HIGH);
      while(Serial.available()){
        Serial.read();
      }
    }
  }

  delay(1);
}
