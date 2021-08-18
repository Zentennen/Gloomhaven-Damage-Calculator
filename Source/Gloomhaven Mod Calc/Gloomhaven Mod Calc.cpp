#pragma once
#include "Card.h"
#include "Effect.h"
#include "Prints.h"
#include "Deck.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>

#define now std::chrono::steady_clock::now()

void save(const std::string& name, const Deck& deck) {
    std::ofstream stream(("Saves/" + name + ".txt").c_str());
    if (!stream.is_open()) {
        std::cout << "ERR: Cannot open file to write save\n";
        return;
    }
    FOR(deck.size()) {
        stream << deck[i].toString() << "\n";
    }
    stream.close();
}

void load(const std::string& name, Deck& deck) {
    std::ifstream stream(("Saves/" + name + ".txt").c_str());
    if (!stream.is_open()) {
        std::cout << "Could not open save file\n";
        return;
    }
    deck.clear();
    std::string line;
    while (std::getline(stream, line)) {
        deck.add(Card(line));
    }
}

bool processInput(const std::string& input, Deck& deck) {
    auto lines = separateByToken(input, ' ');
    if (input.substr(0, 5) == "save ") {
        save(input.substr(5), deck);
    }
    else if (input.substr(0, 5) == "load ") {
        load(input.substr(5), deck);
    }
    else if (lines[0] == "quit") return false;
    else if (lines[0] == "commands") printCommands();
    else if (lines[0] == "types") printTypes();
    else if (lines[0] == "deck") deck.print();
    else if (lines[0] == "clear") deck.clear();
    else if (lines[0] == "default") deck.setToDefault();
    else if (lines[0] == "average") {
        if (lines.size() == 1) deck.average(Advantage::Neutral);
        else if (lines[1] == "adv") deck.average(Advantage::Advantage);
        else if (lines[1] == "neu") deck.average(Advantage::Neutral);
        else if (lines[1] == "dis") deck.average(Advantage::Disadvantage);
        else std::cout << "average must specify an [advantage]\n";
    }
    else if (lines[0] == "add") {
        if (lines.size() == 1) std::cout << "add must specify a [card code]\n";
        else {
            if (lines.size() > 2) {
                if (isAnInteger(lines[2])) {
                    unsigned int s = std::stoi(lines[2]);
                    deck.add(Card(lines[1]), s);
                }
                else if (isAnInteger(lines[2].substr(1))) {
                    if (lines[2][0] == 'x') {
                        unsigned int s = std::stoi(lines[2].substr(1));
                        deck.add(Card(lines[1]), s);
                    }
                    else {
                        std::cout << "[integer] must be an integer\n";
                    }
                }
                else {
                    std::cout << "[integer] must be an integer\n";
                }
            }
            else deck.add(Card(lines[1]));
        }
    }
    else if (lines[0] == "remove") {
        if (lines.size() == 1) std::cout << "remove must specify a [card code]\n";
        else {
            if (lines.size() > 2) {
                if (isAnInteger(lines[2])) {
                    unsigned int s = std::stoi(lines[2]);
                    deck.remove(Card(lines[1]), s);
                }
                else {
                    std::cout << "[integer] must be an integer\n";
                }
            }
            else {
                deck.remove(Card(lines[1]));
            }
        }
    }
    else std::cout << "Could not process command\n";
    NL;
    return true;
}

int main()
{
    Deck deck;
    deck.setToDefault();
    //std::cout << "Gloomhaven Battle Modifier Deck Calculator"; NN;
    printCommands(); NL;
    printTypes(); NL;
    std::cout << "Examples :" CNL
        "average dis: calculate the average result using disadvantage" CNL
        "add rs 3: add 3 rolling stun cards\n\n";
    bool run = true;
    while (run) {
        std::cout << "Enter a command"; NL;
        std::string input = "";
        std::getline(std::cin, input);
        auto begin = now;
        std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return std::tolower(c); });
        run = processInput(input, deck); // note: input is not case-sensitive
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
        double time = static_cast<double>(ms.count());
        if (ms.count() > 2000) {
            std::cout << "It took " << time / 1000.0 << " seconds to process the command\n";
        }
    }
}
