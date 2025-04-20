#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream> 
using namespace std;

// Global variables for test state
int choice;
int correct, wrong;
string corrected[100];
string wronged[100];
bool keepRunning = true;
int x[100] = {};
string words[10000];

// Timer functions (no class needed)
void startTest() {
    switch (choice) {
        case 1:
            for (int i = 0; i <= 15; i++) {
                cout << "\033[s";
                cout << "\033[35;80H";
                cout << "Time: " << i << "s   " << flush;
                cout << "\033[u";
                _sleep(1000);
            }
            break;
        case 2:
            for (int i = 0; i <= 30; i++) {
                cout << "\033[s";
                cout << "\033[15;80H";
                cout << "Time: " << i << "s   " << flush;
                cout << "\033[u";
                _sleep(1000);
            }
            break;
        case 3:
            for (int i = 0; i <= 60; i++) {
                cout << "\033[s";
                cout << "\033[15;80H";
                cout << "Time: " << i << "s   " << flush;
                cout << "\033[u";
                _sleep(1000);
            }
            break;
    }
    cout << "time is up \n";
    keepRunning = false;
    cout << "press any button to see the results \n";
}

// Text functions (no class needed)
void getCurrentText() {
    srand(time(0));
    ifstream myfile;
    myfile.open("all-english-words.txt");
    string line;
    if (myfile.is_open()) {
        int i = 0;
        while (myfile >> line) {
            words[i] = line;
            i++;
        }
        myfile.close();
        for (int i = 0; i < 100; i++) {
            x[i] = rand() % 10000;
            cout << words[x[i]] << " ";
        }
    }
}

// Accuracy checking functions
void checkInput(string input, int y) {
    if (input == words[x[y]]) {
        correct++;
        corrected[y] = input;
    }
    else if (input != words[x[y]]) {
        wrong++;
        wronged[y] = input;
    }
}

void input() {
    int y = 0;
    string line;
    while (keepRunning) {
        cout << "\nType here: ";
        getline(cin >> ws, line);
        string word;
        istringstream iss(line);
        while (iss >> word && y < 100 && keepRunning == true) {
            checkInput(word, y);
            cout << "(You typed: " << word << ")" << endl;
            y++;
        }
    }

    if (!keepRunning && !line.empty()) {
        string word;
        istringstream iss(line);
        while (iss >> word && y < 100) {
            checkInput(word, y);
            cout << "(You typed: " << word << ")" << endl;
            y++;
        }
    }
}

void resetTest() {
    keepRunning = true;
    correct = 0;
    wrong = 0;
    for (int i = 0; i < 100; i++) {
        corrected[i] = "";
        wronged[i] = "";
    }
}

void runTest() {
    resetTest();
    getCurrentText();
    cout << "\n\ndo you want to play for 1 : 15 sec or 2 : 30 sec or 3 : 60 sec" << endl;
    cin >> choice;
    
    thread t2(startTest);
    thread t3(input);

    t2.join();
    t3.join();
    
    cout << "correct words : " << correct << endl;
    cout << "wrong words : " << wrong << endl;

    cout << "You typed correct :\n";
    for (int i = 0; i < 100; i++) {
        if (!corrected[i].empty()) {
            cout << corrected[i] << " "<< endl;
        }
    }
    
    cout << "You typed wrong :\n";
    for (int i = 0; i < 100; i++) {
        if (!wronged[i].empty()) {  
            cout << wronged[i] << " "<< endl;
        }
    }
}

// Keep user as class since it's good OOP
class user {
public:
    int userCorrect;
    int userWrong;

    user(int c = 0, int w = 0)   {
        userCorrect = c;
        userWrong = w;
    }
    // Removed redundant default constructor
    void display() {
        cout << "User correct words: " << userCorrect ;
        cout << "User wrong words: " << userWrong ;
        cout << "\n User score: " << userCorrect - userWrong;
    }
};

int main() {
    int number, highest = 0, lowest = 9999;
    
    cout << "Welcome to the Typing Test!" << endl;
    cout << "\nHow many users or players competing in typing speed\n";
    cin >> number;
    
    user* users = new user[number];
    
    for (int i = 0; i < number; i++) {
        cout << "\n\nUser " << i + 1 << " is playing" << endl;
        runTest();
        users[i] = user(correct, wrong);
        
        if (users[i].userCorrect > highest) {
            highest = users[i].userCorrect;
        }
        if (users[i].userCorrect < lowest) {
            lowest = users[i].userCorrect;
        }
    }

    cout << "\nFinal Results:" << endl;
    for (int i = 0; i < number; i++) {
        cout << "User " << i + 1 << " scores:" << endl;
        users[i].display();
        cout << endl;
    }
      
    cout << "Highest score: " << highest << endl;
    cout << "Lowest score: " << lowest << endl;

    for (int i = 0; i < number; i++) {
        if (users[i].userCorrect == highest) {
            cout << "\n\nUser " << i + 1 << " Is the winner" << endl;
        }
        if (users[i].userCorrect == lowest) {
            cout << "\n\nUser " << i + 1 << " Is the loser" << endl;
        }
    } 
    delete[] users;
    return 0;
}