//
//  MultiDocumentPanel.h
//  NewProject
//
//  Created by Osmely Fernandez on 22/10/16.
//
//

#ifndef MultiDocumentPanel_h
#define MultiDocumentPanel_h


#include "JuceHeader.h"
#include "CodeEditor.h"

class AppMultiDocumentPanel    : public MultiDocumentPanel
{
public:
    AppMultiDocumentPanel()
    {
    }

    ~AppMultiDocumentPanel()
    {
        closeAllDocuments (true);
    }

    bool tryToCloseDocument (Component* component) override
    {

//        if (Note* note = dynamic_cast<Note*> (component))
//            return note->saveIfNeededAndUserAgrees() != FileBasedDocument::failedToWriteToFile;


        return true;
    }


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppMultiDocumentPanel)
};


#endif /* MultiDocumentPanel_h */
