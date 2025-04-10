#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

int choice;
bool keepRunning = true; // Flag to control input
int x[100] = {};
string words[10000];
int correct, wrong;

void generating_words()
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
void time_stamp()
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
            cout << "Time: " << i << "s " << flush; // Overwrites the time on the same line
            _sleep(1000);
        }
        cout << "time is up \n";
        keepRunning = false;

        break;
    case 2:
    for (int i = 0; i < 16; i++)
    {
        cout << "\nTime: " << i << "s" << endl;
        _sleep(1000);
    }

        cout << "time is up \n";
        keepRunning = false;
        break;
    case 3:
        for (int i = 0; i < 61; i++)
        {
            cout << "Time: " << i << "s " << flush; // Overwrites the time on the same line
            _sleep(1000);
        }
        cout << "time is up \n";
        keepRunning = false;
    default:
        break;
    }
}
void checker(string input , int y)
{
    if (input == words[x[y]])
    {
        correct++;
    }
    else
    {
        wrong++;
    }
}

void input()
{
    int y = 0 ;
    string inputs;
    while (keepRunning) // Allow input while timer is running
    {
        cout << "\nType here: ";
        cin >> inputs;
        checker(inputs, y);
        cout << "(You typed: " << inputs << ")" << endl;
        y++;
    }
}
int main()
{
    generating_words();
    cout << "do you want to play  for 1 : 15 sec or 2 : 30 sec or 3 : 60 sec" << endl;
    cin >> choice;

    thread t2(time_stamp);
    thread t3(input);

    t2.join(); // wait for timer to finish
    t3.join(); // wait for timer to finish
    cout << "correct words : " << correct << endl;
    cout << "wrong words : " << wrong << endl;

    return 0;
}
