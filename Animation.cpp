/*
  Animation.h - Library for animations.
  Created by Pavel Milkevich, December 12, 2020.

  Inspired by
  https://github.com/lmirel/MorphingClockRemix/blob/master/Digit.cpp
*/
#include "Animation.h"
#include "gfxfont.h"
#include "Debugger.h"

Animation::Animation() : Animation( 500 ) {}

Animation::Animation( unsigned long duration ) {
    _duration = duration;
    _running = false;
    Debugger::debug( "Animation.constructor(%d): running=%s\n", duration, _running ? "true" : "false" );
}

bool Animation::isRunning() {
    return _running;
}

unsigned long Animation::getDuration() {
    return _duration;
}

void Animation::setDuration( unsigned long duration ) {
    _duration = duration;
}

void Animation::animate( char from, char to, const GFXfont* font ) {
    Debugger::debug( "Animation.animate [%c]->[%c]: font [%p]\n", from, to, font );
    _font = (GFXfont*) font;
    if ( from != to ) {
        Debugger::debug( "Animation.animate: starting animation\n" );

        Debugger::debug( "From char: [%c]\n", from );
        _fromData->_char = from;
        _fromData->_bytes = decodeBitmap( from, &_fromData->_width, &_fromData->_height );

        Debugger::debug( "To char: [%c]\n", to );
        _toData->_char = to;
        _toData->_bytes = decodeBitmap( to, &_toData->_width, &_toData->_height );

        _running = true;
        _startTime = millis();
        notify( STARTED, 0 );
    }
}

void Animation::stop() {
    Debugger::debug( "Animation.stop [%c]->[%c]\n", _fromData->_char, _toData->_char );

    _running = false;
    _startTime = 0;
    notify( STOPPED, 100 );
}

uint8_t* Animation::next() {
    if ( !_running ) {
        return 0;
    }
    unsigned long elapsed = millis() - _startTime;
    if ( elapsed > _duration ) {
        stop();
        return 0;
    }
    uint8_t prog = 100 * elapsed / _duration;
    notify( PROGRESS, prog);
    return getNextFrame( prog, _fromData->_bytes, _toData->_bytes );
}

byte* Animation::decodeBitmap( unsigned char c, byte* w, byte* h ) {
    Debugger::debug( "Animation.decodeBitmap: %c\n", c );
    c -= pgm_read_byte( &_font->first );
    GFXglyph* glyph = &( ( (GFXglyph*) pgm_read_ptr( &_font->glyph ) )[ c ] );
    uint8_t*  bitmap = (uint8_t*) pgm_read_ptr( &_font->bitmap );

    uint16_t bo = pgm_read_word( &glyph->bitmapOffset );
    *w = pgm_read_byte( &glyph->width );
    *h = pgm_read_byte( &glyph->height );
    Debugger::debug( "Width=%d, height =%d\n", *w, *h );
    int8_t xo = pgm_read_byte( &glyph->xOffset );
    int8_t yo = pgm_read_byte( &glyph->yOffset );
    byte   xx, yy, bitIndex, bitMask, currentBitmap, currentShift = 0;

    byte bytes[ *w ][ *h ];
    for ( yy = 0; yy < *h; yy++ ) {
        for ( xx = 0; xx < *w; xx++ ) {
            bitIndex = xx + *w * yy;
            currentShift = bitIndex & 7;  // verifies bitIndex is 1-7
            bitMask = 0x80 >> currentShift;

            if ( !currentShift ) {
                currentBitmap = pgm_read_byte( &bitmap[ bo++ ] );
            }

            if ( currentBitmap & bitMask ) {
                bytes[ xx ][ yy ] = 1;
                Debugger::debug( "[X]" );
            } else {
                Debugger::debug( "[ ]" );
            }
        }
        Debugger::debug( "\n" );
    }
    Debugger::debug( "Decompressed char: %p\n", (void*) *bytes );
    return *bytes;
}

void Animation::bind( AnimationListener* listener ) {
    _listeners[ _numListeners++ ] = listener;
    Debugger::debug( "Animation[%p] bound listener: %p\n", listener, this );
}

void Animation::unbind( AnimationListener* listener ) {
    for ( byte i = 0; i < _numListeners; i++ ) {
        if ( _listeners[ i ] == listener ) {
            // overwrite it with the remaining array
            for ( byte k = i; k < _numListeners - 1; k++ ) {
                _listeners[ k ] = _listeners[ i + 1 ];
            }
            _numListeners--;
            Debugger::debug( "Animation[%p] unbound listener: %p\n", (void*) this, (void*) listener );
            break;
        }
    }
}

void Animation::notify( AnimationStatus status, byte progress ) {
    for ( byte i = 0; i < _numListeners; i++ ) {
        AnimationListener* lis = _listeners[ i ];
        // Debugger::debug( "Animation[%p] notifying listener[%p]: %i\n", this, lis, progress );
        lis->onAnimation( status, _fromData->_char, _toData->_char, progress );
    }
}
