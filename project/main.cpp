#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream> // Required for std::istringstream
using namespace std;
class main
{
protected:
    int choice;
    int correct, wrong;

    string corrected[100];
    string wronged[100];
    bool keepRunning = true; // Flag to control input
    int x[100] = {};
    string words[10000];
};

// aqib
class text : protected main
{
protected:
    void getCurrentText()
    {
        srand(time(0));
        ifstream myfile;
        myfile.open("all-english-words.txt");
        string line;
        if (myfile.is_open())
        {
            int i = 0;
            while (myfile >> line)
            {
                words[i] = line;
                i++;
            }
            myfile.close();
            for (int i = 0; i < 100; i++)
            {
                x[i] = rand() % 10000;
                cout << words[x[i]] << " "; // Only use up to number of words read
            }
        }
    }
};

// ahsan
class time : protected text
{
protected:
    void startTest()
    {
        int arr[60];
        for (int i = 0; i < 60; i++)
        {
            arr[i] = i;
        }

        switch (choice)
        {
        case 1:
            for (int i = 0; i < 16; i++)
            {
                _sleep(1000);
            }
            cout << "time is up \n";
            keepRunning = false;
            cout << "press any button to seee the results \n";

            break;
        case 2:
            for (int i = 0; i < 31; i++)
            {
                _sleep(1000);
                break;
            }

            cout << "time is up \n";
            keepRunning = false;
            cout << "press any button to seee the results \n";
            break;
        case 3:
            for (int i = 0; i < 61; i++)
            {
                cout << "Time: " << i << "s " << flush; // Overwrites the time on the same line
                _sleep(1000);
            }
            cout << "time is up \n";
            keepRunning = false;
            cout << "press any button to seee the results \n";
        default:
            break;
        }
    }
};
// aqib
class accuracy_checker : protected time
{
protected:
    void checkInput(string input, int y)
    {
        if (input == words[x[y]])
        {
            correct++;
            corrected[y] = input;
        }
        else if (input != words[x[y]])
        {
            wrong++;
            wronged[y] = input;
        }
    }

    void input()
    {
        int y = 0;
        string line;
        while (keepRunning)
        {
            cout << "\nType here: ";
            getline(cin >> ws, line); // reads a whole line, and clears leading whitespace

            // Split line into words
            string word;
            istringstream iss(line);
            while (iss >> word && y < 100 && keepRunning == true)
            {
                checkInput(word, y);
                cout << "(You typed: " << word << ")" << endl;
                y++;
            }
        }

        // If timer ended but we are still inside last line, check it once more
        if (!keepRunning && !line.empty())
        {
            string word;
            istringstream iss(line);
            while (iss >> word && y < 100)
            {
                checkInput(word, y);
                cout << "(You typed: " << word << ")" << endl;
                y++;
            }
        }
    }
};
class child : public accuracy_checker
{
public:
    int getCorrect() const { return correct; }
    int getWrong() const { return wrong; }
   

    void resetTest()
    { // New: added reset function
        keepRunning = true;
        correct = 0;
        wrong = 0;
        for (int i = 0; i < 100; i++)
        {
            corrected[i] = "";
            wronged[i] = "";
        }
    }
    void getCurrentText()
    {
        resetTest(); // New: reset before each test

        text::getCurrentText(); // Call the function from the base class
        cout << "\n\ndo you want to play  for 1 : 15 sec or 2 : 30 sec or 3 : 60 sec" << endl;
        cin >> choice;
        thread t2([this]()
                  { this->startTest(); });
        thread t3([this]()
                  { this->input(); });

        t2.join(); // wait for timer to finish
        t3.join(); // wait for timer to finish
        cout << "correct words : " << correct << endl;
        cout << "wrong words : " << wrong << endl;

        cout << "You typed correct :\n";
        for (int i = 0; i < 100; i++)
        {
            if (!corrected[i].empty()){
                cout << corrected[i] << " "<< endl;

            }
        }
        
        cout << "You typed wrong :\n";
        for (int i = 0; i < 100; i++)
        {
            if (!wronged[i].empty())
            {  
                  cout << wronged[i] << " "<< endl;
            }
        }
    }
};
class user
{ // Changed: simplified user class
public:
    int userCorrect;
    int userWrong;

    user(int c, int w)
    {
        userCorrect = c;
        userWrong = w;
    }
    user (){

    }

    void display()
    {
        cout << "User correct words: " << userCorrect << endl;
        cout << "User wrong words: " << userWrong << endl;
    }
};

int main()
 {
    child test;
    int number,highest =0 , lowest=9999;
    
    cout << "Welcome to the Typing Test!" << endl;
    cout << "\nHow many users or players competing in typing speed\n";
    cin >> number;
    
    // Create an array to store all users' results
    user* users = new user[number];
    
    for (int i = 0; i < number; i++) {
        cout << "\n\nUser " << i + 1 << " is playing" << endl;
        users[i] = user(test.getCorrect(), test.getWrong());
        if (users[i].userCorrect > highest)
        {
            users[i].userCorrect = highest;
        }
        else if (users[i].userCorrect < lowest)
        {
            users[i].userCorrect = lowest;
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
        if (users[i].userCorrect == highest)
        {
            cout << "\n\nUser " << i + 1 << " Is the winner" << endl;
        }
        else if (users[i].userCorrect == lowest)
        {
            cout << "\n\nUser " << i + 1 << " Is is the loser" << endl;
        }
    } 
    delete[] users;
    return 0;
}

   