//
//  CodeEditor.h
//  NewProject
//
//  Created by Osmely Fernandez on 22/10/16.
//
//

#ifndef CodeEditor_h
#define CodeEditor_h

#include "JuceHeader.h"


class CodeEditor:
public Component,
private TextEditor::Listener
{
public:
    CodeEditor (const String& name, const String& contents)
    : textValueObject (contents)
    {
        setName (name);

        editor.setMultiLine (true);
        editor.setReturnKeyStartsNewLine (true);
        editor.getTextValue().referTo (textValueObject);
        addAndMakeVisible (editor);
        editor.addListener (this);


        //addAndMakeVisible(code = new CodeEditorComponent(doc, &tokeniser));
    }

    ~CodeEditor()
    {
        editor.removeListener (this);
    }

    void resized() override
    {
        editor.setBounds (getLocalBounds());
        //code->setBounds (getLocalBounds());
    }

    String getText(){
        return editor.getText();
    }

private:
    Value textValueObject;
    TextEditor editor;

    void textEditorTextChanged (TextEditor& ed) override
    {
        // let our FileBasedDocument know we've changed
//        if (&ed == &editor)
//            changed();
    }

    void textEditorReturnKeyPressed (TextEditor&) override {}
    void textEditorEscapeKeyPressed (TextEditor&) override {}
    void textEditorFocusLost (TextEditor&) override {}




//    CodeDocument doc;
//    CPlusPlusCodeTokeniser tokeniser;
//    ScopedPointer<CodeEditorComponent> code;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeEditor)
};

#endif /* CodeEditor_h */


