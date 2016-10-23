//
//  Lienzo.hpp
//  NewProject
//
//  Created by Osmely Fernandez on 3/9/16.
//
//

#ifndef Lienzo_hpp
#define Lienzo_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AGGGraphicContext.h"
#include "Compiler.h"

class Lienzo : public AGGGraphicContext {

    Image _image;
    int _w;
    int _h;

public:
    Lienzo():
    _w(1),
    _h(1)
    {

    }
    
    Lienzo(int w, int h, const agg::rgba8 &color = agg::rgba8(255, 255, 255, 0));
    ~Lienzo();
    Image getImage();

    Lienzo& operator= (const Lienzo& other){
        _w = other._w;
        _h = other._h;
        _image = other._image;
        return *this;
    }

};



#endif /* Lienzo_hpp */
