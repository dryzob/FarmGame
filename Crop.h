// This will hold the logic for crops and ground tiles

#ifndef CROP_H
#define CROP_H

enum class BGObject : uint8_t {
  ground1, ground2,
  tilled,
  water1, water2,
  count
};

enum class Carrots : uint8_t {
  baby1, baby2, teen1, teen2, adult
};

const uint8_t gridMaxX = WIDTH / 8;
const uint8_t gridMaxY = HEIGHT / 8;
const uint8_t gridSize = gridMaxX * gridMaxY;
uint16_t grid[gridSize];
const uint8_t BGOffset = 6;

void drawBackground() {
  // Gonna use a 8x8 tile set for the background
  uint8_t index = 0;
  for(uint8_t backY = 0; backY <= HEIGHT; backY += tileSize) {
    for(uint8_t backX = 0; backX <= WIDTH; backX += tileSize) {
      switch(grid[index]) {
        // Ground types
        case static_cast<uint8_t>(BGObject::ground1):
          Sprites::drawOverwrite(backX, backY, BG, 0);
          break;
        case static_cast<uint8_t>(BGObject::ground2):
          Sprites::drawOverwrite(backX, backY, BG, 1);
          break;
        case static_cast<uint8_t>(BGObject::tilled):
          Sprites::drawOverwrite(backX, backY, BG, 2);
          break;
        case static_cast<uint8_t>(BGObject::water1):
          Sprites::drawOverwrite(backX, backY, BG, 3);
          break;
        case static_cast<uint8_t>(BGObject::water2):
          Sprites::drawOverwrite(backX, backY, BG, 4);
          break;
        // Carrots
        case static_cast<uint8_t>(Carrots::baby1) + BGOffset:
          Sprites::drawOverwrite(backX, backY, Carrots, 0);
          break;
        case static_cast<uint8_t>(Carrots::baby2) + BGOffset:
          Sprites::drawOverwrite(backX, backY, Carrots, 1);
          break;
        case static_cast<uint8_t>(Carrots::teen1) + BGOffset:
          Sprites::drawOverwrite(backX, backY, Carrots, 2);
          break;
        case static_cast<uint8_t>(Carrots::teen2) + BGOffset:
          Sprites::drawOverwrite(backX, backY, Carrots, 3);
          break;
        case static_cast<uint8_t>(Carrots::adult) + BGOffset:
          Sprites::drawOverwrite(backX, backY, Carrots, 4);
          break;
      }
      index++;
      if(index > (gridSize-1)) {
        index = 0;
      }
    }
  }
}

/****************************************/
/*Name: updateCrop                      */
/*This will update the sprites of crops */
/****************************************/
void updateCrop() {
  for(uint8_t index = 0; index < gridSize; index++) {
    if(arduboy.everyXFrames(3)){
      switch(grid[index]) {
        // Water Animation
        case static_cast<uint8_t>(BGObject::water1):
          grid[index] = static_cast<uint8_t>(BGObject::water2);
          break;
        case static_cast<uint8_t>(BGObject::water2):
          grid[index] = static_cast<uint8_t>(BGObject::water1);
          break;
        // Carrot animations
        case static_cast<uint8_t>(Carrots::baby1) + BGOffset:
          grid[index] = static_cast<uint8_t>(Carrots::baby2);
          break;
        case static_cast<uint8_t>(Carrots::baby2) + BGOffset:
          grid[index] = static_cast<uint8_t>(Carrots::baby1);
          break;
        case static_cast<uint8_t>(Carrots::teen1) + BGOffset:
          grid[index] = static_cast<uint8_t>(Carrots::teen2);
          break;
        case static_cast<uint8_t>(Carrots::teen2) + BGOffset:
          grid[index] = static_cast<uint8_t>(Carrots::teen1);
          break;
      }
    }
  }
}

void buildInitialGrid() {
  for(uint8_t i = 0; i < (gridSize); i++) {
    if(i%2 == 0) {
      grid[i] = static_cast<uint8_t>(BGObject::ground1);
    } else {
      grid[i] = static_cast<uint8_t>(BGObject::ground2);
    }
  }
}



#endif