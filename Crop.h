// This will hold the logic for crops and ground tiles

#ifndef CROP_H
#define CROP_H

enum class BGObject : uint8_t {
  ground1, ground2,
  tilled,
  water1, water2
};

const uint8_t gridMaxX = WIDTH / 8;
const uint8_t gridMaxY = HEIGHT / 8;
const uint8_t gridSize = gridMaxX * gridMaxY;
uint16_t grid[gridSize];

void drawBackground() {
  // Gonna use a 8x8 tile set for the background
  uint8_t index = 0;
  for(uint8_t backY = 0; backY <= HEIGHT; backY += tileSize) {
    for(uint8_t backX = 0; backX <= WIDTH; backX += tileSize) {
      switch(grid[index]) { 
        case static_cast<uint8_t>(BGObject::ground1):
          Sprites::drawOverwrite(backX, backY, BG, 0);
          break;
        case static_cast<uint8_t>(BGObject::ground2):
          Sprites::drawOverwrite(backX, backY, BG, 1);
          break;
      }
      index++;
      if(index > (gridSize-1)) {
        index = 0;
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