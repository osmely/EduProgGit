//
//  Compiler.hpp
//  NewProject
//
//  Created by Osmely Fernandez on 3/9/16.
//
//

#ifndef Compiler_hpp
#define Compiler_hpp

//#include "agg.h"
#include "Lienzo.h"

#include "angelscript.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <iostream>  // cout
#include <assert.h>  // assert()
#include <string.h>
#include <sys/time.h>
#include <sstream>
#include <stdexcept>


//addons
#include "add_on/scriptstdstring/scriptstdstring.h"
#include "add_on/scripthandle/scripthandle.h"
#include "add_on/weakref/weakref.h"



using namespace std;

class Compiler {


    #define UINT unsigned int
    typedef unsigned int DWORD;
    DWORD timeGetTime()
    {
        timeval time;
        gettimeofday(&time, NULL);
        return time.tv_sec*1000 + time.tv_usec/1000;
    }

    static void MessageCallback(const asSMessageInfo *msg, void *param);
    int configureEngine();


    asIScriptEngine *engine = nullptr;
    asIScriptContext *scriptContext = nullptr;
    asIScriptFunction *mainF;
    asIScriptModule *mod;


public:

    static Compiler* instance;

    Compiler();
    void printConsole(const std::string &msg);
    int build(const std::string &script);
    int run(bool resetGlobals = true);
    void clear();

    std::function<void(const std::string &data)> callback;

};


#endif /* Compiler_hpp */
