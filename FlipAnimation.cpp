/*
  Animation.h - Library for animations.
  Created by Pavel Milkevich, December 12, 2020.

  Inspired by
  https://github.com/lmirel/MorphingClockRemix/blob/master/Digit.cpp
*/
#include "FlipAnimation.h"
#include "Arduino.h"
#include "Debugger.h"

FlipAnimation::FlipAnimation( unsigned long duration ) : Animation( duration ) {}

uint8_t* FlipAnimation::getNextFrame( uint8_t progress, byte* startBytes, byte* endBytes ) {
    Debugger::debug( "FlipAnimation.getNextFrame: %d\n", progress, getDuration() );
    return 0;  // TODO: implement me !
}
