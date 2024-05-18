#include "noteScore.h"
#include "pitches.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C
// Define proper RST_PIN if required.
#define RST_PIN -1
SSD1306AsciiWire oled;

#define BuzzB 12 // buzzer to display the bass part
#define BuzzV1 10 // buzzer to display the violin1 part (main melody)
#define BuzzV2 8 // buzzer to display the violin2 part (counter-melody)
#define capPin 2
#define NAME "  MAGGIE!"

/**************************** GLOBAL VARIABLES ***************************/

/*    Create a long const variable to set the tempo for the entire song,
 * it represents the length of a beat(a quarter note) in microsecond.
 
 *    When the tempo is 115bpm(beats per minute), each beat would be 
 * 521739 microseconds long.
 * (60,000,000 microseconds / 115 beats) = 521739 microseconds per beat.
 
 *    Since each beat will be sub divided into 16 parts to generate different 
 * note length, and all variables are represented by integers. Therefore,
 * (BEATLENGTH % 16 = 0) must be true. 521744 is the closest number to 521739
 * which satisfies this condition.
 */
  const unsigned long BEATLENGTH = 461536; // tempo 115

/*    Since the music score is made up of arrays, we need an index for 
 * each array to run through the entire music score.
 */
  byte V1index = 0; // index for main melody(V1)
  byte V2index = 0; // index for counter melody(V2)
  byte Bindex = 0; // index for bass(B)

/*    In order for a buzzer to play in the right tone, we need to turn the
 * buzzer on and off for a constant period of time. Check "notePeriod.h" 
 * for details on how to define and use the note period values.
 */
  // create an int variable to store the delay time for the next switch
  // motion on any buzzer,
  // delayTime = 10 represents the next switch mostion will take place
  // after 10 microseconds.
  unsigned int delayTime = 0; 
  // create a long variable to keep track of the current length of the beat,
  // curLength = 0 represents the very beginning of a beat.
  unsigned long curLength = 0;
  // create three long variables to store the next time for each buzzer to 
  // be switched on or off.
  // for convinence, NST = next switch time
  // V1nextSwitchTime = 2000 means when curLength = 2000, switch V1 buzzer.
  unsigned long V1nextSwitchTime = 0; // NST for V1
  unsigned long V2nextSwitchTime = 0; // NST for V2
  unsigned long BnextSwitchTime = 0; // NST for B
  // create three byte variables to store the current state of each buzzer,
  // V1state = LOW means the V1 buzzer is off, HIGH means on.
  byte V1state = LOW; // buzzer state for V1
  byte V2state = LOW; // buzzer state for V2
  byte Bstate = LOW; // buzzer state for B
  // create three long variables to store the note length for the current note
  // on each buzzer,
  // for convinence, NL = note length,
  // V1noteLength = 5000 means the current note will play for 5000 microseconds
  // on V1 buzzer.
  unsigned long V1noteLength = 0; // NL for the current V1 note
  unsigned long V2noteLength = 0; // NL for the current V2 note
  unsigned long BnoteLength = 0; // NL for the current B note
  // create and initialize max and min variables for NST and NL, they are used to
  // determine which buzzer will be switched first(minNST) or last(maxNST).
  unsigned long minNextSwitchTime = 0; // min for NST
  unsigned long maxNextSwitchTime = 0; // max for NST
  unsigned long minNoteLength = 0; // min for NL
  unsigned long maxNoteLength = 0; // max for NL
void setup() {
  Serial.begin(115200);
  Wire.setClock(400000L);
  #if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);

  uint32_t m = micros();
  oled.clear();
  oled.set1X();
  oled.println("         2024   ");
  oled.println();
  oled.set2X();
  oled.println("   HAPPY");
  oled.println("GRADUATION");
  oled.println(NAME);
  delay(2000);
  // set all the pins connected with a buzzer to OUTPUT mode
  pinMode(BuzzB, OUTPUT); // set BuzzB to OUTPUT mode
  pinMode(BuzzV1, OUTPUT); // set BuzzV1 to OUTPUT mode
  pinMode(BuzzV2, OUTPUT); // set BuzzV2 to OUTPUT mode
  pinMode(capPin, INPUT);
  playSong();
}

