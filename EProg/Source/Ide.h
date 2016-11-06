

#ifndef __JUCE_HEADER_1C2FC31221CA8C__
#define __JUCE_HEADER_1C2FC31221CA8C__


#include "JuceHeader.h"
#include "Compiler.h"
#include "AppMultiDocumentPanel.h"
#include "CodeEditor.h"
#include "LienzoViewer.h"
#include "ConsoleViewer.h"


class Ide  : public Component, public ButtonListener
{
public:

    Ide ();
    ~Ide();
    static Ide* instance;


    void paint (Graphics& g);
    void resized();

    void updateLayoutMode(){
        multiDocumentPanel.setLayoutMode (MultiDocumentPanel::FloatingWindows);
    }


    void setCommonProperties(MultiDocumentPanelWindow* window){
        window->setTitleBarButtonsRequired(juce::DialogWindow::closeButton, true);
        window->setTitleBarHeight(24);
        window->setTitleBarTextCentred(false);
    }


    CodeEditor* addCodeEditor (const String& name, const String& content){
        CodeEditor* newNote = new CodeEditor (name, content);
        newNote->setSize (350, 200);
        multiDocumentPanel.addDocument (newNote, Colours::lightblue.withAlpha (0.6f), true);

        MultiDocumentPanelWindow* window = static_cast<MultiDocumentPanelWindow*>(multiDocumentPanel.getDocument(multiDocumentPanel.getNumDocuments()-1)->getParentComponent());
        setCommonProperties(window);

        return newNote;
    }

    LienzoViewer* addLienzoViewer (const String& name, const Image& content){
        LienzoViewer* newNote = new LienzoViewer (name, content);
        newNote->setSize (200, 200);
        multiDocumentPanel.addDocument (newNote, Colours::lightblue.withAlpha (0.6f), true);

        MultiDocumentPanelWindow* window = static_cast<MultiDocumentPanelWindow*>(multiDocumentPanel.getDocument(multiDocumentPanel.getNumDocuments()-1)->getParentComponent());
        setCommonProperties(window);

        return newNote;
    }

    ConsoleViewer* findConsole(const String &viewName){
        //buscar visor con ese nombre y pasarle la data.
        int countD = multiDocumentPanel.getNumDocuments();
        for (int i = 0; i < countD; i++) {
            if (ConsoleViewer* view = dynamic_cast<ConsoleViewer*> (multiDocumentPanel.getDocument(i))){
                if(view->getName() == viewName){
                    return view;
                }
            };
        }

        return nullptr;
    }

    ConsoleViewer* addConsoleViewer (const String& name, const String& content){
        ConsoleViewer* newNote = new ConsoleViewer (name, content);
        newNote->setSize (200, 50);
        multiDocumentPanel.addDocument (newNote, Colours::lightblue.withAlpha (0.6f), true);

        MultiDocumentPanelWindow* window = static_cast<MultiDocumentPanelWindow*>(multiDocumentPanel.getDocument(multiDocumentPanel.getNumDocuments()-1)->getParentComponent());
        setCommonProperties(window);

        return newNote;
    }

    void showImageInViewer(const Image &image, const String &viewName){
        //buscar visor con ese nombre y pasarle la data.
        int countD = multiDocumentPanel.getNumDocuments();
        for (int i = 0; i < countD; i++) {
            if (LienzoViewer* lienzo = dynamic_cast<LienzoViewer*> (multiDocumentPanel.getDocument(i))){
                if(lienzo->getName() == viewName){
                    lienzo->setImage(image);
                    //break;
                }
            };
        }
    }

    void printTextInConsole(const String &text, const String &viewName){
        //buscar visor con ese nombre y pasarle la data.
        int countD = multiDocumentPanel.getNumDocuments();
        for (int i = 0; i < countD; i++) {
            if (ConsoleViewer* view = dynamic_cast<ConsoleViewer*> (multiDocumentPanel.getDocument(i))){
                if(view->getName() == viewName){
                    view->setText(text);
                    //break;
                }
            };
        }
    }

private:
    Compiler *_compiler;

    void buttonClicked (Button* buttonThatWasClicked);

    ScopedPointer<DrawableButton> buildButton;
    ScopedPointer<DrawableButton> runButton;
    ScopedPointer<DrawableButton> addConsolaButton;
    ScopedPointer<DrawableButton> addLienzoButton;
    ScopedPointer<DrawableButton> addCodeButton;

    AppMultiDocumentPanel multiDocumentPanel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ide)
};


#endif   // __JUCE_HEADER_1C2FC31221CA8C__
