/*
  AnimatedChar.h - Library for animated characters.
  Created by Pavel Milkevich, December 12, 2020.
*/
#ifndef _LedMatrixAnimatedChar_h
#define _LedMatrixAnimatedChar_h

#include "Arduino.h"
#include <FastLED.h>
#include <FastLED_GFX.h>
#include <FastLEDMatrix.h>
#include "gfxfont.h"
#include "AnimatedChar.h"

class LedMatrixAnimatedChar : public AnimatedChar {
  public:
    LedMatrixAnimatedChar( cLEDMatrixBase* matrix, const GFXfont* font );
    LedMatrixAnimatedChar( cLEDMatrixBase* matrix, const GFXfont* font, char ch );

  protected:
    void printFrame( uint8_t* data );

  private:
    cLEDMatrixBase* _matrix;
};

#endif
