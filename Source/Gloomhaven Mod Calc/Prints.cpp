#include "Prints.h"
#include "Core.h"
#include <iostream>

void printCommands() {
    std::cout << "Commands:" CNL
        "commands: show commands again" CNL
        "types: show types again" CNL
        "average: calculate the average result with neutral advantage" CNL
        "average [advantage]: calculate the average result." CNL
        "                     [advantage] refers to whether the calculation should use advantage, neutral or disadvantage" CNL
        "add [card code]: add a card using [card code]" CNL
        "remove [card code]: add a card using [card code]" CNL
        "add [card code] [integer]: add a card [integer] times using [card code]" CNL
        "remove [card code] [integer]: remove a card [integer] times using [card code]" CNL
        "deck: show all cards currently in deck" CNL
        "clear: removes all cards from deck" CNL
        "default: set deck to the default 20 card deck" CNL
        "save [string]: save the current deck to a text file, it will be placed in the Saves folder" CNL
        "load [string]: load a save from the Saves folder\n";
}

void printTypes() {
    std::cout << "Types:" CNL
        "[advantage]: can be either adv, neu or dis. Used to specify advantage, neutral or disadvantage." CNL
        "[integer]: an integer" CNL
        "[string]: a string of characters" CNL
        "[card code]: a combination of letters and a number used to refer to cards." CNL
        "                The number is the damage of the card and the letters are the first letter in another property," CNL
        "                such as rolling, stun, and so on. Rolling uses r, stun uses s, for example\n";
}