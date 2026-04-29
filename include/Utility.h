#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "../include/Product.h"

namespace Utility
{
        /**
            Sleeps\Pauses program for an amount of time
            @param mSec - duration in milliseconds
        */
        void pause(int mSec);

        /**
            Prints a character a repeated number of times, plus new line
            @param c - the character
            @param reps - number of repetitions
        */
        void printChars(char c, int reps);

        /**
            Prints a character with seperators a repeated number of times, plus new line
            @param c - the character
            @param sep - seperating character
            @param reps - number of repetitions
        */
        void printChars(char c, char sep, int reps);

        /**
            Prints a character with seperators a repeated number of times
            @param c - the character
            @param sep - seperating character
            @param reps - number of repetitions
        */
        void printRep(char c, char sep, int reps);

        /**
            Draws a line of arrows across console
        */
        void line();

        /**
            Appends spaces to strings less than 20 chars
            @param str - input string
        */
        void fillString(std::string &str);

        // resizes terminal to fit our console output
        void setupTerminal();
};

#endif // UTILITY_H
