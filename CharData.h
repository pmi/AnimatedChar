#ifndef _CharData_h
#define _CharData_h

#include "Arduino.h"

class CharData {
  public:
    CharData(){};
    CharData( char ch, byte* bytes, byte w, byte h ) {
        _char = ch;
        _bytes = bytes;
        _width = w;
        _height = h;
    };

    char  _char;
    byte* _bytes;
    byte  _width;
    byte  _height;
};

#endif