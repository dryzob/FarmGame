// This will house all the logic for the farmer
// including controlling, updating, and drawing

#ifndef FARMER_H
#define FARMER_H

#include "Utility.h"

#define SELOFFSET 8

enum class Stance : uint8_t {
  Idle,
  Walk,
  Plant,
  Water,
  Hoe
};

enum class Direction : uint8_t {
  South, West, North, East
};

enum WalkFrame : uint8_t {
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
  bool canMove;
  uint8_t frame;
  const uint8_t *image;
  const uint8_t *mask;
  Farmer(uint16_t initX, uint16_t initY) {
    x = initX;
    y = initY;
    stance = Stance::Idle;
    direction = Direction::South;
    canMove = true;
    frame = 0;
    image = FarmerIdle;
    mask = FarmerIdleMask;
  }
};

struct Selector {
  uint16_t trueX;
  uint16_t trueY;
  uint16_t roundX;
  uint16_t roundY;
  const uint8_t *image;
  const uint8_t *mask;
  bool visable;
  Selector(uint16_t initX, uint16_t initY) {
    trueX = initX;
    trueY = initY;
    roundX = 0;
    roundY = 0;
    image = SelectorImage;
    mask = SelectorImageMask;
    visable = true;
  }
};

const uint8_t *farmerImages[] = {FarmerIdle, FarmerWalk};
const uint8_t *farmerMasks[] = {FarmerIdleMask, FarmerWalkMask};

Farmer farmer(WIDTH/2, HEIGHT/2);
Selector selector(farmer.x + (getImageWidth(FarmerIdle) - getImageWidth(SelectorImage))/2, farmer.y + SELOFFSET);

// FUNCTIONS
void controlFarmer(Farmer &farmer) {
  // This will be where all the controls will be set
  if(farmer.canMove) {
    if(arduboy.pressed(UP_BUTTON)) {
      farmer.y -= 1;
      farmer.stance = Stance::Walk;
      farmer.direction = Direction::North;
      if(farmer.frame != WalkFrame::North1 && farmer.frame != WalkFrame::North2) {
        farmer.frame = WalkFrame::North1;
      }
      
    }
    if(arduboy.pressed(DOWN_BUTTON)) {
      farmer.y += 1;
      farmer.stance = Stance::Walk;
      farmer.direction = Direction::South;
      if(farmer.frame != WalkFrame::South1 && farmer.frame != WalkFrame::South2) {
        farmer.frame = WalkFrame::South1;
      }
      
    }
    if(arduboy.pressed(LEFT_BUTTON)) {
      farmer.x -= 1;
      farmer.stance = Stance::Walk;
      farmer.direction = Direction::West;
      if(farmer.frame != WalkFrame::West1 && farmer.frame != WalkFrame::West2) {
        farmer.frame = WalkFrame::West1;
      }
      
    }
    if(arduboy.pressed(RIGHT_BUTTON)) {
      farmer.x += 1;
      farmer.stance = Stance::Walk;
      farmer.direction = Direction::East;
      if(farmer.frame != WalkFrame::East1 && farmer.frame != WalkFrame::East2) {
        farmer.frame = WalkFrame::East1;
      }
    }
    if(arduboy.notPressed(UP_BUTTON | DOWN_BUTTON | LEFT_BUTTON | RIGHT_BUTTON)) {
      farmer.stance = Stance::Idle;
    }
  }
  if(farmer.x > WIDTH) farmer.x = WIDTH;
  if(farmer.x < 1) farmer.x = 1;
  if(farmer.y > HEIGHT) farmer.y = HEIGHT;
  if(farmer.y < 1) farmer.y = 1;
}

void updateFarmer(Farmer &farmer) {
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

void updateSelector(Farmer &farmer, Selector &selector) {
  if(farmer.canMove) {
    switch(farmer.direction) {
      case Direction::South:
        selector.trueX = farmer.x;
        selector.trueY = farmer.y + SELOFFSET;
        break;
      case Direction::West:
        selector.trueX = farmer.x - (SELOFFSET*2);
        selector.trueY = farmer.y;
        break;
      case Direction::North:
        selector.trueX = farmer.x;
        selector.trueY = farmer.y - SELOFFSET;
        break;
      case Direction::East:
        selector.trueX = farmer.x + SELOFFSET;
        selector.trueY = farmer.y;
        break;
      default:
        break;
    }
    // [[BUG]] Will still cause a wrap due to SELOFFSET
    if(selector.trueX > WIDTH) selector.trueX = WIDTH;
    if(selector.trueX < 1) selector.trueX = 1;
    if(selector.trueY > HEIGHT) selector.trueY = HEIGHT;
    if(selector.trueX < 1) selector.trueY = 1; 
    // Now to round these true values to the grid
    selector.roundX = ((selector.trueX + tileSize/2) / tileSize) * tileSize;
    selector.roundY = ((selector.trueY + tileSize/2) / tileSize) * tileSize;
  }
}

void drawFarmer(Farmer &farmer) {
  uint8_t imageIndex = static_cast<uint8_t>(farmer.stance);
  uint8_t maskFrame = 0;
  if(farmer.stance == Stance::Idle) farmer.frame = 0;
  if(farmer.stance == Stance::Walk) maskFrame = farmer.frame;

  farmer.image = farmerImages[imageIndex];
  farmer.mask = farmerMasks[imageIndex];
  Sprites::drawExternalMask(farmer.x - getImageWidth(farmer.image)/2, farmer.y - getImageHeight(farmer.image),
                            farmer.image, farmer.mask, farmer.frame, maskFrame);
}

void drawSelector(Selector &selector) {
  uint8_t flashDelay = 10;
  if(arduboy.everyXFrames(flashDelay)){
    selector.visable = !selector.visable;
  }
  if(selector.visable) {
    Sprites::drawExternalMask(selector.roundX, selector.roundY - getImageHeight(selector.image),
                              selector.image, selector.mask, 0, 0);
  }
}

#endif