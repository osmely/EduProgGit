//
//  ConsoleViewer.h
//  NewProject
//
//  Created by Osmely Fernandez on 22/10/16.
//
//

#ifndef ConsoleViewer_h
#define ConsoleViewer_h



class ConsoleViewer:
public Component
{
public:
    ConsoleViewer (const String& name, const String& contents)
    : textValueObject (contents)
    {
        setName (name);

        editor.setMultiLine (true);
        editor.setReturnKeyStartsNewLine (true);
        editor.getTextValue().referTo (textValueObject);

        editor.setReadOnly (true);
        editor.setScrollbarsShown (true);
        editor.setCaretVisible (false);
        editor.setPopupMenuEnabled (true);
        editor.setColour (TextEditor::textColourId, Colours::white);
        editor.setColour (TextEditor::backgroundColourId, Colours::black);
        editor.setColour (TextEditor::highlightColourId, Colours::white);

        addAndMakeVisible (editor);
    }

    ~ConsoleViewer()
    {

    }

    void resized() override
    {
        editor.setBounds (getLocalBounds());
    }

    String getText(){
        return editor.getText();
    }

    void setText(const String &text){
        editor.setText(text);
    }

private:
    Value textValueObject;
    TextEditor editor;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleViewer)
};



#endif /* ConsoleViewer_h */
