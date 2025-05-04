#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

int choice = 0;
int correct, wrong;
string corrected[100];
string wronged[100];
bool keepRunning = true;
string words[100];
int totalWords = 0;
double wpm;
bool flag = false;
bool playagain = false;

// Declare isintvalid, isstringvalid, and repeat as global variables
bool isintvalid;
bool isstringvalid;
bool repeat;

int number;

void intCheck()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">>> Please Enter valid input <<<" << endl;
        isintvalid = false;
    }
    else
    {
        isintvalid = true;
    }
}
void stringcheck(string &value)
{
    bool temp;
    isstringvalid = true;
    // Check if string is empty

    if (value.empty())
    {
        isstringvalid = false;
        temp = false;
    }

    // Check each character
    for (char x : value)
    {
        if (isdigit(x))
        {
            isstringvalid = false;
            temp = false;
        }
        else
        {
            temp = true;
            repeat = true;
        }
    }
    if (temp == false)
    {
        cout << "Enter a string without numbers" << endl;
    }
}
void isintvalidbool()
{
    if (isintvalid == false)
    {
        repeat = true;
    }
}

string paragraph()
{
    string paragraph[] = {
        "Critical thinking is a vital skill in todays information rich world With countless sources offering varying perspectives individuals must be equipped to assess information carefully and rationally Critical thinking allows a person to go beyond face value analyzing evidence identifying biases and drawing sound conclusions In academic settings students use critical thinking to evaluate research structure arguments and solve complex problems In professional environments it supports decision making improves communication and enhances problem solving Developing this skill requires patience and practice often beginning with asking thoughtful questions and avoiding hasty judgments A critical thinker remains open minded ready to entertain different viewpoints without immediately accepting or rejecting them They seek clarity precision and relevance in their thinking For example when presented with a claim on social media a critical thinker investigates the credibility of the source checks for supporting data and considers alternate explanations before forming an opinion Furthermore in fields like science law and engineering critical thinking is indispensable for analyzing results crafting arguments and designing systems Without it reasoning may fall victim to emotional appeals groupthink or misinformation Educational institutions increasingly recognize its importance integrating critical thinking into curricula through problem based learning debate and reflective writing As artificial intelligence grows more powerful distinguishing between human and machine reasoning may depend on our ability to apply nuanced contextual critical thinking In sum this skill is not only academic it is essential for personal growth civic responsibility and professional success in a complex interconnected world",

        "Climate change stands as one of the most pressing global challenges of our time Driven largely by human activities especially the burning of fossil fuels deforestation and industrial processes the earths climate system has undergone unprecedented changes Rising global temperatures melting polar ice caps and increased frequency of extreme weather events are just a few of the observable impacts Sea levels continue to rise threatening coastal communities and ecosystems At the heart of this crisis is carbon dioxide CO2 a greenhouse gas that traps heat in the atmosphere Although CO2 occurs naturally human activity has increased its concentration far beyond historical levels Addressing climate change requires immediate and sustained action at all levels from international agreements like the Paris Accord to individual choices such as using energy efficient appliances and reducing waste Governments must invest in renewable energy support sustainable agriculture and enforce environmental regulations Businesses play a role too through green innovation and corporate sustainability Education is key citizens need to understand how their actions impact the environment Behavioral shifts such as favoring public transportation or eating less meat can collectively reduce carbon footprints Moreover climate justice demands that wealthier nations support vulnerable countries that suffer disproportionately from climate impacts While the challenge is enormous so is the opportunity A greener future is possible but it requires collaboration innovation and a shared commitment to protect our planet for future generations",

        "Communication has been central to human civilization for thousands of years From prehistoric cave paintings to modern day smartphones humans have constantly developed new ways to share ideas stories and emotions In ancient times early humans used drawings symbols and gestures to convey meaning With the advent of spoken language people were able to pass down history culture and wisdom orally across generations Later writing systems emerged in Mesopotamia and Egypt allowing information to be preserved and transmitted across time and distance The invention of the printing press in the 15th century revolutionized communication by making books and pamphlets more accessible igniting a surge in literacy and learning In the 19th and 20th centuries technologies like the telegraph telephone radio and television enabled instant communication across vast distances The internet introduced in the late 20th century further transformed human interaction by connecting billions of people worldwide Today we live in an age of rapid communication through social media email video conferencing and more Each technological leap has reshaped societies economies and personal relationships Yet with increased speed and reach come challenges such as misinformation digital overload and the erosion of face to face interaction As we continue to innovate it is essential to reflect on how communication shapes our understanding of the world and how we can use it responsibly and effectively",

        "Education is a powerful force that shapes individuals societies and nations It empowers people with the knowledge skills and values necessary to navigate the world and contribute meaningfully to their communities At the personal level education fosters critical thinking self confidence and creativity At the societal level it supports economic development social cohesion and informed citizenship Formal education begins in schools but extends to colleges universities and lifelong learning opportunities Informal education also plays a role through family media and social experiences In todays rapidly changing world education must evolve to meet new demands This includes integrating digital literacy promoting environmental awareness and nurturing emotional intelligence Teachers play a critical role not only in delivering content but also in inspiring curiosity guiding behavior and modeling lifelong learning Access to quality education remains a global challenge particularly in low income regions where poverty conflict and inequality limit opportunities Bridging these gaps requires investment policy reform and international cooperation Education also has a moral dimension it should promote empathy respect and global responsibility As we look toward the future it is clear that education is not just preparation for life it is life itself Societies that invest in education are more resilient innovative and just",

        "Habits are automatic behaviors that shape much of our daily lives From brushing teeth to checking our phones many actions are performed with little conscious thought Psychologists define habits as learned routines triggered by specific cues and reinforced by rewards Understanding how habits form can help us build better routines and break unhelpful ones The habit loop cue routine reward explains how behaviors become ingrained For example seeing your running shoes cue may prompt you to go jogging routine followed by a sense of accomplishment reward Repeating this loop strengthens the habit Changing habits often involves replacing the routine while keeping the same cue and reward Motivation environment and consistency all influence habit development Positive habits like regular exercise healthy eating or reading can improve physical and mental wellbeing Negative habits like procrastination overeating or smoking can be difficult to break but are not impossible Small consistent changes are often more effective than big sudden ones Setting clear goals tracking progress and using reminders or accountability partners can support habit change Neuroscience shows that habits are wired into the brains basal ganglia making them efficient but also resistant to change However with awareness and effort habits can be reshaped leading to lasting personal growth and self improvement",

        "Technology has become a fundamental part of our lives shaping the way we work socialize and communicate With the advent of the internet smartphones and artificial intelligence people now have access to vast amounts of information at their fingertips Technology has transformed industries from healthcare to entertainment to education offering new possibilities for innovation and growth However as technology continues to evolve it also raises concerns about privacy security and its impact on society On one hand technology has enabled greater connectivity allowing people to stay in touch with loved ones regardless of geographical distance It has also improved healthcare by enabling advancements like telemedicine and personalized treatments In education it has made learning more accessible with online courses and digital resources On the other hand the widespread use of social media has raised issues about misinformation mental health and the erosion of privacy As automation and artificial intelligence become more integrated into various sectors there are concerns about job displacement and the ethical implications of machines making decisions Ultimately technology is a double edged sword and its impact depends on how it is used and regulated While it has the potential to improve our lives it also requires careful consideration to ensure it benefits all of humanity in a responsible and ethical manner"

    };

    srand(time(0));
    int randomIndex = rand() % 6;
    return paragraph[randomIndex];
}
string testText = paragraph();

