#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

// Abstract base class
class Test {
public:
    virtual void displayResults() = 0; // Pure virtual function
    virtual ~Test() {}
};

int choice;
int correct, wrong;
string corrected[100];
string wronged[100];
bool keepRunning = true;
string words[100];
int totalWords = 0;
double wpm = 0.0; // Added WPM variable

string paragraph() {
    string paragraph[] = {
        "Critical thinking helps analyze information carefully. It allows us to evaluate evidence and draw conclusions. This skill is vital in academics and professional life.",
        "Climate change is a major global challenge. Human activities like burning fossil fuels are driving it. We need immediate action to address rising temperatures.",
        "Communication evolved from cave paintings to smartphones. Each technology changed how we interact. Today we face challenges like misinformation online.",
        "Education empowers people with knowledge and skills. It supports personal growth and societal development. Quality education should be accessible to all.",
        "Habits are automatic behaviors we repeat daily. Understanding them helps build good routines. Small consistent changes lead to lasting improvement.",
        "Technology shapes how we work and communicate. It offers benefits but raises privacy concerns. We must use it responsibly for society's benefit."
    };

    srand(time(0));
    int randomIndex = rand() % 6;
    return paragraph[randomIndex];
}

string testText = paragraph();

// Derived class implementing Test
class TypingTest : public Test {
public:
    void displayResults() override {
        cout << "Correct words: " << correct << endl;
        cout << "Wrong words: " << wrong << endl;
        cout << "Words Per Minute (WPM): " << wpm << endl; // Added WPM display

        cout << "You typed correct:\n";
        for (int i = 0; i < 100; i++) {
            if (!corrected[i].empty())
                cout << corrected[i] << " " << endl;
        }

        cout << "You typed wrong:\n";
        for (int i = 0; i < 100; i++) {
            if (!wronged[i].empty())
                cout << wronged[i] << " " << endl;
        }
    }
};

void startTest() {
    int maxTime = (choice == 1) ? 15 : (choice == 2) ? 30 : 60;
    for (int i = 0; i <= maxTime; i++) {
        cout << "\033[s";
        cout << "\033[16;80H";
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
    wpm = 0.0; // Reset WPM
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

    auto startTime = chrono::steady_clock::now(); // Added for WPM calculation
    thread t2(startTest);
    thread t3(input);

    t2.join();
    t3.join();

    // Calculate WPM
    auto endTime = chrono::steady_clock::now();
    double elapsedTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
    wpm = (correct / (elapsedTime / 60.0)); // WPM formula: (correct characters / 5) / (minutes)

    // Using polymorphism
    Test* test = new TypingTest();
    test->displayResults();
    delete test;
}

class Score {
public:
    int userCorrect;
    int userWrong;
    int userScore;

    Score(int c = 0, int w = 0) : userCorrect(c), userWrong(w), userScore(c - w) {}

    virtual void display() {
        cout << "User correct words: " << userCorrect << endl;
        cout << "User wrong words: " << userWrong << endl;
    }
    
    virtual ~Score() {}
};

class Profile {
public:
    string name;
    Score* userScoreObj; // Polymorphism through pointer

    Profile(string name, Score* s) : name(name), userScoreObj(s) {}

    virtual void display() {
        cout << " username : " << name << endl;
        cout << "the score of " << name << " is == " << userScoreObj->userScore << endl;
    }
    
    virtual ~Profile() {
        delete userScoreObj;
    }
};

class Leaderboard : public Profile {
public:
    Leaderboard(string name, Score* s) : Profile(name, s) {}

    void display() override {
        cout << "                    " << name << "  ";
        cout << "      ::              " << userScoreObj->userScore << endl;
    }
};

int main() {
    int number, highest = 0, lowest = 9999;
    string name;
    cout << "Welcome to the Typing Test!" << endl;
    cout << "\nHow many users or players: ";
    cin >> number;

    Profile** profiles = new Profile*[number];

    for (int i = 0; i < number; i++) {
        cout << "\nUser " << i + 1 << " is playing" << endl;
        cout << "Enter your name: ";
        cin >> name;
        runTest();
        Score* score = new Score(correct, wrong);

        if (score->userCorrect > highest)
            highest = score->userCorrect;
        if (score->userCorrect < lowest)
            lowest = score->userCorrect;

        profiles[i] = new Profile(name, score);
    }

    cout << "\n\n\n\nFinal Results:\n";
    for (int i = 0; i < number; i++) {
        cout << endl;
        profiles[i]->userScoreObj->display();
        profiles[i]->display();
    }

    cout << "Highest score: " << highest << endl;
    cout << "Lowest score: " << lowest << endl;

    for (int i = 0; i < number; i++) {
        if (profiles[i]->userScoreObj->userCorrect == highest)
            cout << "\nUser " << i + 1 << " is the winner!" << endl;
        if (profiles[i]->userScoreObj->userCorrect == lowest)
            cout << "User " << i + 1 << " is the loser." << endl;
    }
    string enter;
    cout << "Press enter to see leaderboards: ";
    cin >> enter;

    // Sort profiles based on score
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number - 1; j++) {
            if (profiles[j]->userScoreObj->userScore < profiles[j + 1]->userScoreObj->userScore) {
                swap(profiles[j], profiles[j + 1]);
            }
        }
    }

    // Display leaderboard using polymorphism
    for (int i = 0; i < number; i++) {
        Leaderboard* lb = new Leaderboard(profiles[i]->name, 
                                        new Score(profiles[i]->userScoreObj->userCorrect, 
                                                profiles[i]->userScoreObj->userWrong));
        cout << i + 1 << " ";
        lb->display();
        delete lb;
    }

    // Cleanup
    for (int i = 0; i < number; i++) {
        delete profiles[i];
    }
    delete[] profiles;

}
