//Jonathan Holmes (crait)
//October 24th, 2016
//Number Guessing Game

#include <Arduboy2.h>
#include "FarmGameSprites.h"
Arduboy2 arduboy;

#define DISPLAYX 128
#define DISPLAYY 64

int playerX;
int playerY;
enum Direction {south, west, north, east};

constexpr uint8_t farmDudeWidth = 16;
constexpr uint8_t farmDudeHeight = 16;

constexpr uint8_t farmDude[] PROGMEM
{
  farmDudeWidth, farmDudeHeight,

  //Frame 0
  0x00, 0x00, 0x00, 0x00, 0x9C, 0xBE, 0x73, 0xDF, 0xDF, 0x73, 0xBE, 0x9C, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x07, 0xF9, 0xF0, 0x11, 0x11, 0xF0, 0xF9, 0x07, 0x08, 0x00, 0x00, 0x00
};

constexpr uint8_t farmDudeMaskWidth = 16;
constexpr uint8_t farmDudeMaskHeight = 16;

constexpr uint8_t farmDudeMask[] PROGMEM
{
  farmDudeMaskWidth, farmDudeMaskHeight,

  //Frame 0
  0x00, 0x00, 0x00, 0x00, 0x9C, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0x9C, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x07, 0xFF, 0xFF, 0x1F, 0x1F, 0xFF, 0xFF, 0x07, 0x08, 0x00, 0x00, 0x00
};




void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(30);
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
  for(uint8_t backY = 0; backY <= DISPLAYY; backY += tileSize) {
    for(uint8_t backX = 0; backX <= DISPLAYX; backX += tileSize) {
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
    animationPlayer(250); // FORCES Default CASE
  } else {
    if(arduboy.pressed(UP_BUTTON)) {
      playerY -= 1;
      animationPlayer(Direction::north);
    }
    if(arduboy.pressed(DOWN_BUTTON)) {
      playerY += 1;
      animationPlayer(Direction::south);
    }
    if(arduboy.pressed(LEFT_BUTTON)) {
      playerX -= 1;
      animationPlayer(Direction::west);
    }
    if(arduboy.pressed(RIGHT_BUTTON)) {
      playerX += 1;
      animationPlayer(Direction::east);
    }
  }
}

void animationPlayer(uint8_t state) {
  switch(state) {
    case 0:
      Sprites::drawExternalMask(playerX, playerY, FarmerWalk, FarmerWalkMask, 0, 0);
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