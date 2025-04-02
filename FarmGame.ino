#include <Arduboy2.h>
#include "FarmGameSprites.h"
Arduboy2 arduboy;

#define GAMEFPS 30
#define SELOFFSET 10

enum class Stance {
  Idle,
  Walk,
  Plant,
  Water
};

enum class Direction {
  South, West, North, East
};

enum WalkFrame {
  South1, South2,
  West1, West2,
  North1, North2,
  East1, East2,
  None
};

struct Farmer {
  uint16_t x;
  uint16_t y;
  Stance stance;
  Direction direction;
  uint8_t frame;
  const uint8_t *image;
  const uint8_t *mask;
};

struct Selector {
  uint16_t x;
  uint16_t y;
  const uint8_t *image;
  const uint8_t *mask;
};

const uint8_t *farmerImages[] = {FarmerIdle, FarmerWalk};
const uint8_t *farmerMasks[] = {FarmerIdleMask, FarmerWalkMask};

uint8_t getImageHeight(const uint8_t *image);
uint8_t getImageWidth(const uint8_t *image);
bool drawObject = true;

Farmer farmer = {WIDTH/2 - getImageWidth(FarmerIdle)/2, HEIGHT/2 + getImageHeight(FarmerIdle)/2, Stance::Idle, Direction::South, 0, FarmerIdle, FarmerIdleMask};
Selector selector = {farmer.x + (getImageWidth(FarmerIdle) - getImageWidth(SelectorImage))/2, farmer.y + SELOFFSET, SelectorImage, SelectorImageMask};

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(GAMEFPS);
  arduboy.initRandomSeed();
}

void loop() {
  if(!arduboy.nextFrame()) return; // Prevents game from running fast
  arduboy.clear();
  arduboy.pollButtons();
  
  controlFarmer();
  updateFarmer();

  drawBackground();
  drawFarmer();
  drawSelector();

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

void controlFarmer() {
  // This will be where all the controls will be set
  if(arduboy.pressed(UP_BUTTON)) {
    farmer.y -= 1;
    farmer.stance = Stance::Walk;
    if(farmer.frame != WalkFrame::North1 && farmer.frame != WalkFrame::North2) {
      farmer.frame = WalkFrame::North1;
    }
    
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    farmer.y += 1;
    farmer.stance = Stance::Walk;
    if(farmer.frame != WalkFrame::South1 && farmer.frame != WalkFrame::South2) {
      farmer.frame = WalkFrame::South1;
    }
    
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    farmer.x -= 1;
    farmer.stance = Stance::Walk;
    if(farmer.frame != WalkFrame::West1 && farmer.frame != WalkFrame::West2) {
      farmer.frame = WalkFrame::West1;
    }
    
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    farmer.x += 1;
    farmer.stance = Stance::Walk;
    if(farmer.frame != WalkFrame::East1 && farmer.frame != WalkFrame::East2) {
      farmer.frame = WalkFrame::East1;
    }
  }
  if(arduboy.notPressed(UP_BUTTON | DOWN_BUTTON | LEFT_BUTTON | RIGHT_BUTTON)) {
    farmer.stance = Stance::Idle;
  }
}

void updateFarmer() {
  // This will be the animation changes and the like
  switch(farmer.stance) {
    case Stance::Idle:
      break;

    case Stance::Walk:
      if(arduboy.everyXFrames(3)) {
        switch(farmer.frame) {
          case WalkFrame::South1:
            farmer.frame = WalkFrame::South2;
            break;
          case WalkFrame::South2:
            farmer.frame = WalkFrame::South1;
            break;

          case WalkFrame::West1:
            farmer.frame = WalkFrame::West2;
            break;
          case WalkFrame::West2:
            farmer.frame = WalkFrame::West1;
            break;

          case WalkFrame::North1:
            farmer.frame = WalkFrame::North2;
            break;
          case WalkFrame::North2:
            farmer.frame = WalkFrame::North1;
            break;

          case WalkFrame::East1:
            farmer.frame = WalkFrame::East2;
            break;
          case WalkFrame::East2:
            farmer.frame = WalkFrame::East1;
            break;

          default:
            break;
        }
      }
  }
}

void updateSelector() {
  // We need to bound the selector to an 8x8 grid
  uint8_t gridX = WIDTH / 8;
  uint8_t gridY = HEIGHT / 8;
}

void drawFarmer() {
  uint8_t imageIndex = static_cast<uint8_t>(farmer.stance);
  uint8_t maskFrame = 0;
  if(farmer.stance == Stance::Idle) farmer.frame = 0;
  if(farmer.stance == Stance::Walk) maskFrame = farmer.frame;

  farmer.image = farmerImages[imageIndex];
  farmer.mask = farmerMasks[imageIndex];
  Sprites::drawExternalMask(farmer.x, farmer.y - getImageHeight(farmer.image), farmer.image, farmer.mask, farmer.frame, maskFrame);
}

void drawSelector() {
  uint8_t flashDelay = 15;
  if(arduboy.everyXFrames(flashDelay)){
    drawObject = !drawObject;
  }
  if(drawObject) {
    Sprites::drawExternalMask(selector.x, selector.y - getImageHeight(selector.image), selector.image, selector.mask, 0, 0);
  }
}

uint8_t getImageHeight(const uint8_t *image) {
  return pgm_read_byte_near(image + 1);
}

uint8_t getImageWidth(const uint8_t *image) {
  return pgm_read_byte_near(image);
}