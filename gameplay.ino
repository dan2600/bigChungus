//Main gameplay


#define NUMBER_OF_OBSTACLES 3
byte inviTimer = 120;
int jumpHeight = 0;
byte tileoffset = 0;
int scoreSound = 0;
bool makeSound = false;
unsigned int chungusbonus = 0;
byte chungusHelp = 0;
unsigned int obstacleLaunchCountdown = 60;
unsigned int carrotCountdown = 120;
WALL obstacles[NUMBER_OF_OBSTACLES] = {
  {
    148,
    44,
    0,
    0,
    0,
    obst
  },
  {
    148,
    44,
    0,
    0,
    0,
    obst
  },
  {
    148,
    44,
    0,
    0,
    0,
    obst
  },
};
CARROT carrot = {
  0,
  0,
  0,
  carrotImg
};

//Ground Animation Function
void animateGround() {
  for (int i = 0; i < 9; i++) {
    arduboy.drawBitmap((0 + (16 * i)) - tileoffset, 52, ground, 16, 12, WHITE);
  }
  tileoffset++;
  if (tileoffset > 16) {
    tileoffset = 0;
  }
}
//Object Launcher
void launchObstacle(byte obstacleNumber) {
  obstacles[obstacleNumber].x = 148;
  if (theGame.level >= 3)
  {
    obstacles[obstacleNumber].y = random(22, 44);
    obstacles[obstacleNumber].type = random(0, 7);
  }
  obstacles[obstacleNumber].scored = false;
  obstacles[obstacleNumber].isActive = true;
}

//Carrot Launcher
void launchCarrot() {
  carrot.isActive = true;
  carrot.x = 148;
  carrot.y = random(10, 45);
}

//Update Objects
void updateObstacles() {
  for (byte i = 0; i < NUMBER_OF_OBSTACLES; i++) {
    if (obstacles[i].isActive == true) {
      obstacles[i].x--;
      sprites.drawOverwrite(obstacles[i].x, obstacles[i].y, obst, obstacles[i].type);
      if (obstacles[i].x <= -8) {
        obstacles[i].isActive = false;
      }
      if (obstacles[i].x < thePlayer.x && !obstacles[i].scored) {
        obstacles[i].scored = true;
        if (!makeSound) {
          makeSound = true;
          scoreSound = 600;
        }
        theGame.score += 100 + (100-thePlayer.y) + chungusbonus;
      }
    }
  }
  if (carrot.isActive) {
    carrot.x--;
    sprites.drawSelfMasked(carrot.x, carrot.y, carrot.image, 0);
    if (carrot.x <= -13) {
      carrot.isActive = false;
    }
  }
}

//See if they touch a wall
bool collision() {
  if (inviTimer > 0) {
    return false;
  }
  for (byte i = 0; i < NUMBER_OF_OBSTACLES; i++) {
    if (obstacles[i].isActive == true) {
      if (collide(thePlayer.x, thePlayer.y - getImageHeight(thePlayer.image) / 2, thePlayer.image, obstacles[i].x, obstacles[i].y - getImageHeight(obst), obst)) {
        return true;
      }
    }
  }
  return false;
}

//See if they touch a carrot
bool collisionCarrot() {
  if (carrot.isActive == true) {
    if (collide(thePlayer.x, thePlayer.y - getImageHeight(thePlayer.image) / 2, thePlayer.image, carrot.x, carrot.y - getImageHeight(carrot.image), carrot.image))
    {
      return true;
    }
  }
  return false;
}

//See if the world is clear
bool allClear() {
  for (byte i = 0; i < NUMBER_OF_OBSTACLES; i++) {
    if (obstacles[i].isActive) {
      return false;
    }
    if (carrot.isActive) {
      return false;
    }
  }
  return true;
}


//See if they are heavy enough to become CHUNGUS
void chungusCheck() {
  if (thePlayer.weight >= thePlayer.targetweight && !thePlayer.chungused) {
    tunes.playScore(godzill);
    thePlayer.chungused = true;
    thePlayer.image = playerChungused;
    chungusHelp = 10;
    arduboy.clear();
    if (thePlayer.y > 64 - 12 - getImageHeight(thePlayer.image)) {
      thePlayer.y = 64 - 12 - getImageHeight(thePlayer.image);
    }
    arduboy.drawBitmap(2, 18, chungsT, 123, 31, WHITE);
    arduboy.display();
    for (int i = 200; i < 1000; i += 50)
    {
      tunes.tone(i, 30);
      flashScreen(2, 10);
    }
    arduboy.clear();
    inviTimer = 120;
  }
  if (thePlayer.weight < thePlayer.targetweight && thePlayer.chungused) {
    chungusbonus = 0;
    tunes.playScore(adj);
    thePlayer.chungused = false;
    thePlayer.image = playerSmall;
    chungusHelp = 0;
    arduboy.clear();
    thePlayer.y = 41;
    arduboy.drawBitmap(22, 28, lilchung, 83, 8, WHITE);
    arduboy.display();
    for (int i = 1000; i > 200; i -= 50)
    {
      tunes.tone(i, 10);
      flashScreen(2, 10);
    }
    arduboy.clear();
    inviTimer = 120;
  }
}

