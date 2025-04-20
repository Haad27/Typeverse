#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Global variables
string words[10000];
vector<string> easyWords, mediumWords, hardWords;
bool keepRunning = true;

// ====================== PLAYER PROFILE CLASS ======================
class PlayerProfile {
private:
    string username;
    int totalTests;
    int highScore;
    vector<int> pastScores;
    map<string, int> mistakeCount;
    
public:
    PlayerProfile(string name) : username(name), totalTests(0), highScore(0) {}
    
    string getUsername() { return username; }
    
    void updateStats(int score, const string wrongWords[], int wrongCount) {
        totalTests++;
        pastScores.push_back(score);
        if(score > highScore) highScore = score;
        
        for(int i = 0; i < wrongCount; i++) {
            if(!wrongWords[i].empty()) {
                mistakeCount[wrongWords[i]]++;
            }
        }
    }
    
    void showProfile() {
        cout << "\n=== PLAYER PROFILE ===";
        cout << "\nUsername: " << username;
        cout << "\nTests Taken: " << totalTests;
        cout << "\nHigh Score: " << highScore;
        
        if(!pastScores.empty()) {
            cout << "\nLast Scores: ";
            int start = max(0, (int)pastScores.size()-5);
            for(int i = start; i < pastScores.size(); i++) {
                cout << pastScores[i] << " ";
            }
        }
    }
    
    vector<string> getWeakWords(int count) {
        vector<pair<string, int>> sortedMistakes(mistakeCount.begin(), mistakeCount.end());
        sort(sortedMistakes.begin(), sortedMistakes.end(), 
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second;
            });
        
        vector<string> result;
        for(int i = 0; i < min(count, (int)sortedMistakes.size()); i++) {
            result.push_back(sortedMistakes[i].first);
        }
        return result;
    }
};

// ====================== LEADERBOARD CLASS ======================
class Leaderboard {
private:
    map<string, int> topScores;
    
public:
    void addScore(const string& username, int score) {
        if(topScores.find(username) == topScores.end() || score > topScores[username]) {
            topScores[username] = score;
        }
    }
    
    void display() {
        cout << "\n=== LEADERBOARD ===";
        
        vector<pair<string, int>> sortedScores(topScores.begin(), topScores.end());
        sort(sortedScores.begin(), sortedScores.end(), 
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second;
            });
        
        int count = 0;
        for(const auto& entry : sortedScores) {
            cout << "\n" << ++count << ". " << entry.first << ": " << entry.second;
            if(count >= 5) break;
        }
        
        if(sortedScores.empty()) {
            cout << "\nNo scores yet!";
        }
    }
};

// ====================== TYPING TEST CLASS ======================
class TypingTest {
private:
    int correct, wrong;
    string corrected[100];
    string wronged[100];
    int x[100];
    Leaderboard* leaderboard;
    
public:
    TypingTest(Leaderboard* lb) : correct(0), wrong(0), leaderboard(lb) {
        for(int i = 0; i < 100; i++) {
            corrected[i] = "";
            wronged[i] = "";
        }
    }
    
    void loadWords() {
        ifstream myfile("all-english-words.txt");
        string line;
        int i = 0;
        
        if(myfile.is_open()) {
            while(myfile >> line) {
                words[i] = line;
                
                if(line.length() <= 4) easyWords.push_back(line);
                else if(line.length() <= 7) mediumWords.push_back(line);
                else hardWords.push_back(line);
                
                i++;
            }
            myfile.close();
        }
    }
    
    void getCurrentText(int difficulty) {
        srand(time(0));
        vector<string>* wordList = &easyWords;
        
        switch(difficulty) {
            case 1: wordList = &easyWords; break;
            case 2: wordList = &mediumWords; break;
            case 3: wordList = &hardWords; break;
        }
        
        for(int i = 0; i < 100; i++) {
            if(wordList->empty()) {
                x[i] = rand() % 10000;
                cout << words[x[i]] << " ";
            } else {
                x[i] = rand() % wordList->size();
                cout << (*wordList)[x[i]] << " ";
            }
        }
    }
    
    void checkInput(string input, int y) {
        string correctWord;
        
        if(x[y] == -1) {
            // Practice mode word
            correctWord = input; // In practice mode, we just check if they typed it at all
            if(!input.empty()) {
                correct++;
                corrected[y] = input;
            } else {
                wrong++;
                wronged[y] = input;
            }
        } else {
            // Normal test word
            if(x[y] < easyWords.size()) correctWord = easyWords[x[y]];
            else if(x[y] < mediumWords.size()) correctWord = mediumWords[x[y]];
            else if(x[y] < hardWords.size()) correctWord = hardWords[x[y]];
            else correctWord = words[x[y]];
            
            if(input == correctWord) {
                correct++;
                corrected[y] = input;
            } else {
                wrong++;
                wronged[y] = input;
            }
        }
    }
    
