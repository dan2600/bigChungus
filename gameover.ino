bool changed = false;
bool inputName = false;
char nameInput[3] = "   ";

bool scoreChecker(unsigned long scored) {
  if (changed)
  {
    return false;
  }
  if (scored < theGame.score)
  {
    changed = true;
    inputName = true;
    return true;
  }
  return false;
}

void gameOver() {
  int place = 0;
  while (true) {
    if (scoreChecker(highscores.scoreOne))
    {
      highscores.scoreThree = highscores.scoreTwo;
      strcpy(highscores.nameThree, highscores.nameTwo);
      highscores.weightThree = highscores.weightTwo;
      highscores.levelThree = highscores.levelTwo;
      highscores.scoreTwo = highscores.scoreOne;
      strcpy(highscores.nameTwo, highscores.nameOne);
      highscores.weightTwo = highscores.weightOne;
      highscores.levelTwo = highscores.levelOne;
      highscores.scoreOne = theGame.score;
      highscores.weightOne = thePlayer.weight;
      highscores.levelOne = theGame.level;
      place = 1;
      break;
    }
    if (scoreChecker(highscores.scoreTwo))
    {
      highscores.scoreThree = highscores.scoreTwo;
      strcpy(highscores.nameThree, highscores.nameTwo);
      highscores.weightThree = highscores.weightTwo;
      highscores.levelThree = highscores.levelTwo;
      highscores.scoreTwo = theGame.score;
      highscores.weightTwo = thePlayer.weight;
      highscores.levelTwo = theGame.level;
      place = 2;
      break;
    }
    if (scoreChecker(highscores.scoreThree))
    {
      highscores.scoreThree = theGame.score;
      highscores.weightThree = thePlayer.weight;
      highscores.levelThree = theGame.level;
      place = 3;
      break;
    }
    break;
  }

  arduboy.clear();
  arduboy.fillRect(0, 30, 80, 34, WHITE);
  arduboy.drawBitmap(128 - 50, 0, endScreen, 50, 64, WHITE);
  arduboy.setTextBackground(BLACK);
  arduboy.setCursor(0, 0);
  arduboy.print("GAME OVER");
  arduboy.setCursor(2, 32);
  arduboy.print("Level: ");
  arduboy.print(theGame.level);
  arduboy.setCursor(2, 40);
  arduboy.print("Score: ");
  arduboy.print(theGame.score);
  arduboy.setCursor(2, 48);
  arduboy.print("Weight:");
  arduboy.print(thePlayer.weight);
  arduboy.print(" lb");
  arduboy.display();
  for (int i = 700; i > 200; i -= 50)
  {

    tunes.tone(random(200, i), 56);
    delay(60);
  }
  while (true) {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      break;
    }
  }
  if (place == 0) {
    theGame.gamestate = 8;
    return;
  }
  else
  {
    tunes.playScore(godzill);
    bool tester = true;
    byte cursLoc = 0;
    nameInput[cursLoc] = 65;
    while (tester) {
      arduboy.clear();
      arduboy.drawBitmap(1, 0, biggestC, 123, 16, WHITE);
      switch (place) {
        case 0:
          arduboy.setCursor(2, 20);
          arduboy.print("ERROR");
          break;
        case 1:
          arduboy.setCursor(12, 20);
          arduboy.print("NEW GRAND CHUNGUS");
          break;
        case 2:
          arduboy.setCursor(31, 20);
          arduboy.print("2ND PLACE");
          break;
        case 3:
          arduboy.setCursor(31, 20);
          arduboy.print("3RD PLACE");
          break;
      }
      arduboy.setCursor(19, 56);
      arduboy.print("INPUT INTIALS");
      arduboy.setTextSize(2);
      arduboy.setCursor(39, 34);
      arduboy.print(nameInput[0]);
      arduboy.setCursor(55, 34);
      arduboy.print(nameInput[1]);
      arduboy.setCursor(71, 34);
      arduboy.print(nameInput[2]);
      arduboy.setTextSize(1);
      switch (cursLoc) {
        case 0:
          arduboy.fillRect(39, 50, 10, 2, WHITE);
          break;
        case 1:
          arduboy.fillRect(55, 50, 10, 2, WHITE);
          break;
        case 2:
          arduboy.fillRect(71, 50, 10, 2, WHITE);
          break;
      }
      arduboy.pollButtons();
      if (arduboy.justPressed(LEFT_BUTTON))
      {
        if (cursLoc == 0) cursLoc = 3;
        cursLoc--;
      }
      if (arduboy.justPressed(RIGHT_BUTTON))
      {

        if (cursLoc == 2) cursLoc = 0;
        else cursLoc++;
      }
      if (arduboy.justPressed(B_BUTTON))
      {
        nameInput[cursLoc] = 32;
        if (cursLoc > 0) --cursLoc;
      }
      if (arduboy.justPressed(A_BUTTON))
      {
        if (cursLoc == 2) {
          switch (place) {
            case 1:
              strcpy(highscores.nameOne, nameInput);
              highscores.scoreOne = theGame.score;
              break;
            case 2:
              strcpy(highscores.nameTwo, nameInput);
              highscores.scoreTwo = theGame.score;
              break;
            case 3:
              strcpy(highscores.nameThree, nameInput);
              highscores.scoreThree = theGame.score;
              break;
          }
          EEPROM.put(EEPROM_SCORE, highscores);
          flashScreen(5, 100);
          changed = false;
          inputName = false;
          nameInput[0] = 32;
          nameInput[1] = 32;
          nameInput[2] = 32;
          delay(200);
          theGame.gamestate = 8;
          tester = false;
        }
        else {
          ++cursLoc;
          nameInput[cursLoc] = 65;
        }
      }
      if (arduboy.pressed(UP_BUTTON))
      {
        switch (nameInput[cursLoc])
        {
          case 32:
            nameInput[cursLoc] = 65;
            break;
          case 90:
            nameInput[cursLoc] = 32;
            break;
          default:
            ++nameInput[cursLoc];
        }
        delay(100);
      }
      if (arduboy.pressed(DOWN_BUTTON))
      {
        switch (nameInput[cursLoc])
        {
          case 32:
            nameInput[cursLoc] = 90;
            break;
          case 65:
            nameInput[cursLoc] = 32;
            break;
          default:
            --nameInput[cursLoc];
        }
        delay(100);
      }
      arduboy.display();
    }
   // tunes.stopScore();
  }
}
