//This Game is called Big Chungus
//by @dan2600
//In the Year 2019



//Define some structs for Chungs (the game) Player (The Player) Wall (Wall Objects) Carrot (Carrots) High Scores (Obvious)
struct CHUNGUS {
  byte level;
  byte lives;
  int feet;
  byte gamestate;
  unsigned long score;
};
struct PLAYER {
  int x;
  int y;
  byte yVel;
  unsigned int weight;
  unsigned int targetweight;
  byte playerFrame;
  bool jumping;
  bool falling;
  bool chungused;
  const byte *image;
};
struct WALL {
  int x;
  byte y;
  bool isActive;
  byte type;
  bool scored;
  const byte *image;
};
struct CARROT {
  int x;
  byte y;
  bool isActive;
  const byte *image;
};
struct THEHIGHSCORES {
  char nameOne[3];
  unsigned long scoreOne;
  byte levelOne;
  unsigned int weightOne;
  char nameTwo[3];
  unsigned long scoreTwo;
  byte levelTwo;
  unsigned int weightTwo;
  char nameThree[3];
  unsigned long scoreThree;
  byte levelThree;
  unsigned int weightThree;
};


//Import the stuff and define the objects
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
THEHIGHSCORES highscores;
#include "sprites.h"
#include "epp.h"
Arduboy2 arduboy;
Sprites sprites;
ArduboyPlaytune tunes(arduboy.audio.enabled);
CHUNGUS theGame;
PLAYER thePlayer = {0, 0, 0, 0, false, false, false, playerSmall};


//Some Helpful Functions

void animatePlayer() {
  thePlayer.playerFrame++;
  if (thePlayer.playerFrame > 3)
  {
    thePlayer.playerFrame = 0;
  }
}

void flashScreen(int numLoops, int delaySpeed) {
  for (int z = 0; z < numLoops; z++) {
    arduboy.invert(true);
    delay(delaySpeed);
    arduboy.invert(false);
    delay(delaySpeed);
  }
}

//Setup

void setup() {
  initEEPROM();
  EEPROM.get(EEPROM_SCORE, highscores);
  theGame.level = 1;
  theGame.feet = 1700 + (120 * theGame.level);
  theGame.score = 0;
  theGame.lives = 3;
  thePlayer.image = playerSmall;
  thePlayer.playerFrame = 0;
  arduboy.begin();
  arduboy.setFrameRate(60);
  randomSeed(analogRead(0));
  arduboy.clear();
  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.initChannel(PIN_SPEAKER_2);
}
//Main Loop
void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.pollButtons();
  arduboy.clear();
  switch ( theGame.gamestate ) {
    case 0:
      //Intro
      introSequence();
      break;
    case 2:
      //Title
      title();
      break;
    case 3:
      //Options
      optionsScreen();
      break;
    case 4:
      //Level Intro
      levelIntro();
      break;
    case 5:
      //Gameplay
      gamePlay();
      break;
    case 6:
      //Level Win
      winLevel();
      break;
    case 7:
      //Game Over
      gameOver();
      break;
    case 8:
      //High Scores
      highScores();
      break;
  }
  arduboy.display();
}
