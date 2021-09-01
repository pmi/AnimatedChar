/*
  Animation.h - Library for animations.
  Created by Pavel Milkevich, December 12, 2020.
*/
#ifndef _Animation_h
#define _Animation_h

#include "Arduino.h"
#include "gfxfont.h"
#include "AnimationListener.h"
#include "Debugger.h"
#include "CharData.h"

class Animation {
  public:
    Animation();
    Animation( unsigned long duration );
    unsigned long getDuration();
    void          setDuration( unsigned long duration );
    void          animate( char from, char to, const GFXfont* font );
    void          stop();
    uint8_t*      next();
    bool          isRunning();
    void          bind( AnimationListener* listener );
    void          unbind( AnimationListener* listener );

  protected:
    virtual uint8_t* getNextFrame( uint8_t elapsedTime, byte* startBytes, byte* endBytes ) = 0;
    byte*            decodeBitmap( unsigned char c, byte* w, byte* h );
    uint8_t          encodeBitmap( byte* matrix, byte w, byte h );
    void             notify( AnimationStatus status, byte progress );

  private:
    byte               _numListeners = 0;
    bool               _running = false;
    unsigned long      _duration = 500;
    CharData*          _fromData = new CharData();
    CharData*          _toData = new CharData();
    unsigned long      _startTime = 0;
    GFXfont*           _font;
    AnimationListener* _listeners[];
};

#endif
