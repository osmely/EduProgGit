//
//  LienzoViewer.h
//  NewProject
//
//  Created by Osmely Fernandez on 22/10/16.
//
//

#ifndef LienzoViewer_h
#define LienzoViewer_h

#include "JuceHeader.h"


class LienzoViewer:
public Component
{
public:
    LienzoViewer (const String& name, const Image& contents)
    {
        setName (name);
        addAndMakeVisible (_imagecomp);
        setImage(contents);
    }

    ~LienzoViewer()
    {

    }

    void resized() override
    {
        _imagecomp.setBounds (getLocalBounds());
    }

    void setImage(const Image &image){
        _imagecomp.setImage(image);
    }


private:
    Value imageValueObject;
    ImageComponent _imagecomp;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LienzoViewer)
};

#endif /* LienzoViewer_h */
