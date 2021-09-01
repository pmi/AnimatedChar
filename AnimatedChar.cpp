/*
  AnimatedChar.cpp - Library for animated characters.
  Created by Pavel Milkevich, December 12, 2020.

  Inspired by
  https://github.com/lmirel/MorphingClockRemix/blob/master/Digit.cpp
*/
#include "Arduino.h"
#include "gfxfont.h"
#include "AnimatedChar.h"
#include "FlipAnimation.h"
#include "Debugger.h"

AnimatedChar::AnimatedChar() : AnimatedChar( nullptr ) {
    Debugger::debug( "AnimatedChar constructor()\n" );
}

AnimatedChar::AnimatedChar( const GFXfont* font ) : AnimatedChar( font, '0' ) {
    Debugger::debug( "AnimatedChar constructor(%p)\n", font );
}

AnimatedChar::AnimatedChar( const GFXfont* font, char ch ) {
    Debugger::debug( "AnimatedChar constructor(%p, %c)\n", font, ch );
    _font = (GFXfont*) font;
    _char = ch;
    Animation* anim = new FlipAnimation( 500 );
    setAnimation( anim );
    Debugger::debug( "Created AnimatedChar[%p]: %c\n", this, ch );
}

Animation* AnimatedChar::getAnimation() {
    return _anim;
}

void AnimatedChar::setAnimation( Animation* anim ) {
    if ( _anim != nullptr ) {
        _anim->unbind( this );
    }
    _anim = anim;
    if ( anim != nullptr ) {
        _anim->bind( this );
    }
}

char AnimatedChar::getChar() {
    return _char;
}

void AnimatedChar::setPosition( int x, int y ) {
    _x = x;
    _y - y;
}

void AnimatedChar::animateTo( char to ) {
    Debugger::debug( "AnimatedChar.animateTo [%c]->[%c]: animation [%p]\n", _char, to, _anim );
    _anim->animate( _char, to, _font );
}

void AnimatedChar::stopAnimation() {
    _anim->stop();
}

void AnimatedChar::setVisible( bool visible ) {
    _visible = visible;
}

void AnimatedChar::next() {
    if ( !_visible || !_anim->isRunning() ) {
        return;
    } else {
        printFrame( _anim->next() );
    }
}

void AnimatedChar::onAnimation( AnimationStatus status, char from, char to, byte progress ) {
    if ( status == STOPPED && progress >= 100 ) {
        _char = to;
        Debugger::debug( "AnimatedChar.onAnimation: done animation from[%c] to[%c]\n", from, to );
    }
}