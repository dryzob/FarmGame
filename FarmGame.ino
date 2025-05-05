#include <Arduboy2.h>
#include "FarmGameSprites.h"
Arduboy2 arduboy;

#define GAMEFPS 30
#define SELOFFSET 8
#define TILESIZE 8

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

enum class Menus : uint8_t {
  Tools,
  Seeds,
  Menu
};
// This is probably not smart to do but it works
Menus& operator++(Menus &m) {
  m = static_cast<Menus>(static_cast<uint8_t>(m) + 1);
  return m;
}
Menus& operator--(Menus &m) {
  m = static_cast<Menus>(static_cast<uint8_t>(m) - 1);
  return m;
}

enum class BGObject : uint8_t {
  ground1,
  ground2,
  carrot
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
  Selector(uint16_t initX, uint16_t initY) {
    trueX = initX;
    trueY = initY;
    roundX = 0;
    roundY = 0;
    image = SelectorImage;
    mask = SelectorImageMask;
  }
};

const uint8_t *farmerImages[] = {FarmerIdle, FarmerWalk};
const uint8_t *farmerMasks[] = {FarmerIdleMask, FarmerWalkMask};

// Function names
uint8_t getImageHeight(const uint8_t *image);
uint8_t getImageWidth(const uint8_t *image);

// Globals variables
bool drawObject = true;
bool menuOpen = false;
Menus currMenu = Menus::Tools;

Farmer farmer(WIDTH/2, HEIGHT/2);

Selector selector(farmer.x + (getImageWidth(FarmerIdle) - getImageWidth(SelectorImage))/2, farmer.y + SELOFFSET);

const uint8_t gridMaxX = WIDTH / 8;
const uint8_t gridMaxY = HEIGHT / 8;
const uint8_t gridSize = gridMaxX * gridMaxY;
uint16_t grid[gridSize];


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(GAMEFPS);
  // Serial.begin(9600);
  arduboy.initRandomSeed();
  buildInitialGrid();
}

void loop() {
  if(!arduboy.nextFrame()) return; // Prevents game from running fast
  arduboy.clear();
  arduboy.pollButtons();
  
  if(arduboy.pressed(A_BUTTON)) {
    menuOpen = true;
    farmer.canMove = false;
  } else {
    menuOpen = false;
    farmer.canMove = true;
  }

  controlFarmer();
  controlMenu();
  updateFarmer();
  updateSelector();

  drawBackground();
  drawFarmer();
  drawSelector();
  drawMenu();

  // arduboy.fillRect(farmer.x-1, farmer.y, 3, 3); // Debug hitbox type thing

  arduboy.display();
}

void drawBackground() {
  // Gonna use a 8x8 tile set for the background
  uint8_t tileSize = TILESIZE;
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

void controlMenu() {
  if(menuOpen) {
    // This will set up much the cursor jumps
    switch(currMenu) {
      case Menus::Tools:
        break;
      case Menus::Seeds:
        break;
      case Menus::Menu:
        break;
    }

    // Actual inputs
    if(arduboy.justPressed(LEFT_BUTTON) && currMenu > Menus::Tools) currMenu--;
    if(arduboy.justPressed(RIGHT_BUTTON) && currMenu < Menus::Menu) currMenu++;
  }
}

void controlFarmer() {
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
  // Possibly round to the nearest block?
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
  selector.roundX = ((selector.trueX + TILESIZE/2) / TILESIZE) * TILESIZE;
  selector.roundY = ((selector.trueY + TILESIZE/2) / TILESIZE) * TILESIZE;
}

void drawFarmer() {
  uint8_t imageIndex = static_cast<uint8_t>(farmer.stance);
  uint8_t maskFrame = 0;
  if(farmer.stance == Stance::Idle) farmer.frame = 0;
  if(farmer.stance == Stance::Walk) maskFrame = farmer.frame;

  farmer.image = farmerImages[imageIndex];
  farmer.mask = farmerMasks[imageIndex];
  Sprites::drawExternalMask(farmer.x - getImageWidth(farmer.image)/2, farmer.y - getImageHeight(farmer.image),
                            farmer.image, farmer.mask, farmer.frame, maskFrame);
}

void drawSelector() {
  uint8_t flashDelay = 10;
  if(arduboy.everyXFrames(flashDelay)){
    drawObject = !drawObject;
  }
  if(drawObject) {
    Sprites::drawExternalMask(selector.roundX, selector.roundY - getImageHeight(selector.image),
                              selector.image, selector.mask, 0, 0);
  }
}

void drawMenu() {
  if(!menuOpen) return; // menu is not open therefor, no draw
  uint8_t menuBottom = HEIGHT - 4;
  uint8_t menuLeft = WIDTH/2;
  uint8_t lineWidth = 52;
  uint8_t itemNum = 1;

  // Box
  arduboy.fillRect(menuLeft, 0, menuLeft, HEIGHT, BLACK);
  arduboy.drawRect((menuLeft), 0, (menuLeft), HEIGHT);
  arduboy.drawRect((menuLeft)+2, 2, (menuLeft)-4, HEIGHT-4);

  // swtich statement for type of menu: tools/seeds/menu
  switch(currMenu) {
    case Menus::Tools:
      // want 3 spaces for this section: water can, hoe, scythe 
      for(uint8_t menuHeight = getImageHeight(Menu) + 15; menuHeight < menuBottom; menuHeight += 15) {
        arduboy.setCursor(menuLeft + 5, menuHeight - 3);
        arduboy.print(itemNum);
        arduboy.print(".");

        // names

        itemNum++;
      }
      // tools title
      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 0, 0);
      break;
    case Menus::Seeds:
      // Currently thinkin 4 seeds for this one
      for(uint8_t menuHeight = getImageHeight(Menu) + 15; menuHeight < menuBottom; menuHeight += 10) {
        arduboy.setCursor(menuLeft + 5, menuHeight - 3);
        arduboy.print(itemNum);
        arduboy.print(".");

        // names

        itemNum++;
      }
      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 1, 1);
      break;
    case Menus::Menu:
      // General menu stuff, this will be fairly unique compared to the other menus

      Sprites::drawExternalMask(WIDTH/2 + 3, 5, Menu, MenuMask, 2, 2);
      break;
  }
  
}

uint8_t getImageHeight(const uint8_t *image) {
  return pgm_read_byte_near(image + 1);
}

uint8_t getImageWidth(const uint8_t *image) {
  return pgm_read_byte_near(image);
}