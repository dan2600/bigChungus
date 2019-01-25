//Check if they wanna skip the awesome intro
bool skipIntro() {
  arduboy.pollButtons();
  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
    theGame.gamestate = 2;
    tunes.stopScore();
    return true;
  }
  return false;
}

//Intro Sequence
void introSequence() {
  arduboy.display();
  delay(1000);
  if (skipIntro()) return;
  arduboy.setCursor(43, 20);
  arduboy.print("dan2600");
  arduboy.setCursor(40, 30);
  arduboy.print("Presents");
  arduboy.display();
  delay(2000);
  if (skipIntro()) return;
  tunes.stopScore();
  tunes.playScore(ite);
  for (int i = 0; i < 116; i++)
  {
    arduboy.drawBitmap(0, -128 + i, introGfx, 128, 192, WHITE);
    arduboy.display();
    arduboy.clear();
    if (skipIntro()) return;
    delay(40);
  }
  delay(200);
  arduboy.drawBitmap(2, 18, chungsT, 123, 31, WHITE);
  arduboy.display();
  for (int i = 200; i < 2500; i += 50)
  {
    flashScreen(2, 10);
  }
  delay(1500);
  tunes.stopScore();
  theGame.gamestate = 2;
}
