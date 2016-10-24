

#include "MainComponent.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <iostream>  // cout
#include <assert.h>  // assert()
#include <string.h>
#include <sys/time.h>




//==============================================================================
MainContentComponent::MainContentComponent()
{

    setSize (1200, 800);


    comp = new Compiler();


    const char *script1 =
    "int count = 0;                     "
    "void main()                        "
    "{                                  "

    "  Print(count++);                  "
    "}                                  "
    ;



    //comp->build(script1);



    setFramesPerSecond(5);

}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::update() {

}

void MainContentComponent::paint (Graphics& g){


    int width = getWidth();
    int height = getHeight();

    Lienzo * l = new Lienzo(width, height);

    l->fill_ellipse(width/2, height/2, 200, 100, agg::rgba8(0,230,230));
    l->fill_ellipse(width/2, height/2 + 100, 200, 100, agg::rgba8(230,20,230,100));
    l->fill_line(10,10, 200, 300, 20, agg::rgba8(230,120,30,200));

    Image image = l->getImage();

    g.drawImageTransformed(image, RectanglePlacement (RectanglePlacement::centred)
                           .getTransformToFit (image.getBounds().toFloat(),
                                               getLocalBounds().toFloat()), false);


    delete l;



    comp->run(false);

}

void MainContentComponent::resized(){


}








