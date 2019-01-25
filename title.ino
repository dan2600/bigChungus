//Title Screen
void title() {
  if (!tunes.playing())
    tunes.playScore(titles);
  bool optionSelect = false;
  while (true)
  {

    arduboy.clear();
    arduboy.drawBitmap(27, 3, titleBig, 39, 18, WHITE);
    arduboy.drawBitmap(27, 25, titleChungus, 103, 18, WHITE);
    arduboy.drawBitmap(0, 2, chungside, 25, 61, WHITE);
    arduboy.setCursor(35, 51);
    arduboy.print("START");
    arduboy.setCursor(79, 51);
    arduboy.print("OPTIONS");
    if (!optionSelect)
    {
      arduboy.fillRect(35, 59, 30, 2, WHITE);
    }
    else if (optionSelect)
    {
      arduboy.fillRect(79, 59, 42, 2, WHITE);
    }
    arduboy.pollButtons();
    if (arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) {
      optionSelect = !optionSelect;
    }
    arduboy.display();
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      break;
    }
  }
  if (optionSelect)
  {
    tunes.stopScore();
    for (int i = 50; i > 0; i--)
    {
      tunes.tone(random(400, 700), 4);
      flashScreen(2, 2);
    }
    theGame.gamestate = 3;
  }
  else
  {
    tunes.stopScore();

    for (int i = 50; i > 0; i--)
    {
      tunes.tone(random(400, 700), 4);
      flashScreen(2, 2);
    }

    theGame.lives = 3;
    theGame.score = 0;
    theGame.level = 1;
    theGame.feet = 1700 + (120 * theGame.level);
    thePlayer.weight = 5;
    theGame.gamestate = 4;
    thePlayer.x = 0;
    thePlayer.y = 35;
  }
}
