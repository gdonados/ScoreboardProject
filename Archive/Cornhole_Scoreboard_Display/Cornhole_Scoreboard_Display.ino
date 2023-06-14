#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

/////////////////////
// Hardware Hookup //
/////////////////////
// R0, G0, B0, R1, G1, B1 should be connected to pins
// 2, 3, 4, 5, 6, and 7 respectively. Their pins aren't defined,
// because they're controlled directly in the library. These pins
// can be moved (somewhat):

// CLK be on PORTB!
// CLK can be moved but must remain on PORTB(8, 9, 10, 11, 12, 13)
#define CLK 11
#define LAT 10
#define OE  9

#define A   A0
#define B   A1
#define C   A2
#define D   A3 // Comment this line out if you're using a 32x16

//Variable used for communication bewteen bluetooth modules
char c = ' ';

/*IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
*/

/* ========== For 32x64 LED panels: ==========
  You MUST use an Arduino Mega2560 with 32x64 size RGB Panel */
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64); // 32x64

////////////////////
//Cursor Variables//
////////////////////
const int idealX = 3;
const int idealY = 9;
int cursorX;
int cursorY;
bool scoreChange = false;



///////////////////
//Score Variables//
///////////////////
int leftTeamScore = 0;
int rightTeamScore = 0;
String scoreString;

void setup() {
  Serial.begin(9600);

  Serial1.begin(9600);
  
  matrix.begin();
  
  matrix.setCursor(3, 9); //sets cursor
  matrix.setTextSize(2);
  
  scoreChange = true;
  
 // matrix.setTextColor(3); //for testing #3, not bright, dull blue
 // matrix.setTextColor(matrix.Color333(7, 0, 0)); //sets color to red
  //matrix.print("00-00"); //prints basic 00 - 00 

  updateDisplay();
}

void loop() {
  
  if(Serial1.available())
  {
    c = Serial1.read();
    Serial.println(c); //*****************may need to be on master
    //Serial.print(c);

    switch(c)
    {
      case 'U':
        leftTeamScore++;
        scoreChange = true;
        break;
      case 'I':
        leftTeamScore--;
        scoreChange = true;
        break;
      case 'T':
        leftTeamScore = 11;
        scoreChange = true;
        break;
      case 'E':
        rightTeamScore++;
        scoreChange = true;
        break;
      case 'R':
        rightTeamScore--;
        scoreChange = true;
        break;
      case 'Q':
        rightTeamScore = 11;
        scoreChange = true;
        break;
      case 'W':
        leftTeamScore = 0;
        rightTeamScore = 0;
        scoreChange = true;
        break;
    }
  }

  updateDisplay();
}

/////////////
//Functions//
/////////////

void updateDisplay()
{
  ///////////////////////////////////////////
  //ONLY UPDATE DISLAY IF THE SCORE CHANGES//
  ///////////////////////////////////////////
  if(scoreChange)
  {
    if(leftTeamScore < 1)
    {
      leftTeamScore = 0;
    }

    if(rightTeamScore < 1)
    {
      rightTeamScore = 0;
    }
    
    //scoreString = formatScore(leftTeamScore) + '-' + formatScore(rightTeamScore);
    
    matrix.fillScreen(0);
    matrix.setCursor(3, 9);
    scoreChange = false;
    //matrix.print(scoreString);

    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(formatScore(leftTeamScore));
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print('-');
    matrix.setTextColor(matrix.Color333(0, 4, 7));
    matrix.print(formatScore(rightTeamScore));
  }

  
}


// Reset the screen. Set cursors back to top-left. Reset oldColor
// and blank the screen.
void blankEasel()
{
  cursorX = 0;
  cursorY = 0;
  matrix.fillScreen(0); // Blank screen
}

String formatScore(int score)
{
  if(score < 10)
  {
    return '0' + String(score);
  }

  else
  {
    return String(score);
  }
}
