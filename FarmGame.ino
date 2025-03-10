#include <Arduboy2.h>
#include "FarmGameSprites.h"
Arduboy2 arduboy;

#define GAMEFPS 30
#define buffer_size 10

int playerX;
int playerY;
enum Direction {south, west, north, east};

struct Animations {
  Animations(); // Empty contructor for global creation

  bool addQueue(uint8_t* animation, uint8_t* mask, uint8_t start, uint16_t end, uint8_t FPS, bool loop) {

  }
  
  uint8_t qTracker = 0;

  uint8_t* animation[buffer_size];
  uint8_t* mask[buffer_size];
  uint8_t start[buffer_size];
  uint16_t end[buffer_size];
  uint8_t FPS[buffer_size];
  bool loop[buffer_size];
}

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(GAMEFPS);
  playerX = 10;
  playerY = 25;
}

void loop() {
  if(!arduboy.nextFrame()) return; // Prevents game from running fast
  arduboy.clear();
  arduboy.pollButtons();
  drawBackground();

  controlPlayer();
  arduboy.display();
}

void drawBackground() {
  // Gonna use a 8x8 tile set for the background
  uint8_t tileSize = 8;
  uint8_t currFrame = 0;
  for(uint8_t backY = 0; backY <= HEIGHT; backY += tileSize) {
    for(uint8_t backX = 0; backX <= WIDTH; backX += tileSize) {
      Sprites::drawOverwrite(backX, backY, BG, currFrame);
      if(currFrame == 0) {
        currFrame = 1;
      } else {
        currFrame = 0;
      }
    }
  }
}

void controlPlayer() {
  if(arduboy.notPressed(UP_BUTTON | DOWN_BUTTON | LEFT_BUTTON | RIGHT_BUTTON)) {
    animationSelector(250); // FORCES Default CASE
  } else {
    if(arduboy.pressed(UP_BUTTON)) {
      playerY -= 1;
      animationSelector(Direction::north);
    }
    if(arduboy.pressed(DOWN_BUTTON)) {
      playerY += 1;
      animationSelector(Direction::south);
    }
    if(arduboy.pressed(LEFT_BUTTON)) {
      playerX -= 1;
      animationSelector(Direction::west);
    }
    if(arduboy.pressed(RIGHT_BUTTON)) {
      playerX += 1;
      animationSelector(Direction::east);
    }
  }
}

void animationSelector(uint8_t state) {
  switch(state) {
    case 0:
      // animationPlayer(FarmerWalk, FarmerWalkMask, 0, 1, 15, false);
      break;
    case 1:
      Sprites::drawExternalMask(playerX, playerY, FarmerWalk, FarmerWalkMask, 2, 0);
      break;
    case 2:
      Sprites::drawExternalMask(playerX, playerY, FarmerWalk, FarmerWalkMask, 4, 0);
      break;
    case 3:
      Sprites::drawExternalMask(playerX, playerY, FarmerWalk, FarmerWalkMask, 6, 0);
      break;
    default:
      Sprites::drawExternalMask(playerX, playerY, Farmer, FarmerMask, 0, 0);
  }
}

/* animationPlayer
  This function will house the logic needed to play through an animation either on loop or once.
  */
void animationPlayerCall(uint8_t* animation, uint8_t* mask, uint8_t start, uint16_t end, uint8_t FPS, bool loop) {
  

}

void animationPlayer() {

}