//
//  Compiler.cpp
//  NewProject
//
//  Created by Osmely Fernandez on 3/9/16.
//
//

#include "Compiler.h"

#include "Ide.h"
class Ide;


Compiler* Compiler::instance = nullptr;

void Compiler::MessageCallback(const asSMessageInfo *msg, void *param)
{
    const char *type = ">ERROR: ";
    if( msg->type == asMSGTYPE_WARNING )
        type = ">WARNING: ";
    else if( msg->type == asMSGTYPE_INFORMATION )
        type = "";

    Compiler *c = (Compiler*)param;
    std::stringstream msgC;

    std::stringstream pos;
    if(msg->row != -1 && msg->col != -1){
       msgC <<  "(" << msg->row << ", " << msg->col << ")";
    }

    std::stringstream seccion;
    if(strlen(msg->section) > 0){
        seccion << " <" << msg->section << "> ";
    }


    msgC << type << seccion.str() << pos.str() << msg->message << "\n";
    c->printConsole(msgC.str());
}

void Compiler::printConsole(const std::string &msg){
    if(this->callback)
        callback(msg);
}

void PrintNumber(int num){
    std::stringstream msg;
    msg << num;
    std::cout << msg.str() << "\n";

    Compiler::instance->printConsole(msg.str());
}

void printString(const std::string &msg){
    Compiler::instance->printConsole(msg);
}

void PrintLienzo(void *ref, const std::string &name, int typeId){
    Lienzo *aaa = (Lienzo*)ref;
    Ide::instance->showImageInViewer(aaa->getImage(), name);
}

void printConsoleViewer(const std::string &text, const std::string &name, int typeId){
    Ide::instance->printTextInConsole(text, name);
}


Compiler::Compiler(){
    callback = nullptr;

    Compiler::instance = this;

    engine = asCreateScriptEngine();
    int r = engine->SetMessageCallback(asFUNCTION(Compiler::MessageCallback), this, asCALL_CDECL); assert( r >= 0 );

    r = configureEngine();
    assert( r >= 0 );
}

void Compiler::clear(){
    if(scriptContext)
        scriptContext->Release();
    scriptContext = nullptr;
}

int Compiler::run(bool resetGlobals){

    int r = 0;

    if(scriptContext && mainF){
        
        r = scriptContext->Prepare(mainF);

        r = scriptContext->GetState();

        if( r < 0 ){
            engine->WriteMessage("", -1, -1, asMSGTYPE_ERROR, "Failed to prepare the context.");
            return -1;
        }

        if(resetGlobals)
            mod->ResetGlobalVars();

        r = scriptContext->Execute();

        r = scriptContext->GetState();
        if( r == asEXECUTION_FINISHED ){
            if( r != asEXECUTION_EXCEPTION ){
                engine->WriteMessage("", -1, -1, asMSGTYPE_INFORMATION, "OK");
            }
        }

        return 0;

    }else{
        return -1;
    }

}


int Compiler::build(const std::string &script){

    int r = 0;
    std::string moduleName = "Script";
    mod = engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);

    r = mod->AddScriptSection(moduleName.c_str(), script.c_str(), strlen(script.c_str()));
    if( r < 0 ){
        engine->WriteMessage(moduleName.c_str(), -1, -1, asMSGTYPE_ERROR, "Internal error: AddScriptSection() failed");
        clear();
        return -1;
    }

    r = mod->Build();
    if( r < 0 ){
        clear();
        //engine->WriteMessage(moduleName.c_str(), -1, -1, asMSGTYPE_ERROR, "Build failed.");
        return -1;
    }

    scriptContext = engine->CreateContext();
    if( scriptContext == 0 )
    {
        engine->WriteMessage(moduleName.c_str(), -1, -1, asMSGTYPE_ERROR, "Internal error: Failed to create the context.");
        clear();
        return -1;
    }

    mainF = mod->GetFunctionByDecl("void main()");

    if(!mainF){
        engine->WriteMessage(moduleName.c_str(), -1, -1, asMSGTYPE_ERROR, "Cannot find 'void main()'");
        clear();
        return -1;
    }
    
    
    return r;
}

void ConstructTime(Lienzo* thisPointer){
    new(thisPointer) Lienzo();
}

void ConstructTime1(int w, int h, Lienzo* thisPointer){
    new(thisPointer) Lienzo(w, h);
}

void DestructTime(Lienzo* thisPointer){
    if(thisPointer != nullptr){
        thisPointer->~Lienzo();
        thisPointer = nullptr;
    }
}



void ConstructColor(agg::rgba8* thisPointer){
    new(thisPointer) agg::rgba8();
}

void ConstructColor1(int r, int g, int b, int a, agg::rgba8* thisPointer){
    new(thisPointer) agg::rgba8(r,g,b,a);
}

void DestructColor(agg::rgba8* thisPointer){
    if(thisPointer != nullptr){
        thisPointer->~rgba8();
        thisPointer = nullptr;
    }
}


int Compiler::configureEngine(){
    int r = 0;
    
    // Register the string type
    RegisterStdString(engine);

    // Register the generic handle type, called 'ref' in the script
    RegisterScriptHandle(engine);

    // Register the weak ref template type
    RegisterScriptWeakRef(engine);




    r = engine->RegisterGlobalFunction("void Print(int)", asFUNCTION(PrintNumber), asCALL_CDECL); assert( r >= 0 );
    r = engine->RegisterGlobalFunction("void MostrarTexto(string)", asFUNCTION(printString), asCALL_CDECL); assert( r >= 0 );

    r = engine->RegisterObjectType("Lienzo", sizeof(Lienzo), asOBJ_VALUE | asOBJ_ASHANDLE | asOBJ_APP_CLASS_CD); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("Lienzo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("Lienzo", asBEHAVE_CONSTRUCT, "void f(int,int)", asFUNCTION(ConstructTime1), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("Lienzo", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(DestructTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectMethod("Lienzo", "Lienzo& opAssign(const Lienzo& in)", asMETHODPR(Lienzo, operator=, (const Lienzo&), Lienzo&), asCALL_THISCALL); jassert( r >= 0 );




    r = engine->RegisterObjectType("Color", sizeof(agg::rgba8), asOBJ_VALUE | asOBJ_ASHANDLE | asOBJ_APP_CLASS_CD); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructColor), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(int,int,int,int)", asFUNCTION(ConstructColor1), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(DestructColor), asCALL_CDECL_OBJLAST); jassert(r>=0);

    r = engine->RegisterObjectMethod("Color", "Color& opAssign(const Color& in)", asMETHODPR(agg::rgba8, operator=, (const agg::rgba8&), agg::rgba8&), asCALL_THISCALL); jassert( r >= 0 );





    r = engine->RegisterGlobalFunction("void MostrarLienzo(const Lienzo& in, string)", asFUNCTION(PrintLienzo), asCALL_CDECL); assert( r >= 0 );

    r = engine->RegisterObjectMethod("Lienzo", "void rellenar_elipse(double x,  double y, double rx, double ry, Color c)", asMETHOD(Lienzo, fill_ellipse), asCALL_THISCALL);
    assert( r >= 0 );

    r = engine->RegisterGlobalFunction("void MostrarTexto(string, string)", asFUNCTION(printConsoleViewer), asCALL_CDECL); assert( r >= 0 );

    //fill_ellipse(double x,  double y, double rx, double ry)
    return r;
}