void startTest()
{
    int maxTime = (choice == 1) ? 15 : (choice == 2) ? 30
                                                     : 60;
    for (int i = 0; i <= maxTime; i++)
    {
        cout << "\033[s";
        cout << "\033[16;80H";
        cout << "Time: " << i << "s   " << flush;
        cout << "\033[u";
        _sleep(1000);
    }
    cout << "\nTime is up\n";
    keepRunning = false;
    cout << "Press any button to see the results\n";
}

void getCurrentText()
{
    istringstream iss(testText);
    string word;
    totalWords = 0;
    while (iss >> word && totalWords < 100)
    {
        words[totalWords++] = word;
    }

    for (int i = 0; i < totalWords; i++)
    {
        cout << words[i] << " ";
    }
    cout << endl;
}

void checkInput(string input, int y)
{
    if (input == words[y])
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
    while (keepRunning && y < totalWords)
    {
        cout << "\n";
        cout << "\nType here: \n";
        getline(cin >> ws, line);
        istringstream iss(line);
        string word;
        while (iss >> word && y < totalWords && keepRunning)
        {
            checkInput(word, y);
            y++;
        }
    }

    if (!keepRunning && !line.empty())
    {
        istringstream iss(line);
        string word;
        while (iss >> word && y < totalWords)
        {
            checkInput(word, y);
            y++;
        }
    }
}

