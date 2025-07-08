// Class Declaration (Header)

#ifndef CHATBOT_HPP
#define CHATBOT_HPP

#include <bits/stdc++.h>
#include "utilities.hpp"

using namespace std;

class ChatBot {
private:
    string name;
    int age;
    map<string, string> memory;
    map<string, string> userMemory;
    vector<string> jokes;
    vector<string> history;

public:
    ChatBot();

    void timeBasedGreeting();
    void askDetails();
    void askMorePersonalQuestions();
    void chatLoop();
};

#endif
