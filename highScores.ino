void drawScore(byte level, int weight, unsigned long score, byte y1, byte y2) {
  arduboy.setCursor(39, y1);
  arduboy.print("LVL ");
  arduboy.print(level);
  arduboy.print(" WT. ");
  arduboy.print(weight);
  arduboy.print(" lb");
  arduboy.setCursor(39, y2);
  arduboy.print("SCORE:");
  arduboy.print(score);
}

void highScores() {
  arduboy.setCursor(49, 1);
  arduboy.print("BEST CHUNGUS");

  arduboy.setTextSize(2);
  for (byte z = 0; z < 3; z++) {
    arduboy.setCursor(0 + (12 * z), 11);
    arduboy.print(highscores.nameOne[z]);
    arduboy.setCursor(0 + (12 * z), 29);
    arduboy.print(highscores.nameTwo[z]);
    arduboy.setCursor(0 + (12 * z), 48);
    arduboy.print(highscores.nameThree[z]);
  }
  arduboy.setTextSize(1);
  drawScore(highscores.levelOne, highscores.weightOne, highscores.scoreOne, 11, 19);
  drawScore(highscores.levelTwo, highscores.weightTwo, highscores.scoreTwo, 29, 37);
  drawScore(highscores.levelThree, highscores.weightThree, highscores.scoreThree, 48, 56);
  if (arduboy.justPressed(B_BUTTON) || arduboy.justPressed(A_BUTTON)) {
    theGame.gamestate = 0;
  }
}
