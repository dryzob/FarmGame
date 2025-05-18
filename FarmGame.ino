// Farm Game
// Created by dryzob
// For Arduboy FX mini console

#include <Arduboy2.h>
Arduboy2 arduboy; // This object needed for most func

#include "FarmGameSprites.h"
#include "Farmer.h"
#include "Crop.h"
#include "Menu.h"

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(gameFPS);
  // Serial.begin(9600);
  arduboy.initRandomSeed();
  buildInitialGrid();
}

void loop() {
  if(!arduboy.nextFrame()) return; // Prevents game from running fast
  arduboy.clear();
  arduboy.pollButtons();
  

  // TODO: Move these function calls to own function
  

  controlFarmer(farmer);
  controlMenu();
  updateFarmer(farmer);
  updateSelector(farmer, selector);

  drawBackground();
  drawFarmer(farmer);
  drawSelector(selector);
  drawMenu();

  // arduboy.fillRect(farmer.x-1, farmer.y, 3, 3); // Debug hitbox type thing
  // arduboy.print(toolNames[0]);

  arduboy.display();
}
