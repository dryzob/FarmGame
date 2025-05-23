// General functions/variables used by all files

#ifndef UTILITY_H
#define UTILITY_H

// VARIABLES
const uint8_t tileSize = 8;
const uint8_t gameFPS = 30;
uint8_t currSelection[] = {0, 0, 0};
uint8_t waitCounter = 0;

// FUNCTIONS
uint8_t getImageHeight(const uint8_t *image) {
  return pgm_read_byte_near(image + 1);
}

uint8_t getImageWidth(const uint8_t *image) {
  return pgm_read_byte_near(image);
}

bool waitXFrames(uint8_t frames) {
  if(waitCounter >= frames) {
    waitCounter = 0;
    return true;
  } else {
    waitCounter += 1;
    return false;
  }
}

void setRGB(char color) {
  uint8_t brightness = 15;
  switch(color) {
    case 'r':
      // set red light
      arduboy.setRGBled(brightness, 0, 0);
      break;
    case 'b':
      // set blue light
      arduboy.setRGBled(0, 0, brightness);
      break;
    case 'g':
      // set green light
      arduboy.setRGBled(0, brightness, 0);
      break;
    default:
      // turn off lights
      arduboy.setRGBled(0, 0, 0);
  }
}

#endif