void resetTest()
{
    keepRunning = true;
    correct = 0;
    wrong = 0;
    for (int i = 0; i < 100; i++)
    {
        corrected[i] = "";
        wronged[i] = "";
    }
}

void runTest()
{
    resetTest();
    getCurrentText();

    // Time selection with validation
    do
    {
        repeat = false;

        cout << "\n\n\n\n\nChoose time: 1: 15 sec, 2: 30 sec, 3: 60 sec: ";
        cin >> choice;

        intCheck();
        isintvalidbool();
        if (choice < 1 || choice > 3)
        {
            cout << ">>> Please select 1, 2, or 3 <<<" << endl;
            repeat = true;
        }
    } while (repeat);
    thread t2(startTest);
    thread t3(input);

    t2.join();
    t3.join();

    cout << "Correct words: " << correct << endl;
    cout << "Wrong words: " << wrong << endl;

    // Display correct words if any
    bool anyCorrect = false;
    cout << "You typed correct:\n";
    for (int i = 0; i < 100; i++)
    {
        if (!corrected[i].empty())
        {
            cout << corrected[i] << " ";
            anyCorrect = true;
        }
    }
    if (!anyCorrect)
    {
        cout << "No correct words typed.\n";
    }

    // Display wrong words if any
    bool anyWrong = false;
    cout << "\nYou typed wrong:\n";
    for (int i = 0; i < 100; i++)
    {
        if (!wronged[i].empty())
        {
            cout << wronged[i] << " ";
            anyWrong = true;
        }
    }
    if (!anyWrong)
    {
        cout << "No wrong words typed.\n";
    }
}
class score
{
public:
    int userCorrect;
    int userWrong;
    int userScore;
    score(int c = 0, int w = 0) : userCorrect(c), userWrong(w) {}
    void display()
    {
        // cout << "User correct words: " << userCorrect << endl;
        // cout << "User wrong words: " << userWrong << endl;
        userScore = userCorrect - userWrong;
        double minutes;
        if (choice == 1)
        {
            minutes = 0.25;
        }
        else if (choice == 2)
        {
            minutes = 0.5;
        }
        else
        {
            minutes = 1.0;
        }
        wpm = (double)userCorrect / minutes;
        // cout << "WPM: " << wpm << endl;
    }
};
class profile : public score
{
public:
    string name;
    score userScoreObj; // ✅ COMPOSITION: profile has a score object
    int WPM;

    profile(string name, score s)
    {
        this->name = name;
        this->userScoreObj = s;
        this->userScoreObj.display(); // Ensure WPM is calculated
        this->WPM = wpm;
    }

    profile()
    {
    }
    void display()
    {
        cout << " username : " << name << endl;
        cout << "the score of " << name << " is == " << userScoreObj.userScore << endl;
        cout << "WPM: " << WPM << endl;
    }
};
class leaderboard : public profile
{
public:
    void display()
    {
        cout << "         name           " << name << "  ";
        cout << "      score             " << userScoreObj.userScore;
        cout << "        WPM             " << WPM << "  " << endl;
    }
};
void quiter()
{
    cout << "here we go again \n";
}

