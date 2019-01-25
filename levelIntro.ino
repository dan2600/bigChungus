//Start up the level and play the intro
void levelIntro() {
  if(theGame.lives == 0)
  {
    theGame.gamestate = 7;
    return;
  }
      for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
        obstacles[i].isActive = false;
        obstacles[i].y = 44;
      }
      thePlayer.targetweight = 5 * (theGame.level+1);      
      arduboy.setFrameRate(56 + (4*theGame.level));
      arduboy.setCursor(45, 0);
      arduboy.print("Level ");
      arduboy.print(theGame.level);
      arduboy.setCursor(45, 10);
      arduboy.print("Lives ");
      arduboy.print(theGame.lives);
      arduboy.setCursor(15, 20);
      arduboy.print("Target Weight ");
      arduboy.print(thePlayer.targetweight);
      arduboy.print("lb");      
      arduboy.setCursor(30, 30);
      arduboy.print("Feet Left: ");
      arduboy.print(theGame.feet);
      if(arduboy.everyXFrames(3) && thePlayer.x < 64)
      {
        thePlayer.x+=2;
        animatePlayer();
      }
      else if(thePlayer.x == 64)
      {
      thePlayer.playerFrame = 0;
      arduboy.setCursor(45, 54);
      arduboy.print("Press A");
      }
      sprites.drawSelfMasked(thePlayer.x, 40, playerSmall, thePlayer.playerFrame);
    if(arduboy.justPressed(A_BUTTON)){
      theGame.gamestate = 5;
      thePlayer.x = 15;
      thePlayer.y = 64 - 12 - getImageHeight(thePlayer.image) ;
      
      }
  }
