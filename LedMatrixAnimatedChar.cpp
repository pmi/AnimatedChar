/*
  AnimatedChar.cpp - Library for animated characters.
  Created by Pavel Milkevich, December 12, 2020.

  Inspired by
  https://github.com/lmirel/MorphingClockRemix/blob/master/Digit.cpp
*/
#include "LedMatrixAnimatedChar.h"
#include "Debugger.h"

LedMatrixAnimatedChar::LedMatrixAnimatedChar( cLEDMatrixBase* matrix, const GFXfont* font )
    : LedMatrixAnimatedChar( matrix, font, '0' ) {
    Debugger::debug( "LedMatrixAnimatedChar constructor()\n" );
}

LedMatrixAnimatedChar::LedMatrixAnimatedChar( cLEDMatrixBase* matrix, const GFXfont* font, char ch )
    : AnimatedChar( font, ch ) {
    Debugger::debug( "LedMatrixAnimatedChar constructor(%p, %c)\n", matrix, ch );
    _matrix = matrix;
    Debugger::debug( "Created LedMatrixAnimatedChar[%p]: %c\n", this, ch );
}

void LedMatrixAnimatedChar::printFrame( uint8_t* bitmap ) {
    _matrix->drawBitmap( (int16_t) _x, (int16_t) _y, bitmap, (int16_t) _w, (int16_t) _h, CRGB::Red ); //TODO: store color in AnimatedChar
}