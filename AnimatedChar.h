/*
  AnimatedChar.h - Library for animated characters.
  Created by Pavel Milkevich, December 12, 2020.
*/
#ifndef _AnimatedChar_h
#define _AnimatedChar_h

#include "Arduino.h"
#include "gfxfont.h"
#include "Animation.h"

class AnimatedChar : AnimationListener {
  public:
    AnimatedChar();
    AnimatedChar( const GFXfont* font );
    AnimatedChar( const GFXfont* font, char ch );
    Animation* getAnimation();
    void       setAnimation( Animation* animation );
    void       setPosition( int x, int y );
    char       getChar();
    void       animateTo( char ch );
    void       stopAnimation();
    bool       isAnimating();
    void       setVisible( bool visible );
    void       next();
    void       onAnimation( AnimationStatus status, char from, char to, byte progress );

  protected:
    virtual void printFrame( uint8_t* data ) = 0;
    int          _x = 0;
    int          _y = 0;
    int          _w = 0;
    int          _h = 0;

  private:
    bool       _visible = true;
    char       _char;
    Animation* _anim = nullptr;
    GFXfont*   _font;
};

#endif