void loop() {
  oled.clear();
  oled.set2X();
  oled.println();
  oled.println("<- Tap to");
  oled.println("play again~");

  while(digitalRead(capPin) == 0);
  oled.clear();
  oled.set1X();
  oled.println("         2024   ");
  oled.println();
  oled.set2X();
  oled.println("   HAPPY");
  oled.println("GRADUATION");
  oled.println(NAME);
  delay(1000);
  playSong();
}

void playSong() {
  playM1_4();
  playM5_8();
  playM9_12();
  playM13_16();
  playM17_M20();
  playM21_M24();
  playM25_M28();
  playM29_M31();
  delay(1000);
}


void playM1_4() {
  play(melody_V1_1, noteLength1, 4, melody_V2_1, noteLength1, 4, melody_B_1, noteLength1, 4);
  play(melody_V1_2, noteLength1, 4, melody_V2_2, noteLength1, 4, melody_B_2, noteLength1, 4);
  play(melody_V1_3, noteLength2, 4, melody_V2_3, noteLength2, 4, melody_B_3, noteLength2, 4);
  play(melody0, noteLength0, 1, melody0, noteLength0, 1, melody_B_4, noteLength1, 4);
}

void playM5_8() {
  //displayText("Happy!", 15, 16, 3);
  play(melody_V1_5, noteLength1, 4, melody0, noteLength0, 1, melody_B_1, noteLength1, 4);
  //displayText("Happy!", 15, 24, 3);
  play(melody_V1_6, noteLength1, 4, melody0, noteLength0, 1, melody_B_2, noteLength1, 4);
  //displayText("Happy!", 15, 16, 3);
  play(melody_V1_7, noteLength2, 4, melody0, noteLength0, 1, melody_B_3, noteLength2, 4);
  //displayText("Happy!", 15, 24, 3);
  play(melody0, noteLength0, 1, melody0, noteLength0, 1, melody_B_4, noteLength1, 4);
}

void playM9_12() {
  //displayText("Happy!", 15, 16, 3);
  play(melody_V1_9, noteLength3, 8, melody_V2_9, noteLength4, 4, melody_B_9, noteLength1, 4);
  play(melody_V1_10, noteLength3, 8, melody_V2_10, noteLength4, 4, melody_B_10, noteLength1, 4);
  play(melody_V1_11, noteLength4, 4, melody_V2_11, noteLength4, 4, melody_B_11, noteLength1, 4);
  play(melody0, noteLength0, 1, melody0, noteLength0, 1, melody_B_12, noteLength3, 8);
}

void playM13_16() {
  play(melody_V1_13, noteLength3, 8, melody_V1_13, noteLength3, 8, melody_B_9, noteLength1, 4);
  play(melody_V1_14, noteLength3, 8, melody_V1_14, noteLength3, 8, melody_B_10, noteLength1, 4);
  play(melody_V1_15, noteLength4, 4, melody_V1_15, noteLength4, 4, melody_B_11, noteLength1, 4);
  play(melody0, noteLength0, 1, melody_V2_16, noteLength3, 8, melody_V2_16, noteLength3, 8);
}

void playM17_M20() {
  play(melody_V1_17, noteLength3, 8, melody_V1_17, noteLength3, 8, melody_B_17, noteLength3, 8);
  play(melody_V1_18, noteLength3, 8, melody_V1_18, noteLength3, 8, melody_B_18, noteLength3, 8);
  play(melody_V1_19, noteLength3, 8, melody_V1_19, noteLength3, 8, melody_B_19, noteLength3, 8);
  play(melody_V1_20, noteLength3, 8, melody_V1_20, noteLength3, 8, melody_B_20, noteLength3, 8);
}

void playM21_M24() {
  play(melody_V1_21, noteLength3, 8, melody_V1_21, noteLength3, 8, melody_B_21, noteLength3, 8);
  play(melody_V1_22, noteLength3, 8, melody_V1_22, noteLength3, 8, melody_B_22, noteLength3, 8);
  play(melody_V1_23, noteLength3, 8, melody_V1_23, noteLength3, 8, melody_B_23, noteLength3, 8);
  play(melody_V1_24, noteLength3, 8, melody_V1_24, noteLength3, 8, melody_B_24, noteLength3, 8);
}

