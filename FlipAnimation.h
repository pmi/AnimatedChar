/*
  FlipAnimation.h - Library for animations.
  Created by Pavel Milkevich, December 19, 2020.
*/
#ifndef _FlipAnimation_h
#define _FlipAnimation_h

#include "Arduino.h"
#include "Animation.h"

class FlipAnimation : public Animation {
  public:
    FlipAnimation( unsigned long duration );

  protected:
    uint8_t* getNextFrame( uint8_t elapsedTime, byte* startBytes, byte* endBytes  );
};

#endif