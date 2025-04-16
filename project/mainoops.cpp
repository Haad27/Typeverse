#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

class mainBase
{
protected:
    int choice;
    string corrected[100];
    string wronged[100];
    bool keepRunning = true;
    int x[100] = {};
    string words[10000];
    int correct = 0, wrong = 0;
    int wordCount = 0;
};

// Load and display random words
class text : protected mainBase
{
protected:
    void generateWords()
    {
        srand(time(0));
        ifstream myfile("all-english-words.txt");
        string line;
        if (myfile.is_open())
        {
            int i = 0;
            while (myfile >> line && i < 10000)
            {
                words[i] = line;
                i++;
            }
            wordCount = i;
            myfile.close();

            cout << "\n\nTyping words:\n";
            for (int i = 0; i < 100; i++)
            {
                x[i] = rand() % wordCount;
                cout << words[x[i]] << " ";
            }
            cout << "\n\n";
        }
        else
        {
            cout << "Error: Could not open word file.\n";
        }
    }
};

// Handles timing
class timeManager : protected text
{
protected:
    void startTest()
    {
        switch (choice)
        {
        case 1:
            for (int i = 0; i < 15; i++)
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            break;
        case 2:
            for (int i = 0; i < 30; i++)
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            break;
        case 3:
            for (int i = 0; i < 60; i++)
            {
                cout << "Time: " << i + 1 << "s\r" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            break;
        default:
            cout << "Invalid choice.\n";
            return;
        }
        keepRunning = false;
        cout << "\n\nTime is up!\n";
    }
};

// Checks typing accuracy
class accuracy_checker : protected timeManager
{
protected:
    void checkInput(const string &input, int y)
    {
        if (input == words[x[y]])
        {
            correct++;
            corrected[y] = input;
        }
        else
        {
            wrong++;
            wronged[y] = input;
        }
    }

    void input()
    {
        int y = 0;
        string line;
        while (keepRunning && y < 100)
        {
            cout << "\nType here: ";
            getline(cin >> ws, line);

            istringstream iss(line);
            string word;
            while (iss >> word && y < 100 && keepRunning)
            {
                checkInput(word, y);
                y++;
            }
        }

        // Final check if time ended mid-line
        if (!line.empty() && y < 100)
        {
            istringstream iss(line);
            string word;
            while (iss >> word && y < 100)
            {
                checkInput(word, y);
                y++;
            }
        }
    }
};

// Entry class
class child : public accuracy_checker
{
public:
    void runTypingTest()
    {
        generateWords();

        cout << "Choose duration:\n1 - 15 sec\n2 - 30 sec\n3 - 60 sec\nYour choice: ";
        cin >> choice;

        thread timerThread(&child::startTest, this);
        thread inputThread(&child::input, this);

        timerThread.join();
        inputThread.join();

        cout << "\n\nTyping Test Finished!\n";
        cout << "Correct words: " << correct << endl;
        cout << "Wrong words: " << wrong << endl;
        cout << "Wrong inputs:\n";

        for (int i = 0; i < 100; i++)
        {
            if (!wronged[i].empty())
                cout << wronged[i] << " ";
        }
        cout << "\n";
    }
};

int main()
{
    child start;
    start.runTypingTest();

    return 0;
}
