#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int MAX = 100;
string words[MAX];
string hints[MAX];
int totalWords = 0;

void loadWords() {
    ifstream file("words.txt");
    string w, h;
    while (file >> w) {
        getline(file, h);
        if (h.size() > 0 && h[0] == ' ') h.erase(0, 1);
        words[totalWords] = w;
        hints[totalWords] = h;
        totalWords++;
        if (totalWords >= MAX) break;
    }
    file.close();
}

void saveScore(string name, int s, int r) {
    ofstream file("scores.txt", ios::app);
    file << name << " " << s << "/" << r << endl;
    file.close();
}

void showScores() {
    ifstream file("scores.txt");
    string line;
    cout << "\n///////////////////////////////\n";
    cout << "//        PAST SCORES        //\n";
    cout << "///////////////////////////////\n";
    if (!file.is_open()) {
        cout << "No score file found yet. Play a game first!\n";
        return;
    }
    bool any = false;
    while (getline(file, line)) {
        if (line.size() > 0) {
            cout << line << endl;
            any = true;
        }
    }
    if (!any) cout << "No past scores yet. Be the first one.\n";
    file.close();
    cout << "///////////////////////////////\n";
}

string hideWord(string w) {
    string t = w;
    for (int i = 0; i < (int)w.size(); i++) {
        if (i % 2 == 0) t[i] = '_';
    }
    return t;
}

string toLowerCase(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
    return s;
}

void banner() {
    cout << "\n";
    cout << "                  FIVE WORDS  |  FIVE ROUNDS\n\n";
    cout << "Rules:\n";
    cout << "1) You will play 5 rounds.\n";
    cout << "2) Each round shows a half-hidden word and a hint.\n";
    cout << "3) Type your guess and hit enter.\n";
    cout << "Good luck.\n";
}


void exitScreen() {
    cout << "\n////////////////////////////////////////////////////////////\n";
    cout << "//                                                        //\n";
    cout << "//  Thanks for playing Word Game (Five Words Edition)!     //\n";
    cout << "//                                                        //\n";
    cout << "//  This Game is made by Abdul Hameed and Bilal Khan       //\n";
    cout << "//                                                        //\n";
    cout << "////////////////////////////////////////////////////////////\n";
}

void congratsScreen(int score, int rounds) {
    cout << "\n////////////////////////////////////////////////////////////\n";
    cout << "//                GAME OVER - RESULTS                      //\n";
    cout << "////////////////////////////////////////////////////////////\n";
    cout << "You scored: " << score << "/" << rounds << "\n\n";

    if (score == rounds) {
        cout << "////////////////////////////////////////////////////////////\n";
        cout << "//  CONGRATULATIONS "<<name<<" ! YOU WON!                            //\n";
        cout << "//  Perfect score. You crushed all five words.           //\n";
        cout << "////////////////////////////////////////////////////////////\n";
    } else if (score >= 3) {
        cout << "Nice work. You're solid. Run it back and hit 5/5.\n";
    } else {
        cout << "Rough one. You're not done. Play again and improve.\n";
    }
    cout << "////////////////////////////////////////////////////////////\n";
}

void startGame() {
    banner();

    string name;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, name);

    int rounds = 5;
    int score = 0;
    srand(time(0));

    cout << "\n///////////////////////////////\n";
    cout << "//   STARTING: 5 WORD GAME    //\n";
    cout << "///////////////////////////////\n";

    for (int i = 0; i < rounds; i++) {
        int idx = rand() % totalWords;
        string original = words[idx];
        string masked = hideWord(original);

        cout << "\nRound " << (i + 1) << " of " << rounds << "\n";
        cout << "Word: " << masked << endl;
        cout << "Hint: " << hints[idx] << endl;

        string guess;
        cout << "Your guess: ";
        cin >> guess;

        if (toLowerCase(guess) == toLowerCase(original)) {
            cout << "Correct\n";
            score++;
        } else {
            cout << "Wrong, correct was: " << original << endl;
        }
    }

    congratsScreen(score, rounds);
    saveScore(name, score, rounds);
}

int main() {
    loadWords();
    if (totalWords == 0) {
        cout << "No words found";
        return 0;
    }

    int choice;
    do {
        cout << "\n--- Word Fill Puzzle ---\n";
        cout << "Five Words Edition (5 rounds each game)\n";
        cout << "1. Start Game\n";
        cout << "2. View Past Scores\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            showScores();
            break;
        case 3:
            cout << "Exiting...\n";
            exitScreen();
            break;
        default:
            cout << "Invalid choice";
        }

    } while (choice != 3);

    return 0;
}
