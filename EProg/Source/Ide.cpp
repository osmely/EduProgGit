

#include "Ide.h"
#include "ImagesIde.h"
Ide* Ide::instance = nullptr;

#define defineImagesStates(__PREFIX__, __imageData__, __imageSize__)  DrawableImage __PREFIX__ ## _Image_normal; \
__PREFIX__ ## _Image_normal.setImage (ImageCache::getFromMemory (__imageData__, __imageSize__)); \
 \
DrawableImage __PREFIX__ ## _Image_down; \
__PREFIX__ ## _Image_down.setImage (ImageCache::getFromMemory (__imageData__, __imageSize__)); \
__PREFIX__ ## _Image_down.setOverlayColour (Colours::black.withAlpha (0.3f)); \
 \
DrawableImage __PREFIX__ ## _Image_over; \
__PREFIX__ ## _Image_over.setImage (ImageCache::getFromMemory (__imageData__, __imageSize__)); \
__PREFIX__ ## _Image_over.setOverlayColour (Colours::green.withAlpha (0.05f)); \




//==============================================================================
Ide::Ide ()
{


    addAndMakeVisible (multiDocumentPanel);
    multiDocumentPanel.setBackgroundColour (Colour::fromRGBA(0,0,0,0));

    defineImagesStates(build, build_png, build_pngSize)
    addAndMakeVisible (buildButton = new DrawableButton ("new button", DrawableButton::ImageFitted));
    buildButton->setImages (&build_Image_normal, &build_Image_over, &build_Image_down);
    buildButton->addListener (this);
    buildButton->setTooltip("Compilar");


    defineImagesStates(play, play_png, play_pngSize)
    addAndMakeVisible (runButton = new DrawableButton ("new button", DrawableButton::ImageFitted));
    runButton->setImages (&play_Image_normal, &play_Image_over, &play_Image_down);
    runButton->addListener (this);
    runButton->setTooltip("Ejecutar");


    defineImagesStates(consola, consola_png, consola_pngSize)
    addAndMakeVisible (addConsolaButton = new DrawableButton ("new button", DrawableButton::ImageFitted));
    addConsolaButton->setImages (&consola_Image_normal, &consola_Image_over, &consola_Image_down);
    addConsolaButton->addListener (this);
    addConsolaButton->setTooltip("Agregar una nueva consola");


    defineImagesStates(lienzo, lienzo_png, lienzo_pngSize)
    addAndMakeVisible (addLienzoButton = new DrawableButton ("new button", DrawableButton::ImageFitted));
    addLienzoButton->setImages (&lienzo_Image_normal, &lienzo_Image_over, &lienzo_Image_down);
    addLienzoButton->addListener (this);
    addConsolaButton->setTooltip("Agregar un lienzo");


    defineImagesStates(module, module_png, module_pngSize)
    addAndMakeVisible (addCodeButton = new DrawableButton ("new button", DrawableButton::ImageFitted));
    addCodeButton->setImages (&module_Image_normal, &module_Image_over, &module_Image_down);
    addCodeButton->addListener (this);
    addCodeButton->setTooltip("Agregar un nuevo modulo");



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


    addCodeEditor ("Main", code.str());
    addConsoleViewer("Consola", "");


    instance = this;
    setSize (800, 600);
}

Ide::~Ide(){
    runButton = nullptr;
    buildButton = nullptr;
}

void Ide::paint (Graphics& g){
    g.fillAll (Colours::beige);
    g.setColour (Colour (0xffa52a97));
    g.fillRect (36, 180, 100, 100);
}

void Ide::resized(){
    Rectangle<int> area (getLocalBounds());
    multiDocumentPanel.setBounds (area);

    int margen = 50;
    int deltab = 2;
    int deltaSections = 10;

    buildButton->setBounds (getWidth() - margen, 16, 45, 44);
    runButton->setBounds (getWidth() - margen, buildButton->getBottom() + deltab, 45, 44);

    addCodeButton->setBounds (getWidth() - margen, runButton->getBottom() + deltaSections, 45, 44);
    addConsolaButton->setBounds (getWidth() - margen, addCodeButton->getBottom() + deltab, 45, 44);
    addLienzoButton->setBounds (getWidth() - margen, addConsolaButton->getBottom() + deltab, 45, 44);
}

void Ide::buttonClicked (Button* buttonThatWasClicked){

    printTextInConsole("", "Consola");


    if (buttonThatWasClicked == runButton){
        _compiler->run(false);

    }else if (buttonThatWasClicked == buildButton){


        int countD = multiDocumentPanel.getNumDocuments();

        if(countD == 0)
            return;
        
        _compiler->clear();

        int result = 0;

        for (int i = 0; i < countD; i++) {
            if (CodeEditor* view = dynamic_cast<CodeEditor*> (multiDocumentPanel.getDocument(i))){

                std::string code = view->getText().toStdString();
                if(code.length() > 0)
                   result = _compiler->addSection(code, view->getName().toStdString());

                if(result < 0){
                    break;
                }
            };
        }


        if(result == 0){
            _compiler->build();
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

    }else if(buttonThatWasClicked == addCodeButton){
        AlertWindow w ("Agregar nuevo modulo",
                       "Establezca el Identificador del nuevo modulo",
                       AlertWindow::QuestionIcon);

        w.addTextEditor ("text", "", "Identificador:");

        w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

        if (w.runModalLoop() != 0) {
            String text = w.getTextEditorContents ("text");
            addCodeEditor(text, "");
        }
    }
    
}

