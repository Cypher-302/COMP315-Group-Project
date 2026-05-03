#include "../include/Utility.h"
#include "../include/Product.h"

#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>

// this header is only included if we are on Windows
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

namespace Utility
{
    void pause(int mSec){
        std::this_thread::sleep_for(std::chrono::milliseconds(mSec));
    }

    void printChars(char c, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c;
        }
        std::cout<<"\n";
    }

    void printChars(char c, char sep, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c<< sep;
        }
        std::cout<< "\n";
    }

    void printRep(char c, char sep, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c<< sep;
        }
    }

    void line(){
        std::cout<<"\n";
        printChars('�','�',65); // from reps
        std::cout<<"\n";
    }

    void fillString(std::string &str){
        int spaces = 20 - str.length();
        for(int i=spaces; i > 0; i--){
            str +=" ";
        }
    }

    void setupTerminal()
    {
    #ifdef _WIN32
        // this code ONLY exists for the compiler if the OS is Windows

        // gets a handle to stdout
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        // 32 bit unsigned int to store current console settings
        DWORD dwMode = 0;

        // copies current console settings to dwMode
        if (GetConsoleMode(hOut, &dwMode)) {

            // bitwise OR (|=) to add permission to process ANSI escape sequences
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

            // set current console settings to the one we modified
            SetConsoleMode(hOut, dwMode);
        }

        // resize command
        std::cout << "\x1b[8;30;136t";
    #else
        // this code runs on Linux, macOS, etc.
        std::cout << "Non-Windows system detected. Using standard resize." << std::endl;
        std::cout << "\e[8;30;136t";
    #endif
    }
}

