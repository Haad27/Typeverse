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
string words[100];
int totalWords = 0;

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
        this_thread::sleep_for(chrono::seconds(1));
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
        cout << "\nType here: ";
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
    cout << "\nChoose time: 1: 15 sec, 2: 30 sec, 3: 60 sec: ";
    cin >> choice;

    thread t2(startTest);
    thread t3(input);

    t2.join();
    t3.join();

    cout << "Correct words: " << correct << endl;
    cout << "Wrong words: " << wrong << endl;

    cout << "You typed correct:\n";
    for (int i = 0; i < 100; i++)
    {
        if (!corrected[i].empty())
            cout << corrected[i] << " " << endl;
    }

    cout << "You typed wrong:\n";
    for (int i = 0; i < 100; i++)
    {
        if (!wronged[i].empty())
            cout << wronged[i] << " " << endl;
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
        cout << "User correct words: " << userCorrect << endl;
        cout << "User wrong words: " << userWrong << endl;
        userScore = userCorrect - userWrong;
    }
};
class profile 
{ 
public: 
    string name; 
    score userScoreObj; // ✅ COMPOSITION: profile has a score object

    profile(string name, score s) 
    { 
        this->name = name; 
        this->userScoreObj = s; 
    } 
 
    profile() 
    { 
    } 
    void display() 
    { 
        cout << " username : " << name << endl; 
        cout << "the score of " << name << " is == " << userScoreObj.userScore << endl; 
    } 
};
class leaderboard : public profile
{
public:
    void display()
    {
        cout << "                    " << name << "  ";
        cout << "      ::              " << userScoreObj.userScore << endl;
    }
};
int main()
{
    int number, highest = 0, lowest = 9999;
    string name;
    cout << "Welcome to the Typing Test!" << endl;
    cout << "\nHow many users or players: ";
    cin >> number;

    score *users = new score[number];
    profile *p = new profile[number];

    for (int i = 0; i < number; i++)
    {

        cout << "\nUser " << i + 1 << " is playing" << endl;
        cout << "entrer you name ";
        cin >> name;
        runTest();
        users[i] = score(correct, wrong);

        if (users[i].userCorrect > highest)
            highest = users[i].userCorrect;
        if (users[i].userCorrect < lowest)
            lowest = users[i].userCorrect;

        p[i] = profile(name, users[i]);
    }

    cout << "\n\n\n\nFinal Results:\n";
    for (int i = 0; i < number; i++)
    {
        cout << endl;
        users[i].display();                  // this sets userScore
        p[i].userScoreObj.userScore = users[i].userScore; // copy the score into the profile
        p[i].display();                      // now this will print the correct score
    }

    cout << "Highest score: " << highest << endl;
    cout << "Lowest score: " << lowest << endl;

    for (int i = 0; i < number; i++)
    {
        if (users[i].userCorrect == highest)
            cout << "\nUser " << i + 1 << " is the winner!" << endl;
        if (users[i].userCorrect == lowest)
            cout << "User " << i + 1 << " is the loser." << endl;
    }
    string enter;
    cout << "press enter t see leaderboards ";
    cin >> enter;

   // Sort the profile array based on userScore
for (int i = 0; i < number; i++) {
    for (int j = 0; j < number - 1; j++) {
        if (p[j].userScoreObj.userScore < p[j + 1].userScoreObj.userScore) {
            swap(p[j], p[j + 1]);
        }
    }
}

// Display leaderboard
leaderboard b1;
for (int i = 0; i < number; i++) {
    b1.name = p[i].name;
    b1.userScoreObj.userScore = p[i].userScoreObj.userScore;
    cout << i+1<<" ";
    b1.display();
}


    delete[] users;
    return 0;
}