void playM25_M28() {
  play(melody_V1_25, noteLength3, 8, melody_V2_25, noteLength4, 4, melody_B_25, noteLength1, 4);
  play(melody_V1_26, noteLength3, 8, melody_V2_26, noteLength4, 4, melody_B_26, noteLength1, 4);
  play(melody_V1_27, noteLength4, 4, melody_V2_27, noteLength4, 4, melody_B_27, noteLength1, 4);
  play(melody0, noteLength0, 1, melody_V2_28, noteLength4, 4, melody_B_28, noteLength1, 4);
}

void playM29_M31() {
  play(melody_V1_29, noteLength3, 8, melody_V1_29, noteLength3, 8, melody_B_29, noteLength1, 4);
  play(melody_V1_30, noteLength3, 8, melody_V1_30, noteLength3, 8, melody_B_30, noteLength1, 4);
  play(melody_V1_31, noteLength5, 2, melody_V1_31, noteLength5, 2, melody_B_31, noteLength5, 2);
}
// void displayText(String text, int x_pos, int y_pos, int size) {
//   display.clearDisplay();
//   display.setTextColor(WHITE);
//   display.setTextSize(size);
//   display.setCursor(x_pos, y_pos);
//   // Display static text
//   display.println(text);
//   display.display(); 
// }
void play(int V1note[], byte V1beat[], int V1size, 
          int V2note[], byte V2beat[], int V2size, 
          int Bnote[], byte Bbeat[], int Bsize) {
  // initialize all the indexes
  V1index = 0;
  V2index = 0;
  Bindex = 0;
  // initialize delayTime and curLength
  delayTime = 0;
  curLength = 0;
  // initialize all NST, the first NST should just be the note period
  // use checkZero() to assign NST for rest notes
  V1nextSwitchTime = checkZero(V1note[V1index]);
  V2nextSwitchTime = checkZero(V2note[V2index]);
  BnextSwitchTime = checkZero(Bnote[Bindex]);
  // initialize the buzzers and their states
  V1state = LOW;
  V2state = LOW;
  Bstate = LOW;
  digitalWrite(BuzzV1, V1state);
  digitalWrite(BuzzV2, V2state);
  digitalWrite(BuzzB, Bstate);
  // initialize the note length for the first note
  V1noteLength = BEATLENGTH / 16 * V1beat[V1index];
  V2noteLength = BEATLENGTH / 16 * V2beat[V2index];
  BnoteLength = BEATLENGTH / 16 * Bbeat[Bindex];
  // initialize max and min variables for NST and NL
  minNextSwitchTime = minVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime);
  maxNextSwitchTime = maxVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime);
  minNoteLength = minVal(V1noteLength, V2noteLength, BnoteLength);
  maxNoteLength = maxVal(V1noteLength, V2noteLength, BnoteLength);

  // use a while loop to play notes in this beat
  // when the beat is not over
  while(maxNoteLength <= BEATLENGTH) {
    // when the shortest note is not over
    while(maxNextSwitchTime <= minNoteLength) {
      // delay to the minNST
      delayTime = minNextSwitchTime - curLength; // calculate delayTime in microseconds
      delayMicroseconds(delayTime); // delay for "delayTime" microseconds
      curLength = curLength + delayTime; // update current length

      // use an if statement to update NST
      if((V1nextSwitchTime == minNextSwitchTime) && 
            (V2nextSwitchTime == minNextSwitchTime) &&
              (BnextSwitchTime == minNextSwitchTime)) { // update all V1NST, V2NST, BNST
        // update V1, V2, B states
        V1state = switchState(V1state, V1note[V1index]);
        V2state = switchState(V2state, V2note[V2index]);
        Bstate = switchState(Bstate, Bnote[Bindex]);
        // update V1, V2, B buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzV2, V2state);
        digitalWrite(BuzzB, Bstate);
        // update V1, V2, B NST
        V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]);
        V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]);
        BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]);          
      } // end if
      else if((V1nextSwitchTime == minNextSwitchTime) && 
                 (V2nextSwitchTime == minNextSwitchTime)) { // update V1NST, V2NST
        // update V1, V2 states
        V1state = switchState(V1state, V1note[V1index]);
        V2state = switchState(V2state, V2note[V2index]);
        // update V1, V2 buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzV2, V2state);
        // update V1, V2 NST
        V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]);
        V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]);
      } // end else if
      else if((V1nextSwitchTime == minNextSwitchTime) && 
                  (BnextSwitchTime == minNextSwitchTime)) { // update V1NST, BNST 
        // update V1, B states
        V1state = switchState(V1state, V1note[V1index]);
        Bstate = switchState(Bstate, Bnote[Bindex]);
        // update V1, B buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzB, Bstate);
        // update V1, B NST
        V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]);
        BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); 
      } // end else if
      else if((V2nextSwitchTime == minNextSwitchTime) && 
                (BnextSwitchTime == minNextSwitchTime)) { // update V2NST, BNST
        // update V2, B states
        V2state = switchState(V2state, V2note[V2index]);
        Bstate = switchState(Bstate, Bnote[Bindex]);
        // update V2, B buzzers
        digitalWrite(BuzzV2, V2state);
        digitalWrite(BuzzB, Bstate);
        // update V2, b NST
        V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]);
        BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]);
      } // end else if
      else if(minNextSwitchTime == V1nextSwitchTime) { // update V1NST only
        V1state = switchState(V1state, V1note[V1index]); // update V1 state
        digitalWrite(BuzzV1, V1state); // update V1 buzzer
        V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
      } // end else if
      else if(minNextSwitchTime == V2nextSwitchTime) { // update V2NST only
        V2state = switchState(V2state, V2note[V2index]); // update V2 state
        digitalWrite(BuzzV2, V2state); // update V2 buzzer
        V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
      } // end else if
      else if(minNextSwitchTime == BnextSwitchTime) { // update BNST only
        Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
        digitalWrite(BuzzB, Bstate); // update B buzzer
        BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
      } // end else if

      // update max and min NST
      minNextSwitchTime = minVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime); 
      maxNextSwitchTime = maxVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime);
    } // end while


    // use an if statement to move V1NST, V2NST and BNST behind minNL
    if((BnextSwitchTime >= minNoteLength) && 
          (V1nextSwitchTime >= minNoteLength) &&
              (V2nextSwitchTime < minNoteLength)) { // when only BNST and V1NST are behind minBL
      // use while statement to move V2NST behind minBL
      while(V2nextSwitchTime < minNoteLength) {
        delayTime = V2nextSwitchTime - curLength; // calculate delay time in microseconds
        delayMicroseconds(delayTime); // delay for "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        V2state = switchState(V2state, V2note[V2index]); // update V2 state
        digitalWrite(BuzzV2, V2state); // update V2 buzzer
        V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
      } // end while
    } // end if
    else if((BnextSwitchTime >= minNoteLength) && 
              (V2nextSwitchTime >= minNoteLength) &&
                (V1nextSwitchTime < minNoteLength)) { // when only BNST and V2NST are behind minBL
      // use while statement to move V1NST behind minBL
      while(V1nextSwitchTime < minNoteLength) {
        delayTime = V1nextSwitchTime - curLength; // calculate delay time in microseconds
        delayMicroseconds(delayTime); // delay for "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        V1state = switchState(V1state, V1note[V1index]); // update V1 state
        digitalWrite(BuzzV1, V1state); // update V1 buzzer
        V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
      } // end while
    } // end else if
    else if((V1nextSwitchTime >= minNoteLength) && 
              (V2nextSwitchTime >= minNoteLength) &&
                (BnextSwitchTime < minNoteLength)) { // when only V1NST and V2NST are behind minBL
      // use while statement to move BNST behind minBL
      while(BnextSwitchTime < minNoteLength) {
        delayTime = BnextSwitchTime - curLength; // calculate delay time in microseconds
        delayMicroseconds(delayTime); // delay for "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
        digitalWrite(BuzzB, Bstate); // update B buzzer
        BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
      } // end while
    } // end else if
    else if((V1nextSwitchTime >= minNoteLength) && 
              (V2nextSwitchTime < minNoteLength) &&
                (BnextSwitchTime < minNoteLength)) { // when only V1NST is behind minBL
      // evaluate max and min NST between V2 and B
      maxNextSwitchTime = max(V2nextSwitchTime, BnextSwitchTime);
      minNextSwitchTime = min(V2nextSwitchTime, BnextSwitchTime);
      // use while loop to move (one or both) of (V2NST and BNST) behind minBL
      while(maxNextSwitchTime < minNoteLength) {
        // delay to minNST
        delayTime = minNextSwitchTime - curLength; // calculate delayTime in microseconds
        delayMicroseconds(delayTime); // delay "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        // use an if statement to update V2 and B NST
        if(V2nextSwitchTime == BnextSwitchTime) { // update both V2NST and BNST 
          // update V2 and B states
          V2state = switchState(V2state, V2note[V2index]); 
          Bstate = switchState(Bstate, Bnote[Bindex]);
          // update V2 and B buzzers
          digitalWrite(BuzzV2, V2state);
          digitalWrite(BuzzB, Bstate);
          // update V2 and B NST
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]);
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]);
        } // end if
        else if(minNextSwitchTime == V2nextSwitchTime) { // update V2NST only
          V2state = switchState(V2state, V2note[V2index]); // update V2 state
          digitalWrite(BuzzV2, V2state); // update V2 buzzers
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
        } // end else if
        else if(minNextSwitchTime == BnextSwitchTime) { // update BNST only
          Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
          digitalWrite(BuzzB, Bstate); // update B buzzer
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
        } // end else if
        // update max and min NST between V2 and B NST
        minNextSwitchTime = min(V2nextSwitchTime, BnextSwitchTime); 
        maxNextSwitchTime = max(V2nextSwitchTime, BnextSwitchTime);
        // (I repeated these two lines of code before the while loop because I needed
        //  the new max and min NST to enter the while loop)
      } // end while
      // use an if statement to move the remaining (V2NST or BNST) behind minBL
      if((BnextSwitchTime >= minNoteLength) && 
            (V2nextSwitchTime < minNoteLength)) { // when BNST is behind minBL
        // use while statement to move V2NST behind minBL
        while(V2nextSwitchTime < minNoteLength) {
          delayTime = V2nextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          V2state = switchState(V2state, V2note[V2index]); // update V2 state
          digitalWrite(BuzzV2, V2state); // update V2 buzzer
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
        } // end while
      } // end else if
      else if((V2nextSwitchTime >= minNoteLength) && 
                  (BnextSwitchTime < minNoteLength)) { // when V2NST is behind minBL
        // use while statement to move BNST behind minBL
        while(BnextSwitchTime < minNoteLength) {
          delayTime = BnextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
          digitalWrite(BuzzB, Bstate); // update B buzzer
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
        } // end while
      } // end else if
    } // end else if
    else if((V2nextSwitchTime >= minNoteLength) && 
              (V1nextSwitchTime < minNoteLength) &&
                (BnextSwitchTime < minNoteLength)) { // when only V2NST is behind minBL
      // evaluate max and min NST between V1 and B
      maxNextSwitchTime = max(V1nextSwitchTime, BnextSwitchTime);
      minNextSwitchTime = min(V1nextSwitchTime, BnextSwitchTime);
      // use while loop to (move one or both) of (V1NST and BNST) behind minBL
      while(maxNextSwitchTime < minNoteLength) {
        // delay to minNST
        delayTime = minNextSwitchTime - curLength; // calculate delayTime in microseconds
        delayMicroseconds(delayTime); // delay "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        // use an if statement to update V1 and B NST
        if(V1nextSwitchTime == BnextSwitchTime) { // update both V1NST and BNST 
          // update V1 and B state
          V1state = switchState(V1state, V1note[V1index]);
          Bstate = switchState(Bstate, Bnote[Bindex]);
          // update V1 and B buzzers
          digitalWrite(BuzzV1, V1state);
          digitalWrite(BuzzB, Bstate);
          // update V1 and B NST
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]);
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]);
        } // end if
        else if(minNextSwitchTime == V1nextSwitchTime) { // update V1NST only
          V1state = switchState(V1state, V1note[V1index]); // update V1 state
          digitalWrite(BuzzV1, V1state); // update V1 buzzers
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
        } // end else if
        else if(minNextSwitchTime == BnextSwitchTime) { // update BNST only
          Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
          digitalWrite(BuzzB, Bstate); // update B buzzer
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
        } // end else if
        // update max and min NST between V1 and B
        minNextSwitchTime = min(V1nextSwitchTime, BnextSwitchTime); 
        maxNextSwitchTime = max(V1nextSwitchTime, BnextSwitchTime);
      } // end while
      // use an if statement to move the remaining (V1NST or BNST) behind minBL
      if((BnextSwitchTime >= minNoteLength) && 
            (V1nextSwitchTime < minNoteLength)) { // when BNST is behind minBL
        // use while statement to move V1NST behind minBL
        while(V1nextSwitchTime < minNoteLength) {
          delayTime = V1nextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          V1state = switchState(V1state, V1note[V1index]); // update V1 state
          digitalWrite(BuzzV1, V1state); // update V1 buzzer
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
        } // end while
      } // end else if
      else if((V1nextSwitchTime >= minNoteLength) && 
                  (BnextSwitchTime < minNoteLength)) { // when V1NST is behind minBL
        // use while statement to move BNST behind minBL
        while(BnextSwitchTime < minNoteLength) {
          delayTime = BnextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          Bstate = switchState(Bstate, Bnote[Bindex]); // update B state
          digitalWrite(BuzzB, Bstate); // update B buzzer
          BnextSwitchTime = BnextSwitchTime + checkZero(Bnote[Bindex]); // update B NST
        } // end while
      } // end else if
    } // end else if
    else if((BnextSwitchTime >= minNoteLength) && 
              (V1nextSwitchTime < minNoteLength) &&
                (V2nextSwitchTime < minNoteLength)) { // when only BNST is behind minBL
      // evaluate max and min NST between V1 and V2 NST
      maxNextSwitchTime = max(V1nextSwitchTime, V2nextSwitchTime);
      minNextSwitchTime = min(V1nextSwitchTime, V2nextSwitchTime);
      // use while loop to move (one or both) of (V2NST and BNST) behind minBL
      while(maxNextSwitchTime < minNoteLength) {
        // delay to minNST
        delayTime = minNextSwitchTime - curLength; // calculate delayTime in microseconds
        delayMicroseconds(delayTime); // delay "delayTime" microseconds
        curLength = curLength + delayTime; // update curLength by adding delayTime
        // use an if statement to update V1 and V2 NST
        if(V1nextSwitchTime == V2nextSwitchTime) { // update both V1NST and V2NST
          // update V1 and V2 state
          V1state = switchState(V1state, V1note[V1index]);
          V2state = switchState(V2state, V2note[V2index]);
          // update V1 and V2 buzzers
          digitalWrite(BuzzV1, V1state);
          digitalWrite(BuzzV2, V2state);
          // update V1 and V2 NST
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]);
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]);
        } // end if
        else if(minNextSwitchTime == V1nextSwitchTime) { // update V1NST only
          V1state = switchState(V1state, V1note[V1index]); // update V1 state
          digitalWrite(BuzzV1, V1state); // update V1 buzzer
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
        } // end else if
        else if(minNextSwitchTime == V2nextSwitchTime) { // update V2NST only
          V2state = switchState(V2state, V2note[V2index]); // update V2 state
          digitalWrite(BuzzV2, V2state); // update V2 buzzer
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
        } // end else if
        // update max and min NST between V1 and V2
        minNextSwitchTime = min(V1nextSwitchTime, V2nextSwitchTime); 
        maxNextSwitchTime = max(V1nextSwitchTime, V2nextSwitchTime);
      } // end while
      // use an if statement to move the remaining (V2NST or BNST) behind minBL
      if((V2nextSwitchTime >= minNoteLength) && 
            (V1nextSwitchTime < minNoteLength)) { // when V2NST is behind minBL
        // use while statement to move V1NST behind minBL
        while(V1nextSwitchTime < minNoteLength) {
          delayTime = V1nextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          V1state = switchState(V1state, V1note[V1index]); // update V1 state
          digitalWrite(BuzzV1, V1state); // update V1 buzzer
          V1nextSwitchTime = V1nextSwitchTime + checkZero(V1note[V1index]); // update V1 NST
        } // end while
      } // end else if
      else if((V1nextSwitchTime >= minNoteLength) && 
                  (V2nextSwitchTime < minNoteLength)) { // when V1NST is behind minBL
        // use while statement to move V2NST behind minBL
        while(V2nextSwitchTime < minNoteLength) {
          delayTime = V2nextSwitchTime - curLength; // calculate delayTime in microseconds
          delayMicroseconds(delayTime); // delay for "delayTime" microseconds
          curLength = curLength + delayTime; // update curLength by adding delayTime
          V2state = switchState(V2state, V2note[V2index]); // update V2 state
          digitalWrite(BuzzV2, V2state); // update V2 buzzer
          V2nextSwitchTime = V2nextSwitchTime + checkZero(V2note[V2index]); // update V2 NST
        } // end while
      } // end else if
    } // end else if    
    // update curLength to minBL
    delayTime = minNoteLength - curLength; // calculate delayTime in microseconds
    delayMicroseconds(delayTime); // delay for "delayTime" microseconds
    curLength = minNoteLength; // update curLength

    // use an if to update all variables when the beat is not over (curLength < beatLength)
    if(curLength != BEATLENGTH) {
      // use an if to prepare all variables before changing any note(s)
      if((V1noteLength == minNoteLength) &&
            (V2noteLength == minNoteLength) &&
              (BnoteLength == minNoteLength)) { // if all V1, V2, B need to be updated
        // update all index
        V1index = V1index + 1;
        V2index = V2index + 1;
        Bindex = Bindex + 1;
        // update all noteLength
        V1noteLength = V1noteLength + (BEATLENGTH / 16 * V1beat[V1index]);
        V2noteLength = V2noteLength + (BEATLENGTH / 16 * V2beat[V2index]);
        BnoteLength = BnoteLength + (BEATLENGTH / 16 * Bbeat[Bindex]);
        // update all NST
        V1nextSwitchTime = minNoteLength + checkZero(V1note[V1index]);
        V2nextSwitchTime = minNoteLength + checkZero(V2note[V2index]);
        BnextSwitchTime = minNoteLength + checkZero(Bnote[Bindex]);
        // update all state
        V1state = LOW;
        V2state = LOW;
        Bstate = LOW;
        // update all buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzV2, V2state);
        digitalWrite(BuzzB, Bstate);
      } // end if
      else if((V1noteLength == minNoteLength) &&
                 (V2noteLength == minNoteLength)){ // when V1 and V2 need to be updated
        // update V1 and V2 index
        V1index = V1index + 1;
        V2index = V2index + 1;
        // update V1 and V2 noteLength
        V1noteLength = V1noteLength + (BEATLENGTH / 16 * V1beat[V1index]);
        V2noteLength = V2noteLength + (BEATLENGTH / 16 * V2beat[V2index]);
        // update V1 and V2 NST
        V1nextSwitchTime = minNoteLength + checkZero(V1note[V1index]);
        V2nextSwitchTime = minNoteLength + checkZero(V2note[V2index]);
        // update V1 and V2 states
        V1state = LOW;
        V2state = LOW;
        // update V1 and V2 buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzV2, V2state);
      } // end else if
      else if((V1noteLength == minNoteLength) &&
                 (BnoteLength == minNoteLength)){ // when V1 and B need to be updated
        // update V1 and B index
        V1index = V1index + 1;
        Bindex = Bindex + 1;
        // update V1 and B noteLength
        V1noteLength = V1noteLength + (BEATLENGTH / 16 * V1beat[V1index]);
        BnoteLength = BnoteLength + (BEATLENGTH / 16 * Bbeat[Bindex]);
        // update V1 and B NST
        V1nextSwitchTime = minNoteLength + checkZero(V1note[V1index]);
        BnextSwitchTime = minNoteLength + checkZero(Bnote[Bindex]);
        // update V1 and B states
        V1state = LOW;
        Bstate = LOW;
        // update V1 and B buzzers
        digitalWrite(BuzzV1, V1state);
        digitalWrite(BuzzB, Bstate);
      } // end else if
      else if((BnoteLength == minNoteLength) &&
                 (V2noteLength == minNoteLength)){ // when V2 and B need to be updated
        // update V2 and B index
        V2index = V2index + 1;
        Bindex = Bindex + 1;
        // update V2 and B noteLength
        V2noteLength = V2noteLength + (BEATLENGTH / 16 * V2beat[V2index]);
        BnoteLength = BnoteLength + (BEATLENGTH / 16 * Bbeat[Bindex]);
        // update V2 and B NST
        V2nextSwitchTime = minNoteLength + checkZero(V2note[V2index]);
        BnextSwitchTime = minNoteLength + checkZero(Bnote[Bindex]);
        // update V2 and B states
        V2state = LOW;
        Bstate = LOW;
        // update V2 and B buzzers
        digitalWrite(BuzzV2, V2state);
        digitalWrite(BuzzB, Bstate);
      } // end else if
      else if(minNoteLength == V1noteLength) { // update V1
        V1index = V1index + 1; // update V1 index
        V1noteLength = V1noteLength + (BEATLENGTH / 16 * V1beat[V1index]); // update V1 noteLength
        V1nextSwitchTime = minNoteLength + checkZero(V1note[V1index]); // update V1 NST
        V1state = LOW; // update V1 state
        digitalWrite(BuzzV1, V1state); // update V1 buzzer
      } // end else if
      else if(minNoteLength == V2noteLength) { // update V2
        V2index = V2index + 1; // update V2 index
        V2noteLength = V2noteLength + (BEATLENGTH / 16 * V2beat[V2index]); // update V2 noteLength
        V2nextSwitchTime = minNoteLength + checkZero(V2note[V2index]); // update V2 NST
        V2state = LOW; // update V2 state
        digitalWrite(BuzzV2, V2state); // update V2 buzzer
      } // end else if
      else if(minNoteLength == BnoteLength) { // update B
        Bindex = Bindex + 1; // update B index
        BnoteLength = BnoteLength + (BEATLENGTH / 16 * Bbeat[Bindex]); // update B noteLength
        BnextSwitchTime = minNoteLength + checkZero(Bnote[Bindex]); // update B state
        Bstate = LOW; // update B state
        digitalWrite(BuzzB, Bstate); // update B buzzer
      } // end else if
      
      // update all max and min NST and noteLength
      minNextSwitchTime = minVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime);
      maxNextSwitchTime = maxVal(V1nextSwitchTime, V2nextSwitchTime, BnextSwitchTime);
      minNoteLength = minVal(V1noteLength, V2noteLength, BnoteLength);
      maxNoteLength = maxVal(V1noteLength, V2noteLength, BnoteLength);

      // display V1, V2, B note names on the LCD screen
      // display.clearDisplay();
      // display.setTextSize(1);
      // display.setTextColor(WHITE);
      // display.setCursor(0, 0);
      // display.print(displayNote(V1note[V1index])); // display V1 note name
      // display.setCursor(50, 0);
      // display.print(displayNote(V2note[V2index])); // display V1 note name
      // display.setCursor(100, 0);
      // display.println(displayNote(Bnote[Bindex])); // display V1 note name
      // display.display(); 

    } // end if
    else { // update maxNL to exit the loop
      maxNoteLength = maxNoteLength + 1;
    } // end else
  } // end while (outer)
  return;
} // end play()
byte switchState(byte curState, int note) {
  byte nextState = LOW; // create and initialize a byte variable for return
  if(note == 0) // if it is a rest note
    nextState = LOW; // always keeps the buzzer off 
  else { // if it is not a rest note
    if(curState == LOW) // when the buzzer is off
      nextState = HIGH; // turn it on 
  }
  return nextState; // return the next state of the buzzer
} // end switchState()

