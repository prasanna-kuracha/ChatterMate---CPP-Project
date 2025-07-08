// Class Method Definitions

// ChatBot.cpp
#include "ChatBot.hpp"
#include "utilities.hpp"

ChatBot::ChatBot() {
    memory["hi"] = "Hello!";
    memory["how are you"] = "I'm just a program, but I'm doing great!";
    memory["what is your name"] = "I am your friendly ChatBot!";
    memory["help"] = "Try saying hi, ask how I am, or ask my name.";

    jokes = {
        "Why do programmers mix up Halloween and Christmas? Because Oct 31 == Dec 25!",
        "What's a computer's favorite snack? Microchips!",
        "Why do programmers prefer dark mode? Because light attracts bugs!"
    };

    srand(time(0));
}

void ChatBot::timeBasedGreeting() {
    auto now = chrono::system_clock::now();
    time_t t_now = chrono::system_clock::to_time_t(now);
    tm* ltm = localtime(&t_now);
    int hour = ltm->tm_hour;

    if (hour < 12) cout << "Good Morning!\n";
    else if (hour < 18) cout << "Good Afternoon!\n";
    else cout << "Good Evening!\n";
}

void ChatBot::askDetails() {
    cout << "What is your name?\n--> ";
    getline(cin >> ws, name);

    cout << "What is your age?\n--> ";
    while (!(cin >> age)) {
        cout << "Please enter a valid number.\n--> ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    if (age == 18) cout << "You are young.\n";
    else if (age == 30) cout << "You are a grown-up.\n";
    else cout << "Nothing to say about your age.\n";
}

void ChatBot::askMorePersonalQuestions() {
    string input;
    cout << "\nNice to meet you, " << name << "! \n";

    cout << "What's your favorite color?\n--> ";
    getline(cin >> ws, input);
    userMemory["favorite color"] = input;

    cout << "What's your favorite city?\n--> ";
    getline(cin >> ws, input);
    userMemory["favorite city"] = input;

    cout << "What's your hobby?\n--> ";
    getline(cin >> ws, input);
    userMemory["hobby"] = input;

    cout << "\nAwesome! I'll remember that your favorite color is " << userMemory["favorite color"]
        << ", you like " << userMemory["favorite city"]
        << ", and your hobby is " << userMemory["hobby"] << ".\n";
}

void ChatBot::chatLoop() {
    string input;
    ofstream log("chatlog.txt", ios::app);

    timeBasedGreeting();
    askDetails();
    log << "User: " << name << ", Age: " << age << endl;

    askMorePersonalQuestions();
    log << "Color: " << userMemory["favorite color"]
        << ", City: " << userMemory["favorite city"]
        << ", Hobby: " << userMemory["hobby"] << endl;

    cout << "\nNow you can start chatting! (Type 'bye' to exit)\n";
    while (true) {
        cout << "--> ";
        getline(cin >> ws, input);

        string rawInput = input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        history.push_back(rawInput);
        log << "User input: " << rawInput << endl;

        if (input == "bye") {
            cout << "Goodbye " << name << "! Have a nice day.\n";
            log << "Session ended.\n\n";
            break;
        }
        else if (input == "joke") {
            string joke = jokes[rand() % jokes.size()];
            cout << joke << endl;
            log << "Bot: " << joke << endl;
        }
        else if (input == "what time is it") {
            string time = getCurrentTime();
            cout << "Current time is: " << time << endl;
            log << "Bot: " << time << endl;
        }
        else if (input == "what date is it") {
            string date = getCurrentDate();
            cout << "Today's date is: " << date << endl;
            log << "Bot: " << date << endl;
        }
        else if (input.find("remember my") != string::npos || input.find("my ") == 0) {
            size_t pos = input.find("is");
            if (pos != string::npos) {
                string key = input.substr(0, pos);
                string value = input.substr(pos + 3);

                size_t my_pos = key.find("my");
                if (my_pos != string::npos)
                    key = key.substr(my_pos + 3);

                key = trim(key);
                value = trim(value);

                userMemory[key] = value;
                cout << "Got it! I'll remember that.\n";
                log << "Bot: Remembered " << key << " = " << value << endl;
            }
        }
        else if (input == "what did i tell you") {
            if (userMemory.size() == 3) {
                cout << "You haven't told me anything yet.\n";
            } else {
                cout << "Here's what I remember:\n";
                for (const auto& kv : userMemory) {
                    string key = kv.first;
                    if (!key.empty()) key[0] = toupper(key[0]);
                    cout << "- Your " << key << " is " << kv.second << ".\n";
                }
            }
        }
        else if (input == "history") {
            cout << "Here's what you typed so far:\n";
            for (const string& cmd : history) {
                cout << "- " << cmd << endl;
            }
        }
        else if (isMathExpression(input)) {
            double result = evaluateExpression(input);
            if (isnan(result)) {
                cout << "Sorry, I couldn't evaluate that.\n";
            } else {
                cout << "Answer: " << result << endl;
            }
        }
        else if (memory.count(input)) {
            cout << memory[input] << endl;
            log << "Bot: " << memory[input] << endl;
        }
        else {
            cout << "I don't understand that. Try: 'help', 'joke', 'what time is it', 'what date is it', 'history', 'remember ...' or 'bye'.\n";
            log << "Bot: Unrecognized input.\n";
        }
    }

    log.close();
}
