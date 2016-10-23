

#include "Ide.h"
Ide* Ide::instance = nullptr;

//==============================================================================
Ide::Ide ()
{


    addAndMakeVisible (multiDocumentPanel);
    multiDocumentPanel.setBackgroundColour (Colours::beige);

    addAndMakeVisible (buildButton = new TextButton ("new button"));
    buildButton->setButtonText (TRANS("BUILD"));
    buildButton->addListener (this);


    addAndMakeVisible (runButton = new TextButton ("new button"));
    runButton->setButtonText (TRANS("RUN"));
    runButton->addListener (this);

    addAndMakeVisible (addConsolaButton = new TextButton ("new button"));
    addConsolaButton->setButtonText (TRANS("Consola++"));
    addConsolaButton->addListener (this);

    addAndMakeVisible (addLienzoButton = new TextButton ("new button"));
    addLienzoButton->setButtonText (TRANS("Lienzo++"));
    addLienzoButton->addListener (this);








    //[Constructor] You can add your own custom stuff here..
    _compiler = new Compiler();
    _compiler->callback = [=](const std::string &msg){
        ConsoleViewer *consola = findConsole("Consola");
        if(consola){
            std::stringstream text;
            text << consola->getText().toRawUTF8();
            text << msg.c_str();
            consola->setText(text.str());
        }
    };


    std::stringstream code;

    code << "int px = 0;\n";

    code << "void main(){\n";
    code << "    px = px + 2;\n";
    code << "    Lienzo a(200,200);\n";
    code << "    a.rellenar_elipse(100 + px,100,50,30,Color(200,100,100,255));\n";
    code << "    MostrarLienzo(a, \"Lienzo\");\n";
    code << "    MostrarTexto(\"px: \" + px, \"Consola2\");\n";
    code << "    MostrarTexto(\"px: \" + px + \"\\n\");\n";
    code << "}\n";
    


    updateLayoutMode();

    _firstEditor = addCodeEditor ("Main", code.str());
    addConsoleViewer("Consola", "");



    
    instance = this;


    setSize (600, 400);
}

Ide::~Ide(){
    runButton = nullptr;
    buildButton = nullptr;
}


void Ide::paint (Graphics& g){
    g.fillAll (Colour (0xff));
}

void Ide::resized(){
    Rectangle<int> area (getLocalBounds());
    multiDocumentPanel.setBounds (area);

    runButton->setBounds (getWidth() - 72, 16, 64, 24);
    buildButton->setBounds (getWidth() - 172, 16, 64, 24);
    addConsolaButton->setBounds (getWidth() - 250, 16, 64, 24);
    addLienzoButton->setBounds (getWidth() - 350, 16, 64, 24);


}

void Ide::buttonClicked (Button* buttonThatWasClicked){

    printTextInConsole("", "Consola");


    if (buttonThatWasClicked == runButton){
        _compiler->run(false);

    }else if (buttonThatWasClicked == buildButton){
        std::string script = _firstEditor->getText().toStdString();

        if(_compiler->build(script) >= 0){

        }else{
            _compiler->clear();
        }

    }else if(buttonThatWasClicked == addConsolaButton){
        AlertWindow w ("Agregar nueva consola",
                       "Establezca el Identificador de la nueva consola",
                       AlertWindow::QuestionIcon);

        w.addTextEditor ("text", "", "Identificador:");

        w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

        if (w.runModalLoop() != 0) {
            String text = w.getTextEditorContents ("text");
            addConsoleViewer(text, "");

        }
    }else if(buttonThatWasClicked == addLienzoButton){
        AlertWindow w ("Agregar nuevo visor de lienzos",
                       "Establezca el Identificador del nuevo visor de lienzos",
                       AlertWindow::QuestionIcon);

        w.addTextEditor ("text", "", "Identificador:");

        w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

        if (w.runModalLoop() != 0) {
            String text = w.getTextEditorContents ("text");
            addLienzoViewer(text, Image());
        }

    }

}

