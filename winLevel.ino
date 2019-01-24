
void updateScore() {
  arduboy.setCursor(35, 42);
  arduboy.print("Score: ");
  arduboy.print(theGame.score);
  arduboy.display();
}

void winLevel() {
  tunes.stopScore();
  for(byte i = 0; i < 105; i++){
  arduboy.clear();
  arduboy.drawBitmap(0, 0 - i, introGfx, 128, 192, WHITE);
  arduboy.display();
  delay(10);
  }
  arduboy.setTextBackground(BLACK);
  updateScore();
  arduboy.display();
  delay(500);
    arduboy.setCursor(35, 10);
    arduboy.print("Weight Bonus:");
    arduboy.setCursor(35, 18);
    arduboy.print(thePlayer.weight);
    arduboy.print("kg x ");
    arduboy.print(100 * theGame.level);
      theGame.score += thePlayer.weight * (100 * theGame.level);
      updateScore();
      arduboy.display();
      delay(1000);
    if (thePlayer.chungused)
    {
      arduboy.setCursor(35, 26);
      arduboy.print("Chungus Bonus:");
      arduboy.setCursor(35, 34);
      arduboy.print(1000 * theGame.level);

        theGame.score += 1000 * theGame.level;
        updateScore();
        arduboy.display();
        updateScore();      
  }
  arduboy.display();
  while (!arduboy.justPressed(A_BUTTON) && !arduboy.justPressed(B_BUTTON)) {
   arduboy.pollButtons();
  }
    theGame.level++;
    theGame.feet = 1700 + (120 * theGame.level);
    theGame.gamestate = 4;
}
