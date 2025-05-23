// This will house all the logic for the farmer
// including controlling, updating, and drawing

#ifndef FARMER_H
#define FARMER_H

#include "Utility.h"

#define SELOFFSET 8

enum class Stance : uint8_t {
  Idle,
  Walk,
  Water,
  Hoe,
  Harvest,
  // Plant /* This isn't in yet */
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

enum class TillFrame : uint8_t {
  Frame1 = 20, Frame2 = 21, end = 22
};
enum class WaterFrame : uint8_t {
  Frame1 = 30, Frame2 = 31, end = 32
};
enum class HarvestFrame : uint8_t {
  Frame1 = 40, Frame2 = 41, end = 42
};

struct Farmer {
  uint16_t x;
  uint16_t y;
  Stance stance;
  Direction direction;
  bool canMove;
  bool inAction;
  uint8_t frame;
  const uint8_t *image;
  const uint8_t *mask;
  Farmer(uint16_t initX, uint16_t initY) {
    x = initX;
    y = initY;
    stance = Stance::Idle;
    direction = Direction::South;
    canMove = true;
    inAction = false;
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

const uint8_t *farmerImages[] = {FarmerIdle, FarmerWalk, WaterGround, TillGround, HarvestGround};
const uint8_t *farmerMasks[] = {FarmerIdleMask, FarmerWalkMask, WaterGroundMask, TillGroundMask, HarvestGroundMask};

Farmer farmer(WIDTH/2, HEIGHT/2);
Selector selector(farmer.x + (getImageWidth(FarmerIdle) - getImageWidth(SelectorImage))/2, farmer.y + SELOFFSET);

// FUNCTIONS
void controlFarmer(Farmer &farmer) {
  arduboy.print("control");
  // This will be where all the controls will be set
  if(farmer.canMove && !farmer.inAction) {
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
      farmer.frame = 0;
    }
    if(arduboy.justPressed(B_BUTTON)) {
      farmer.inAction = true;
    }
  } 
  if(farmer.inAction) {
    switch(currSelection[0]) {
      case 0:
        farmer.stance = Stance::Hoe;
        if(farmer.frame != static_cast<uint8_t>(TillFrame::Frame1) && farmer.frame != static_cast<uint8_t>(TillFrame::Frame2) && farmer.frame != static_cast<uint8_t>(TillFrame::end)) {
          farmer.frame = static_cast<uint8_t>(TillFrame::Frame1);
        }
        break;
      case 1:
        farmer.stance = Stance::Water;
        if(farmer.frame != static_cast<uint8_t>(WaterFrame::Frame1) && farmer.frame != static_cast<uint8_t>(WaterFrame::Frame2) && farmer.frame != static_cast<uint8_t>(WaterFrame::end)) {
          farmer.frame = static_cast<uint8_t>(WaterFrame::Frame1);
        }
        break;
      case 2:
        farmer.stance = Stance::Harvest;
        if(farmer.frame != static_cast<uint8_t>(HarvestFrame::Frame1) && farmer.frame != static_cast<uint8_t>(HarvestFrame::Frame2) && farmer.frame != static_cast<uint8_t>(HarvestFrame::end)) {
          farmer.frame = static_cast<uint8_t>(HarvestFrame::Frame1);
        }
        break;
    }
  }
  if(farmer.x > WIDTH) farmer.x = WIDTH;
  if(farmer.x < 1) farmer.x = 1;
  if(farmer.y > HEIGHT) farmer.y = HEIGHT;
  if(farmer.y < 1) farmer.y = 1;
}

void updateFarmer(Farmer &farmer) {
  arduboy.print("update");
  uint8_t animationFrames = 10;
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
    case Stance::Water:
      if(waitXFrames(animationFrames)) {
        switch(farmer.frame) {
          case static_cast<uint8_t>(WaterFrame::Frame1):
            farmer.frame = static_cast<uint8_t>(WaterFrame::Frame2);
            break;
          case static_cast<uint8_t>(WaterFrame::Frame2):
            farmer.frame = static_cast<uint8_t>(WaterFrame::end);
            break;
          case static_cast<uint8_t>(WaterFrame::end):
            farmer.canMove = true;
            farmer.inAction = false;
            break;
          default:
            break;
        }
      }
    case Stance::Hoe:
      if(waitXFrames(animationFrames)) {
        switch(farmer.frame) {
          case static_cast<uint8_t>(TillFrame::Frame1):
            farmer.frame = static_cast<uint8_t>(TillFrame::Frame2);
            break;
          case static_cast<uint8_t>(TillFrame::Frame2):
            farmer.frame = static_cast<uint8_t>(TillFrame::end);
            break;
          case static_cast<uint8_t>(TillFrame::end):
            farmer.canMove = true;
            farmer.inAction = false;
            break;
          default:
            break;
        }
      }
    case Stance::Harvest:
      if(waitXFrames(animationFrames)) {
        switch(farmer.frame) {
          case static_cast<uint8_t>(HarvestFrame::Frame1):
            farmer.frame = static_cast<uint8_t>(HarvestFrame::Frame2);
            break;
          case static_cast<uint8_t>(HarvestFrame::Frame2):
            farmer.frame = static_cast<uint8_t>(HarvestFrame::end);
            break;
          case static_cast<uint8_t>(HarvestFrame::end):
            farmer.canMove = true;
            farmer.inAction = false;
            break;
          default:
            break;
        }
      }
    default:
      // do nothing
      break;
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
  uint8_t imageFrame = farmer.frame;
  uint8_t maskFrame = 0;
  // if(farmer.stance == Stance::Idle) {
  //    farmer.frame = 0;
  // } else {
  //   maskFrame = farmer.frame;
  // }
  switch(farmer.stance) {
    case Stance::Idle:
      imageFrame = 0;
      break;
    case Stance::Walk:
      maskFrame = imageFrame;
      break;
    case Stance::Harvest:
      imageFrame -= 40;
      maskFrame = imageFrame;
      break;
    case Stance::Water:
      imageFrame -= 30;
      maskFrame = imageFrame;
      break;
    case Stance::Hoe:
      imageFrame -= 20;
      maskFrame = imageFrame;
      break;
  }
  farmer.image = farmerImages[imageIndex];
  farmer.mask = farmerMasks[imageIndex];
  Sprites::drawExternalMask(farmer.x - getImageWidth(farmer.image)/2, farmer.y - getImageHeight(farmer.image),
                            farmer.image, farmer.mask, imageFrame, maskFrame);
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