//Gameplay Loop
void gamePlay() {
  if (inviTimer > 0) {
    --inviTimer;
  }
  arduboy.setCursor(0, 0);

  unsigned long no = theGame.score;
  byte digits = 6;

  while (no != 0) {
    no = no / 10;
    digits--;
  }

  while (digits > 0)
  {
    arduboy.print("0");
    digits--;
  }

  arduboy.print(theGame.score);
  arduboy.print(" ");
  arduboy.print(thePlayer.weight);
  arduboy.print(" lb ");
 // arduboy.fillRect(0, 11, 64,1);
  //arduboy.setCursor(0, 12);
  digits = 4;
  no = theGame.feet;
   while (no != 0) {
    no = no / 10;
    digits--;
  }
  while (digits > 0)
  {
    arduboy.print("0");
    digits--;
  }
  arduboy.print(theGame.feet);
  arduboy.print("ft");
  chungusCheck();

  if (!tunes.playing() && thePlayer.chungused) {
    tunes.playScore(godzill);
  }

  else if (!tunes.playing() && !thePlayer.chungused) {
    tunes.playScore(adj);
  }

  if (thePlayer.chungused) {
    chungusbonus = thePlayer.weight;
  }

  if (arduboy.everyXFrames(3)) {
    animatePlayer();
    theGame.score = theGame.score + (1 * theGame.level) + chungusbonus;
  }

  animateGround();
  updateObstacles();

  if (collision()) {
    if (!thePlayer.chungused)
    {
      tunes.stopScore();
      for (int i = 120; i > 0; i--)
      {
        tunes.tone(random(50, 300), 4);
        flashScreen(2, 2);
      }
      for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
        obstacles[i].isActive = false;
      }
      --theGame.lives;
      obstacleLaunchCountdown = 60;
      carrotCountdown = random(60, 320);
      thePlayer.x = -8;
      theGame.gamestate = 4;
    }
    else {
      thePlayer.weight = thePlayer.targetweight - 5;
    }
  }

  if (collisionCarrot()) {
    theGame.score += 100 + chungusbonus * 5;
    carrot.isActive = false;
    thePlayer.weight++;
    makeSound = true;
    scoreSound = 200;
  }

  --obstacleLaunchCountdown;
  --carrotCountdown;

  if (obstacleLaunchCountdown <= 0 && theGame.feet > 128) {

    for (byte i = 0; i < NUMBER_OF_OBSTACLES; i++) {

      if (!obstacles[i].isActive) {
        launchObstacle(i);
        break;
      }
    }
    obstacleLaunchCountdown = random(30, 120);

  }

  if (carrotCountdown <= 0 && theGame.feet > 60) {
    if (!carrot.isActive) launchCarrot();
    carrotCountdown = random(60, 320);
  }

  if (arduboy.justPressed(A_BUTTON) && thePlayer.jumping == false && thePlayer.falling == false ) {
    thePlayer.jumping = true;
    jumpHeight = 10 - chungusHelp * 2;
  }

  if (arduboy.justPressed(B_BUTTON) && thePlayer.jumping == false && thePlayer.falling == false ) {
    thePlayer.jumping = true;
    jumpHeight = 5 - chungusHelp * 4;
  }

  if (arduboy.justPressed(DOWN_BUTTON) && thePlayer.chungused && thePlayer.weight > thePlayer.targetweight) {
    inviTimer = 80;
    thePlayer.weight--;
  }

  if (arduboy.justPressed(UP_BUTTON) && theGame.score > 1000 * theGame.level) {
    thePlayer.weight += 1;
    theGame.score -= 1000 * theGame.level;
  }

  if (arduboy.pressed(LEFT_BUTTON) && thePlayer.x > 0 && arduboy.everyXFrames(3)) {
    thePlayer.x -= (1 + (chungusHelp / 10));
  }

  if (arduboy.pressed(RIGHT_BUTTON) && thePlayer.x < 64 && arduboy.everyXFrames(3)) {
    thePlayer.x += (1 + (chungusHelp / 10));
  }

  if (thePlayer.jumping) {
    thePlayer.playerFrame = 4;
    if (thePlayer.y > jumpHeight) {
      if (thePlayer.y > 30 - chungusHelp * 2) {
        tunes.tone(500 - (chungusHelp * 20) + (-(thePlayer.y * 5)), 30);
      }
      thePlayer.y -= (1 + (chungusHelp / 10));
    } else {
      thePlayer.jumping = false;
      thePlayer.falling = true;
    }
  } else if (thePlayer.falling) {
    thePlayer.playerFrame = 4;
    if (thePlayer.y <= 64 - 12 - getImageHeight(thePlayer.image)) {
      thePlayer.y += (1 + (chungusHelp / 10));
    } else {
      thePlayer.y = 64 - 12 - getImageHeight(thePlayer.image);
      thePlayer.falling = false;
      thePlayer.playerFrame = 0;
    }
  }
  if (inviTimer > 0 != arduboy.everyXFrames(3) || !inviTimer) {
    sprites.drawSelfMasked(thePlayer.x, thePlayer.y, thePlayer.image, thePlayer.playerFrame);
  }
  --theGame.feet;
  if (theGame.feet < 0) theGame.feet = 0;
  if (theGame.feet <= 0 && allClear())
  {
    obstacleLaunchCountdown = random(30, 120);
    carrotCountdown = random(60, 320);
    for (byte i = 0; i < NUMBER_OF_OBSTACLES; i++) {
      obstacles[i].type = 0;
    }
    theGame.gamestate = 6;
    tunes.stopScore();
    for (int i = 1000; i < 2000; i += 50)
    {
      tunes.tone(random(i, 2000), 10);
      flashScreen(20, 5);
    }
  }
//Sound function for scoring.
  if (makeSound) {
    arduboy.setTextSize(1);
    if (scoreSound < 800 && arduboy.everyXFrames(1))
    {

      tunes.tone(scoreSound, 60);
      scoreSound += 50;
    }
    else if (scoreSound >= 800)
    {
      makeSound = false;
    }
  }
}
