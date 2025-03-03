#pragma once

// For uint8_t
#include <stdint.h>

// For PROGMEM
#include <avr/pgmspace.h>

constexpr uint8_t BGWidth { 8 };
constexpr uint8_t BGHeight { 8 };

constexpr uint8_t BG[] PROGMEM
{
	// Width, Height
	BGWidth, BGHeight,
	
	// Frame 0
	0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00,
	
	// Frame 1
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t FarmerWalkWidth { 16 };
constexpr uint8_t FarmerWalkHeight { 16 };

constexpr uint8_t FarmerWalk[] PROGMEM
{
	// Width, Height
	FarmerWalkWidth, FarmerWalkHeight,
	
	// South 0
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xCF, 0xB3, 0x3F, 0xBF, 0xB3, 0xCF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x7F, 0x7F, 0x08, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// South 1
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xCF, 0xB3, 0x3F, 0xBF, 0xB3, 0xCF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x08, 0x0F, 0x7F, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// West 2
	0x00, 0x00, 0x00, 0x02, 0xC2, 0x0F, 0xB3, 0xBF, 0xB3, 0xDF, 0xEF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x78, 0x7F, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// West 3
	0x00, 0x00, 0x00, 0x02, 0xC2, 0x0F, 0xB3, 0xBF, 0xB3, 0xDF, 0xEF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0xFF, 0x0F, 0x0F, 0x7F, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// North 4
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xCF, 0xBF, 0xBF, 0xBF, 0xBF, 0xCF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x7F, 0x7F, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// North 5
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xCF, 0xBF, 0xBF, 0xBF, 0xBF, 0xCF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x0F, 0x0F, 0x7F, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// East 6
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xEF, 0xDF, 0xB3, 0xBF, 0xB3, 0x0F, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x7F, 0x7F, 0x0F, 0x0F, 0xFF, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// East 7
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xEF, 0xDF, 0xB3, 0xBF, 0xB3, 0x0F, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x0F, 0x0F, 0x7F, 0x78, 0x0F, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t FarmerWidth { 16 };
constexpr uint8_t FarmerHeight { 16 };

constexpr uint8_t Farmer[] PROGMEM
{
	// Width, Height
	FarmerWidth, FarmerHeight,
	
	// Frame 0
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xCF, 0xB3, 0x3F, 0xBF, 0xB3, 0xCF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x08, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t FarmerMaskWidth { 16 };
constexpr uint8_t FarmerMaskHeight { 16 };

constexpr uint8_t FarmerMask[] PROGMEM
{
	// Frame 0
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
};

constexpr uint8_t FarmerWalkMaskWidth { 16 };
constexpr uint8_t FarmerWalkMaskHeight { 16 };

constexpr uint8_t FarmerWalkMask[] PROGMEM
{
	// Frame 0
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x7F, 0x7F, 0x0F, 0x0F, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
	
	// Frame 1
	0x00, 0x00, 0x00, 0x02, 0xC2, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC2, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x0F, 0x0F, 0x7F, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00,
};