/******************************* minVal FUNCTION ********************************/
/*    The minVal() function can return the minimum value out of three values.
 *    It takes in three long variables and returns a long variable.
 */
long minVal(long val1, long val2, long val3) {
  long minimum = 0; // create and initialize a return value
  minimum = min((min(val1, val2)), val3); // find the minimum
  return minimum; // return the minimum
} // end minVal()


/******************************* maxVal FUNCTION ********************************/
/*    The maxVal() function can return the maximum value out of three values.
 *    It takes in three long variables and returns a long variable.
 */
long maxVal(long val1, long val2, long val3) {
  long maximum = 0; // create and initialize a return value
  maximum = max((max(val1, val2)), val3); // find the maximum
  return maximum; // return the maximum
} // end maxVal()

/******************************* checkZero FUNCTION ********************************/
/*    The checkZero() function can return the note period(int) for both rest notes and 
 * regular notes. Without this function, the program will skip the rest note instead
 * of delaying for the rest note length.
 *    The checkZwro() function takes in a note period, then evaluate the note type. 
 * If it is a regular note, the function will return its original period.
 * If it is a rest note, the function will set the note period to 10000.
 * (I tried setting this value to (BEATLENGTH / 16) but the outcome is rushing). 
 */
int checkZero(int note) {
  int period = 0; // create and initialize a return value
  if(note == 0) // if it is a rest note
    period = 10000; // set its period to 10000
  else // if it is a regular note
    period = note; // return its period
  return period; // return period
} // end checkZero()