    void input() {
        int y = 0;
        string line;
        while(keepRunning && y < 100) {
            cout << "\nType here: ";
            getline(cin >> ws, line);
            string word;
            istringstream iss(line);
            
            while(iss >> word && y < 100 && keepRunning) {
                checkInput(word, y);
                cout << "(You typed: " << word << ")" << endl;
                y++;
            }
        }
    }
    
    void startTest(int duration) {
        for(int i = 0; i <= duration; i++) {
            if(!keepRunning) break;
            cout << "\033[s";
            cout << "\033[15;80H";
            cout << "Time: " << i << "s   " << flush;
            cout << "\033[u";
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        if(keepRunning) {
            cout << "Time is up!\n";
            keepRunning = false;
        }
    }
    
    void runTest(PlayerProfile& player) {
        keepRunning = true;
        correct = 0;
        wrong = 0;
        
        int difficulty;
        cout << "\nSelect difficulty (1-Easy, 2-Medium, 3-Hard): ";
        cin >> difficulty;
        
        getCurrentText(difficulty);
        
        int choice;
        cout << "\n\nSelect test duration (1:15s, 2:30s, 3:60s): ";
        cin >> choice;
        
        int duration = 15;
        switch(choice) {
            case 1: duration = 15; break;
            case 2: duration = 30; break;
            case 3: duration = 60; break;
        }
        
        thread timerThread(&TypingTest::startTest, this, duration);
        thread inputThread(&TypingTest::input, this);
        
        timerThread.join();
        inputThread.join();
        
        int streakBonus = max(0, (correct/5)-1);
        int score = correct + streakBonus - wrong;
        
        cout << "\n=== RESULTS ===";
        cout << "\nCorrect words: " << correct;
        cout << "\nWrong words: " << wrong;
        cout << "\nStreak bonus: +" << streakBonus;
        cout << "\nFinal score: " << score;
        
        player.updateStats(score, wronged, wrong);
        leaderboard->addScore(player.getUsername(), score);
        
        auto weakWords = player.getWeakWords(3);
        if(!weakWords.empty()) {
            cout << "\n\nPractice these words: ";
            for(const auto& word : weakWords) {
                cout << word << " ";
            }
        }
    }
    
    void practiceMode(PlayerProfile& player) {
        auto weakWords = player.getWeakWords(10);
        if(weakWords.empty()) {
            cout << "\nNo words to practice yet! Complete some tests first.";
            return;
        }
        
        cout << "\n=== PRACTICE MODE ===";
        cout << "\nType these words you frequently miss:\n";
        
        for(int i = 0; i < weakWords.size(); i++) {
            x[i] = -1; // Mark as practice word
            cout << weakWords[i] << " ";
        }
        
        correct = 0;
        wrong = 0;
        keepRunning = true;
        
        cout << "\n\nYou have 60 seconds to practice these words:";
        
        thread timerThread(&TypingTest::startTest, this, 60);
        thread inputThread(&TypingTest::input, this);
        
        timerThread.join();
        inputThread.join();
        
        cout << "\nPractice results:";
        cout << "\nCorrect: " << correct;
        cout << "\nWrong: " << wrong;
    }
};

// ====================== MAIN FUNCTION ======================
int main() {
    Leaderboard leaderboard;
    TypingTest test(&leaderboard);
    test.loadWords();
    
    cout << "Welcome to the Typing Test!\n";
    
    string username;
    cout << "Enter your username: ";
    cin >> username;
    PlayerProfile player(username);
    
    int option;
    do {
        cout << "\n\n=== MAIN MENU ===";
        cout << "\n1. Take Typing Test";
        cout << "\n2. Practice Mode";
        cout << "\n3. View Profile";
        cout << "\n4. View Leaderboard";
        cout << "\n5. Exit";
        cout << "\nSelect option: ";
        cin >> option;
        
        switch(option) {
            case 1: 
                test.runTest(player); 
                break;
            case 2: 
                test.practiceMode(player); 
                break;
            case 3: 
                player.showProfile(); 
                break;
            case 4: 
                leaderboard.display(); 
                break;
            case 5: 
                cout << "Goodbye!\n"; 
                break;
            default: 
                cout << "Invalid option!\n";
        }
    } while(option != 5);
    
    return 0;
}