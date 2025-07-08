// main.cpp
#include "ChatBot.hpp"

int main() {
    char choice;
    cout << "\t\tWELCOME TO CHATBOX\n\n";
    cout << "To continue, type 'Y'. To exit, type 'N'.\n--> ";
    cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        cout << "Thanks for coming!\n";
        return 0;
    }

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    ChatBot bot;
    bot.chatLoop();

    cout << "\n\t\tPROGRAM ENDED.\n";
    return 0;
}
