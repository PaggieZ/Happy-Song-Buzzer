/******************************* displayNote FUNCTION ********************************/
/*    The displayNote() function can return the note name(string) for both rest notes and 
 * regular notes. The function is designed to display notes for music in A flat major.
 *    The displayNote() function takes in a note period, then evaluate the note type. 
 * If it is a regular note, the function will return its note name.
 * If it is a rest note, the function will return a space. 
 */
#include "pitches.h"
// use a switch statement to assign a note name for each note period.
String displayNote(int note){
  switch(note) {
    case 0: // rest note
      return "   ";
    case C0:
      return "C0 ";
    case Db0:
      return "Db0";
    case D0:
      return "D0 ";
    case Eb0:
      return "Eb0";
    case E0:
      return "E0 ";
    case F0:
      return "F0 ";
    case Fs0:
      return "F#0";
    case G0:
      return "G0 ";
    case Ab0:
      return "Ab0";
    case A0:
      return "A0 ";
    case Bb0:
      return "Bb0";
    case B0:
      return "B0 "; ////////////////////////////////////0
    case C1:
      return "C1 ";
    case Db1:
      return "Db1";
    case D1:
      return "D1 ";
    case Eb1:
      return "Eb1";
    case E1:
      return "E1 ";
    case F1:
      return "F1 ";
    case Fs1:
      return "F#1";
    case G1:
      return "G1 ";
    case Ab1:
      return "Ab1";
    case A1:
      return "A1 ";
    case Bb1:
      return "Bb1";
    case B1:
      return "B1 "; ////////////////////////////////////////////////1 
    case C2:
      return "C2 ";
    case Db2:
      return "Db2";
    case D2:
      return "D2 ";
    case Eb2:
      return "Eb2";
    case E2:
      return "E2 ";
    case F2:
      return "F2 ";
    case Fs2:
      return "F#2";
    case G2:
      return "G2 ";
    case Ab2:
      return "Ab2";
    case A2:
      return "A2 ";
    case Bb2:
      return "Bb2";
    case B2:
      return "B2 "; //////////////////////////////////////////2
    case C3:
      return "C3 ";
    case Db3:
      return "Db3";
    case D3:
      return "D3 ";
    case Eb3:
      return "Eb3";
    case E3:
      return "E3 ";
    case F3:
      return "F3 ";
    case Fs3:
      return "F#3";
    case G3:
      return "G3 ";
    case Ab3:
      return "Ab3";
    case A3:
      return "A3 ";
    case Bb3:
      return "Bb3";
    case B3:
      return "B3 "; /////////////////////////////////////////3
    case C4:
      return "C4 ";
    case Db4:
      return "Db4";
    case D4:
      return "D4 ";
    case Eb4:
      return "Eb4";
    case E4:
      return "E4 ";
    case F4:
      return "F4 ";
    case Fs4:
      return "F#4";
    case G4:
      return "G4 ";
    case Ab4:
      return "Ab4";
    case A4:
      return "A4 ";
    case Bb4:
      return "Bb4";
    case B4:
      return "B4 "; /////////////////////////////4
    case C5:
      return "C5 ";
    case Db5:
      return "Db5";
    case D5:
      return "D5 ";
    case Eb5:
      return "Eb5";
    case E5:
      return "E5 ";
    case F5:
      return "F5 ";
    case Fs5:
      return "F#5";
    case G5:
      return "G5 ";
    case Ab5:
      return "Ab5";
    case A5:
      return "A5 ";
    case Bb5:
      return "Bb5";
    case B5:
      return "B5 "; ////////////////////////////5
    case C6:
      return "C6 ";
    case Db6:
      return "Db6";
    case D6:
      return "D6 ";
    case Eb6:
      return "Eb6";
    case E6:
      return "E6 ";
    case F6:
      return "F6 ";
    case Fs6:
      return "F#6";
    case G6:
      return "G6 ";
    case Ab6:
      return "Ab6";
    case A6:
      return "A6 ";
    case Bb6:
      return "Bb6";
    case B6:
      return "B6 "; //////////////////////////////////6
    case C7:
      return "C7 ";
    case Db7:
      return "Db7";
    case D7:
      return "D7 ";
    case Eb7:
      return "Eb7";
    case E7:
      return "E7 ";
    case F7:
      return "F7 ";
    case Fs7:
      return "F#7";
    case G7:
      return "G7 ";
    case Ab7:
      return "Ab7";
    case A7:
      return "A7 ";
    case Bb7:
      return "Bb7";
    case B7:
      return "B7 ";  //////////////////////////////7  
    case C8:
      return "C8 ";
    case Db8:
      return "Db8";
    case D8:
      return "D8 ";
    case Eb8:
      return "Eb8";
    case E8:
      return "E8 ";
    case F8:
      return "F8 ";
    case Fs8:
      return "F#8";
    case G8:
      return "G8 ";
    case Ab8:
      return "Ab8";
    case A8:
      return "A8 ";
    case Bb8:
      return "Bb8";
    case B8:
      return "B8 ";
  } // end switch
} // end displayNote()