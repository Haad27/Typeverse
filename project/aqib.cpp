#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream> 
using namespace std;

int choice;
int correct, wrong;
string corrected[100];
string wronged[100];
bool keepRunning = true;
string testText = "KIA HALL HAI"; 
string words[100];
int totalWords = 0;


void startTest() {
    int maxTime = (choice == 1) ? 15 : (choice == 2) ? 30 : 60;
    for (int i = 0; i <= maxTime; i++) {
        cout << "\033[s";
        cout << "\033[15;80H";
        cout << "Time: " << i << "s   " << flush;
        cout << "\033[u";
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\nTime is up\n";
    keepRunning = false;
    cout << "Press any button to see the results\n";
}


void getCurrentText() {
    istringstream iss(testText);
    string word;
    totalWords = 0;
    while (iss >> word && totalWords < 100) {
        words[totalWords++] = word;
    }

    for (int i = 0; i < totalWords; i++) {
        cout << words[i] << " ";
    }
    cout << endl;
}

void checkInput(string input, int y) {
    if (input == words[y]) {
        correct++;
        corrected[y] = input;
    } else {
        wrong++;
        wronged[y] = input;
    }
}

void input() {
    int y = 0;
    string line;
    while (keepRunning && y < totalWords) {
        cout << "\nType here: ";
        getline(cin >> ws, line);
        istringstream iss(line);
        string word;
        while (iss >> word && y < totalWords && keepRunning) {
            checkInput(word, y);
            y++;
        }
    }

    if (!keepRunning && !line.empty()) {
        istringstream iss(line);
        string word;
        while (iss >> word && y < totalWords) {
            checkInput(word, y);
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
    cout << "\nChoose time: 1: 15 sec, 2: 30 sec, 3: 60 sec: ";
    cin >> choice;

    thread t2(startTest);
    thread t3(input);

    t2.join();
    t3.join();

    cout << "Correct words: " << correct << endl;
    cout << "Wrong words: " << wrong << endl;

    cout << "You typed correct:\n";
    for (int i = 0; i < 100; i++) {
        if (!corrected[i].empty()) cout << corrected[i] << " " << endl;
    }

    cout << "You typed wrong:\n";
    for (int i = 0; i < 100; i++) {
        if (!wronged[i].empty()) cout << wronged[i] << " " << endl;
    }
}

class user {
public:
    int userCorrect;
    int userWrong;
    user(int c = 0, int w = 0) : userCorrect(c), userWrong(w) {}
    void display() {
        cout << "User correct words: " << userCorrect << endl;
        cout << "User wrong words: " << userWrong << endl;
        cout << "User score: " << userCorrect - userWrong << endl;
    }
};

int main() {
    int number, highest = 0, lowest = 9999;

    cout << "Welcome to the Typing Test!" << endl;
    cout << "\nHow many users or players: ";
    cin >> number;

    user* users = new user[number];

    for (int i = 0; i < number; i++) {
        cout << "\nUser " << i + 1 << " is playing" << endl;
        runTest();
        users[i] = user(correct, wrong);

        if (users[i].userCorrect > highest) highest = users[i].userCorrect;
        if (users[i].userCorrect < lowest) lowest = users[i].userCorrect;
    }

    cout << "\nFinal Results:\n";
    for (int i = 0; i < number; i++) {
        cout << "User " << i + 1 << " scores:\n";
        users[i].display();
    }

    cout << "Highest score: " << highest << endl;
    cout << "Lowest score: " << lowest << endl;

    for (int i = 0; i < number; i++) {
        if (users[i].userCorrect == highest)
            cout << "\nUser " << i + 1 << " is the winner!" << endl;
        if (users[i].userCorrect == lowest)
            cout << "User " << i + 1 << " is the loser." << endl;
    }

    delete[] users;
   return 0;
}