profile allPlayers[100];
int totalPlayers = 0;

int main()
{
    srand(time(0));
    bool restart = false;
    string quit;
    int highest = 0, lowest = 9999;
    string name;
    score users[10];

    // Main game loop
    while (true)
    {

        cout << "\n\n Welcome to the Typing Test!" << endl;

        // Get number of users with validation
        do
        {
            int x;
            repeat = false;
            cout << "\nHow many users or players: (press 100 to see leaderboards)";
            cin >> x;
            intCheck();
            isintvalidbool();

            if (isintvalid && x > 0)
            {
                if (x == 100)
                {
                    cout << "\n                           --- Leaderboard ---\n";
                    if (totalPlayers == 0)
                    {
                        cout << "\n\nNo players have played yet be the first one \n\n";
                    }
                    for (int i = 0; i < totalPlayers; i++)
                    {
                        leaderboard l;
                        l.name = allPlayers[i].name;
                        l.userScoreObj = allPlayers[i].userScoreObj;
                        l.WPM = allPlayers[i].WPM;
                        if (totalPlayers != 0)
                        {
                            l.display();
                        }
                    }
                }
                else if (playagain)
                {
                    number += x; // add new players
                }
                else
                {
                    number = x; // first time
                }
            }
            else
            {
                cout << ">>> Please enter a positive number <<<" << endl;
                repeat = true;
            }
        } while (repeat);

        score *users = new score[number];
        profile *p = new profile[number];

        bool restart = false;
        for (int i = 0; i < number && !restart; i++)
        {
            do
            {
                repeat = false;
                cout << "\nUser " << i + 1 << ", enter your name (or type 'quit' to change the number of users:) \n";
                cin >> name;
                stringcheck(name);
            } while (!isstringvalid);

            if (name == "quit")
            {
                delete[] users; // Clean up before restarting
                delete[] p;
                restart = true;
                continue; // This will break out of the for loop
            }

            runTest();
            users[i] = score(correct, wrong);

            if (users[i].userCorrect > highest)
                highest = users[i].userCorrect;
            if (users[i].userCorrect < lowest)
                lowest = users[i].userCorrect;

            p[i] = profile(name, users[i]);
        }

        if (restart)
        {
            continue; // Restart the whole process
        }

        // Rest of your code...
        cout << "\n\n\n\nFinal Results:\n";
        for (int i = 0; i < number; i++)
        {
            cout << endl;
            users[i].display();
            p[i].userScoreObj.userScore = users[i].userScore;
            p[i].display();
    



            for (int i = 0; i < totalPlayers; i++)
            {
                leaderboard l;
                l.name = allPlayers[i].name;
                l.userScoreObj = allPlayers[i].userScoreObj;
                l.WPM = allPlayers[i].WPM;
                
               
                
                
            }
            
            
        }
        for (int i = 0; i < number; i++)
        {
            allPlayers[totalPlayers++] = p[i]; // Store into global leaderboard array
            if (number > 1) {
                double maxWPM = 0;
                int winnerIndex = -1;
            
                for (int i = 0; i < number; i++) {
                    if (p[i].WPM > maxWPM) {
                        maxWPM = p[i].WPM;
                        winnerIndex = i;
                    }
                }
            
                if (winnerIndex != -1) {
                    cout << "\n\n The winner is: " << p[winnerIndex].name 
                         << " with a WPM of " << p[winnerIndex].WPM << " \n";
                }
            }
            
        }

        delete[] users;
        delete[] p;

        // Option to completely quit the program
        cout << "Type 'quit' to exit or any key to play again: ";
        cin >> quit;
        if (quit == "quit")
        {
            cout << "\n                           --- Leaderboard ---\n";
            for (int i = 0; i < totalPlayers; i++)
            {
                leaderboard l;
                l.name = allPlayers[i].name;
                l.userScoreObj = allPlayers[i].userScoreObj;
                l.WPM = allPlayers[i].WPM;

                l.display();
            }
        } // Close the if block

        else
        {
            flag = true;
            quiter();
        }
    }
    return 0;
}