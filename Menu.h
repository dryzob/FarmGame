// This will house all the menu functions

#ifndef MENU_H
#define MENU_H

#include "Utility.h"

enum class Menus : uint8_t {
  Tools,
  Seeds,
  Menu
};

String toolNames[] = {String("Hoe"), String("W. Can"), String("Scythe")};
Menus currMenu = Menus::Tools;
bool drawHighlighter = true;
bool menuOpen = false;

// This is probably not smart to do but it works
Menus& operator++(Menus &m) {
  m = static_cast<Menus>(static_cast<uint8_t>(m) + 1);
  return m;
}
Menus& operator--(Menus &m) {
  m = static_cast<Menus>(static_cast<uint8_t>(m) - 1);
  return m;
}

void controlMenu() {
  if(arduboy.pressed(A_BUTTON)) {
    menuOpen = true;
    farmer.canMove = false;
  } else {
    menuOpen = false;
    farmer.canMove = true;
  }

  if(menuOpen) {
    // player inputs
    if(arduboy.justPressed(UP_BUTTON)) currSelection[static_cast<uint8_t>(currMenu)]--;
    if(arduboy.justPressed(DOWN_BUTTON)) currSelection[static_cast<uint8_t>(currMenu)]++;
    if(arduboy.justPressed(LEFT_BUTTON) && currMenu > Menus::Tools) currMenu--;
    if(arduboy.justPressed(RIGHT_BUTTON) && currMenu < Menus::Menu) currMenu++;

    // boundary guarding
    if(currSelection[static_cast<uint8_t>(currMenu)] < 0 || currSelection[static_cast<uint8_t>(currMenu)] > 200) {
      currSelection[static_cast<uint8_t>(currMenu)] = 0;
    }
    switch(currMenu) {
      case Menus::Tools:
        if(currSelection[static_cast<uint8_t>(currMenu)] > 2) {
          currSelection[static_cast<uint8_t>(currMenu)] = 2;
        }
        break;
      case Menus::Seeds:
        if(currSelection[static_cast<uint8_t>(currMenu)] > 3) {
          currSelection[static_cast<uint8_t>(currMenu)] = 3;
        }
        break;
      case Menus::Menu:
        // TODO add actual menu here
        break;
    }
  }
}

void drawMenu() {
  if(!menuOpen) return; // menu is not open therefor no draw
  uint8_t menuBottom = HEIGHT - 4;
  uint8_t menuLeft = WIDTH/2;
  uint8_t lineWidth = 52;
  uint8_t delay = 15;
  uint8_t height = getImageHeight(Menu) + 12;

  // Highlight toggle
  if(arduboy.everyXFrames(delay)) drawHighlighter = !drawHighlighter;

  // Box
  arduboy.fillRect(menuLeft, 0, menuLeft, HEIGHT, BLACK);
  arduboy.drawRect((menuLeft), 0, (menuLeft), HEIGHT);
  arduboy.drawRect((menuLeft)+2, 2, (menuLeft)-4, HEIGHT-4);

  // swtich statement for type of menu: tools/seeds/menu
  switch(currMenu) {
    case Menus::Tools:
      // want 3 spaces for this section: water can, hoe, scythe 
      // for(uint8_t menuHeight = getImageHeight(Menu) + 15; menuHeight < menuBottom; menuHeight += 15) {
      //   arduboy.setCursor(menuLeft + 5, menuHeight - 3);
      //   arduboy.print(itemNum + 1);
      //   arduboy.print(". ");
      //   arduboy.print(toolNames[itemNum]);

      //   itemNum++;
      // }
      for(uint8_t index = 0; index < 3; index++) {
        arduboy.setCursor(menuLeft + 5, height);
        arduboy.print(index + 1);
        arduboy.print(". ");
        arduboy.print(toolNames[index]);

        height += 15;
      }
      // tools title
      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 0, 0);
      // selection highlighter logic
      if(drawHighlighter) {
        switch(currSelection[static_cast<uint8_t>(currMenu)]) {
          case 0:
            arduboy.drawFastHLine(WIDTH/2 + 5, 28, 54);
            // setRGB('g');
            break;
          case 1:
            arduboy.drawFastHLine(WIDTH/2 + 5, 43, 54);
            // setRGB('b');
            break;
          case 2:
            arduboy.drawFastHLine(WIDTH/2 + 5, 58, 54);
            // setRGB('r');
            break;
        }
      }
      break;
    case Menus::Seeds:
      // Currently thinkin 4 seeds for this one
      // for(uint8_t menuHeight = getImageHeight(Menu) + 15; menuHeight < menuBottom; menuHeight += 10) {
      //   arduboy.setCursor(menuLeft + 5, menuHeight - 3);
      //   arduboy.print(itemNum);
      //   arduboy.print(".");


      //   itemNum++;
      // }
      for(uint8_t index = 0; index < 4; index++) {
        arduboy.setCursor(menuLeft + 5, height);
        arduboy.print(index + 1);
        arduboy.print(". ");
        // TODO: Will display seed names here

        height += 10;
      }
      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 1, 1);
      // selection highlighter logic
      if(drawHighlighter) {
        switch(currSelection[static_cast<uint8_t>(currMenu)]) {
          case 0:
            arduboy.drawFastHLine(WIDTH/2 + 5, 28, 54);
            break;
          case 1:
            arduboy.drawFastHLine(WIDTH/2 + 5, 38, 54);
            break;
          case 2:
            arduboy.drawFastHLine(WIDTH/2 + 5, 48, 54);
            break;
          case 3:
            arduboy.drawFastHLine(WIDTH/2 + 5, 58, 54);
            break;
        }
      }
      break;
    case Menus::Menu:
      // General menu stuff, this will be fairly unique compared to the other menus

      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 2, 2);
      break;
  } 
}

#endif