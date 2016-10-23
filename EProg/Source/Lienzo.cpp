//
//  Lienzo.cpp
//  NewProject
//
//  Created by Osmely Fernandez on 3/9/16.
//
//

#include "Lienzo.h"



Lienzo::Lienzo(int w, int h, const agg::rgba8 &color){
    _w = w;
    _h = h;
    if(this->beginContext(w, h, color)){

    }
}

Lienzo::~Lienzo(){
    this->clearContext();
}

Image Lienzo::getImage(){

    int width = _w;
    int height = _h;
    Image image = Image (Image::RGB, (int) width, (int) height, false);

    const Image::BitmapData destData (image, Image::BitmapData::writeOnly);
    for (int y = 0; y < (int) height; ++y){
        const uint8* src = (this->buffer)->row(y);

        uint8* dest = destData.getLinePointer (y);
        for (int i = (int) width; --i >= 0;){
            ((PixelARGB*) dest)->setARGB (255, src[0], src[1], src[2]);
            dest += destData.pixelStride;
            src += 3;
        }
    }

    return image;
}
