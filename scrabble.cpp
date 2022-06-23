#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Tile {
public:
    char letter;
    int value;
    Tile(char x, int y) {
        letter = x;
        value = y;
    }
    Tile() {
        letter = 'a';
        value = 0;
    }
};

class TileBag {
public:
    vector<Tile>tiles;
    int amount[26] = { 9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1 };
    int vals[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
    TileBag() {
        for (int i = 0;i < 26;i++) {
            for (int j = 0;j < amount[i];j++) {
                tiles.push_back(Tile(i + 'A', vals[i]));
            }
        }
    }
    Tile takeTile() {
        int gaming = rand() % tiles.size() + 0;
        Tile newTile = tiles[gaming];
        tiles.erase(tiles.begin() + gaming);
        return newTile;
    }
    void returnTile(Tile oldTile) {
        tiles.push_back(oldTile);
    }
};

void menu();
void boardGen(char board[][15]);
void boardPrint(char board[][15]);
int numCheck(int ash);
void gameplay();
void rules();
void dictionary();
void turns(int turnCounter, char hand[], int handVals[], char p2Hand[], int p2HandVals[], string names[], char board[][15], TileBag& bag, bool boolHand[], bool boolHand2[], bool& isP2, int& score1, int& score2, bool& noWords);
void handGen(char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool boolHand[], bool boolHand2[], TileBag& bag);
void playWord(bool& noWords, bool& isP2, char hand[], int handVals[], char p2Hand[], int p2HandVals[], char board[][15], bool boolHand[], bool boolHand2[], int& score1, int& score2);
bool wordCheck(string givenWord, bool& valid);
int assignChar(char newLetter, int& newVal);
void wordAdd(char board[][15], char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool& noWords, string word, bool& isP2, int wordPoints[], int& score1, int& score2, int spaceVal, char newLetter);
void exchange(char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool boolHand[], bool boolHand2[], bool& isP2, TileBag& bag);
void viewScore(int& score1, int& score2, string names[]);
void scoring(int wordPoints[], int& multiplier, int& score1, int& score2, bool& isP2, string word);
void lastTurns(char hand[], int handVals[], char p2Hand[], int p2HandVals[], string names[], char board[][15], TileBag& bag, bool boolHand[], bool boolHand2[], bool& isP2, int& score1, int& score2, bool& noWords);
// declaring functions

char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char black[] = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
char blue[] = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
char purple[] = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
char cyan[] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char Lgray[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
char Bred[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
// colors

int main() {
    int menuCase = 0;
    while (menuCase != 3) {
        menu();
        menuCase = numCheck(menuCase);
        system("cls");
        switch (menuCase) {
            case 1: {
                // case to start the game
                gameplay();
                break;
            }
            case 2: {
                // case to print out the instructions for the game
                rules();
                break;
            }
            case 3: {
                // case to end the program
                cout << "Goodbye!" << endl;
                return 0;
            }
        }
    }
}

void menu() {
    cout << R"(  _      __    __                     __         ____________  ___   ___  ___  __   ______
 | | /| / /__ / /______  __ _  ___   / /____    / __/ ___/ _ \/ _ | / _ )/ _ )/ /  / __/ /
 | |/ |/ / -_) / __/ _ \/  ' \/ -_) / __/ _ \  _\ \/ /__/ , _/ __ |/ _  / _  / /__/ _//_/ 
 |__/|__/\__/_/\__/\___/_/_/_/\__/  \__/\___/ /___/\___/_/|_/_/ |_/____/____/____/___(_)  
                                                                                          
Would you like to:

[1] Start the game!

[2] View the rules!

[3] Exit the program
)";
}

void gameplay() {
    TileBag bag;
    string names[2];
    int handVals[7];
    char hand[7];
    int p2HandVals[7];
    char p2Hand[7];
    char board[15][15];
    int turnCounter = 1;
    bool boolHand[7] = { false, false, false, false, false, false, false };
    bool boolHand2[7] = { false, false, false, false, false, false, false };
    bool isP2 = false;
    int score1 = 0;
    int score2 = 0;
    bool noWords = true;
    // initializing variables

    cout << "So it begins. Player one, what is your name?" << endl;
    cin.clear();
    getline(cin >> ws, names[0]);
    system("cls");
    Sleep(1000);
    cout << "Now, Player 2, please input your name." << endl;
    cin.clear();
    getline(cin >> ws, names[1]);
    system("cls");
    // inputting names
    turns(turnCounter, hand, handVals, p2Hand, p2HandVals, names, board, bag, boolHand, boolHand2, isP2, score1, score2, noWords); // go play the game(it begins)
    lastTurns(hand, handVals, p2Hand, p2HandVals, names, board, bag, boolHand, boolHand2, isP2, score1, score2, noWords); // game ending, happens either on forcequit or on no more tiles being in the bag
}

void turns(int turnCounter, char hand[], int handVals[], char p2Hand[], int p2HandVals[], string names[], char board[][15], TileBag& bag, bool boolHand[], bool boolHand2[], bool& isP2, int& score1, int& score2, bool& noWords) {
    int turnOption = 0;
    bool isFirstTurn = true;
    // initializing variables

    while (bag.tiles.size() == 0 || turnOption != 99) {
        // loop that will run until there are either no more tiles in the tile bag or until someone force quits out of the game as a result of no more turns
        if (isP2 == false) {
            // player 1 menu
            cout << R"(
   ___  __                    ___  __                __
  / _ \/ /__ ___ _____ ____  <  / / /___ _________  / /
 / ___/ / _ `/ // / -_) __/  / / / __/ // / __/ _ \/_/ 
/_/  /_/\_,_/\_, /\__/_/    /_/  \__/\_,_/_/ /_//_(_)  
            /___/                          

)";
            cout << names[0] << ", it is your turn!" << " It is turn " << turnCounter << "." << endl;
        }
        else {
            // player 2 menu
            cout << R"(
   ___  __                    ___    __                __
  / _ \/ /__ ___ _____ ____  |_  |  / /___ _________  / /
 / ___/ / _ `/ // / -_) __/ / __/  / __/ // / __/ _ \/_/ 
/_/  /_/\_,_/\_, /\__/_/   /____/  \__/\_,_/_/ /_//_(_)  
            /___/                                        

)";
            cout << names[1] << ", it is your turn!" << " It is turn " << turnCounter << "." << endl;
        }
        if (noWords == true) {
            // reminds the user that on the first turn a word can only be played in the middle of the board
            cout << "Please remember that there are no words on the board yet, so whatever word you play must cross the middle." << endl;
        }
        else {
            cout << "Remember that all words must intersect!" << endl;
        }
        cout << "\n\n";
        handGen(hand, handVals, p2Hand, p2HandVals, boolHand, boolHand2, bag); // generating hands for both users
        if (turnCounter == 1) {
            boardGen(board); // generating the board on its first print
        }
        else {
            boardPrint(board); // printing the board
        }
        cout << "\n\n";
        cout << "Here is your hand:" << endl;
        if (isP2 == false) {
            // showing player 1's hand
            for (int i = 0;i < 7;i++) {
                cout << hand[i] << "(" << handVals[i] << ")" << " ";
            }
        }
        else {
            // showing player 2's hand
            for (int j = 0;j < 7;j++) {
                cout << p2Hand[j] << "(" << p2HandVals[j] << ")" << " ";
            }
        }
        cout << endl;
        // switch for the options on any given turn
        cout << "\nYou can now: \n[1] Play a word\n[2] Exchange tiles\n[3] Check if a word is valid\n[4] Review the instructions\n[5] View scores\n[6] Pass your turn\n";
        if (noWords == false && turnCounter > 2) {
            cout << "[99] Force quit out of the game\n\n";
        }
        turnOption = numCheck(turnOption);
        system("cls");
        switch (turnOption) {
            case 1: {
                // case to play a word
                playWord(noWords, isP2, hand, handVals, p2Hand, p2HandVals, board, boolHand, boolHand2, score1, score2);
                // do the player swap inside of the function
                turnCounter++;
                break;
            }
            case 2: {
                // case to exchange tiles
                exchange(hand, handVals, p2Hand, p2HandVals, boolHand, boolHand2, isP2, bag);
                turnCounter++;
                break;
            }
            case 3: {
                // case to check if a word is valid
                dictionary();
                break;
            }
            case 4: {
                // rules again
                rules();
                break;
            }
            case 5: {
                // scoring
                viewScore(score1, score2, names);
                break;
            }
            case 6: {
                //pass
                if (isP2 == false) {
                    isP2 = true;
                }
                else {
                    isP2 = false;
                }
                turnCounter++;
                break;
            }
            case 99: {
                // force quitting
                if (noWords == true && turnCounter < 3) {
                    turnOption = 0;
                    cout << "You can't do that yet!" << endl; // there should be at least 1 word on the board and both players should have taken a turn for a game to be force quit
                    break;
                }
                else {
                    break;
                }
            }
            default: {
                // in the case of a wrong input
                cout << "Invalid." << endl;
                break;
            }
        }
    }
}

void lastTurns(char hand[], int handVals[], char p2Hand[], int p2HandVals[], string names[], char board[][15], TileBag& bag, bool boolHand[], bool boolHand2[], bool& isP2, int& score1, int& score2, bool& noWords) {
    char option;
    int turnOption = 0;
    system("cls");
    cout << "We're in the endgame now! Each user gets 1 more turn and then the scores will be tallied to declare the winner." << endl;
    cout << "Press a to continue" << endl;
    cin >> option;
    while (option != 'a') {
        cout << "Please input a (lowercase)" << endl;
        cin >> option;
    }
    system("cls");
    for (int k = 0;k < 2;k++) {
        if (isP2 == false) {
            // player 1 menu
            cout << R"(
   ___  __                    ___  __                __
  / _ \/ /__ ___ _____ ____  <  / / /___ _________  / /
 / ___/ / _ `/ // / -_) __/  / / / __/ // / __/ _ \/_/ 
/_/  /_/\_,_/\_, /\__/_/    /_/  \__/\_,_/_/ /_//_(_)  
            /___/                          

)";
            cout << names[0] << ", it is your turn!" << endl;
        }
        else {
            // player 2 menu
            cout << R"(
   ___  __                    ___    __                __
  / _ \/ /__ ___ _____ ____  |_  |  / /___ _________  / /
 / ___/ / _ `/ // / -_) __/ / __/  / __/ // / __/ _ \/_/ 
/_/  /_/\_,_/\_, /\__/_/   /____/  \__/\_,_/_/ /_//_(_)  
            /___/                                        

)";
            cout << names[1] << ", it is your turn!" << " It is turn " << endl;
        }
        if (noWords == true) {
            // reminds the user that on the first turn a word can only be played in the middle of the board
            cout << "Please remember that there are no words on the board yet, so whatever word you play must cross the middle." << endl;
        }
        else {
            cout << "Remember that all words must intersect!" << endl;
        }
        handGen(hand, handVals, p2Hand, p2HandVals, boolHand, boolHand2, bag);
        boardPrint(board);
        cout << "\n\n";
        cout << "Here is your hand:" << endl;
        if (isP2 == false) {
            // showing player 1's hand
            for (int i = 0;i < 7;i++) {
                cout << hand[i] << "(" << handVals[i] << ")" << " ";
            }
        }
        else {
            // showing player 2's hand
            for (int j = 0;j < 7;j++) {
                cout << p2Hand[j] << "(" << p2HandVals[j] << ")" << " ";
            }
        }
        cout << "\nYou can now: \n[1] Play a word\n[2] Check if a word is valid\n[3] Pass your turn\n\n";
        turnOption = numCheck(turnOption);
        system("cls");
        switch (turnOption) {
            case 1: {
                // case to play a word
                playWord(noWords, isP2, hand, handVals, p2Hand, p2HandVals, board, boolHand, boolHand2, score1, score2);
                // do the player swap inside of the function
                break;
            }
            case 2: {
                // case to check if a word is valid
                dictionary();
                break;
            }
            case 3: {
                //pass
                if (isP2 == false) {
                    isP2 = true;
                }
                else {
                    isP2 = false;
                }
                break;
            }
            default: {
                // in the case of a wrong input
                cout << "Invalid." << endl;
                break;
            }
        }
    }
    system("cls");
    // assigning the winner of the match
    if (score1 == score2) {
        cout << R"(   ______ _               __  _     __
  /  _/ /( )___   ___ _  / /_(_)__ / /
 _/ // __//(_-<  / _ `/ / __/ / -_)_/ 
/___/\__/ /___/  \_,_/  \__/_/\__(_)  
                                      
)";
    }
    else if (score1 > score2) {
        cout << R"(   ___  __                    ___         _          __
  / _ \/ /__ ___ _____ ____  <  / _    __(_)__  ___ / /
 / ___/ / _ `/ // / -_) __/  / / | |/|/ / / _ \(_-</_/ 
/_/  /_/\_,_/\_, /\__/_/    /_/  |__,__/_/_//_/___(_)  
            /___/                                      
)";
    }
    else {
        cout << R"(   ___  __                    ___           _          __
  / _ \/ /__ ___ _____ ____  |_  |  _    __(_)__  ___ / /
 / ___/ / _ `/ // / -_) __/ / __/  | |/|/ / / _ \(_-</_/ 
/_/  /_/\_,_/\_, /\__/_/   /____/  |__,__/_/_//_/___(_)  
            /___/                                        )";
    }
    cout << "\n\n";
    cout << "The score was " << score1 << " - " << score2 << "!" << endl;
    cout << "Press a to go back to the main menu" << endl; // go back to the main menu
    cin >> option;
    while (option != 'a') {
        cout << "Please input a (lowercase)" << endl;
        cin >> option;
    }
    system("cls");
}

void playWord(bool& noWords, bool& isP2, char hand[], int handVals[], char p2Hand[], int p2HandVals[], char board[][15], bool boolHand[], bool boolHand2[], int& score1, int& score2) {
    string word;
    int badCounter = 0;
    int wordPoints[7] = { 0, 0, 0, 0, 0, 0, 0 };
    bool valid = false;
    bool valid2 = false;
    bool valid3 = false;
    int spaceVal = 0;
    char newLetter = ' ';
    int newVal = 0;
    int spaceCount = 0;
    // initializing variables
    cout << "Below is the board and your hand. What word would you like to play." << endl;
    if (noWords == true) {
        // reminding the user once again that if there are no words on the board the word must cross the middle
        cout << "There are no words on the board, so your word must cross the middle" << endl;
        valid3 = true;
    }
    else {
        // reminding the user about intersection rules
        cout << "Please put a 0 where you would like the word to intersect" << endl;
    }
    cout << "Remember to always input the word in UPPERCASE!" << endl;
    boardPrint(board); // prints the board
    cout << "\n\n";
    if (isP2 == false) {
        for (int i = 0;i < 7;i++) {
            cout << hand[i] << "(" << handVals[i] << ")" << " ";
        }
    }
    else {
        for (int j = 0;j < 7;j++) {
            cout << p2Hand[j] << "(" << p2HandVals[j] << ")" << " ";
        }
    }
    // showing hands
    cout << "\n\n";
    while (valid == false) {
        cout << "Please input your word here: " << endl;
        cin.clear();
        getline(cin >> ws, word);
        // input a word
        while (word.length() > 7 || word.length() < 2) {
            // in case if the word has the wrong length
            cout << "You cannot make a word that long!" << endl;
            cin.clear();
            getline(cin >> ws, word);
        }
        if (isP2 == false) {
            // checks through all of the first player's tiles to see if they have all the tiles required
            for (int k = 0;k < word.length();k++) {
                badCounter = 0;
                for (int l = 0;l < 7;l++) {
                    if (noWords == false) {
                        if (word[k] == '0') {
                            // assgin a value to the intersecting placeholder
                            cout << "What character do you intend to use in this space?";
                            cin.clear();
                            cin >> newLetter;
                            spaceVal = k;
                            word[k] = newLetter;
                            assignChar(newLetter, newVal);
                            wordPoints[k] = newVal;
                            valid3 = true;
                            spaceCount++;
                            continue;
                        }
                    }
                    if (word[k] != hand[l] || (word[k] == hand[l] && boolHand[l] == false)) {
                        badCounter++;
                    }
                    else {
                        // flags all the correct tiles to be overwritten and stores the int value of the character
                        boolHand[l] = false;
                        wordPoints[l] = handVals[l];
                        break;
                    }
                }
                if (badCounter == 7) {
                    // in case if the correct tile is not present
                    cout << "Invalid word at index " << k << endl;
                    for (int m = 0;m < 7;m++) {
                        boolHand[m] = true;
                    }
                    break;
                }
            }
        }
        else {
            // checks through all of the second player's tiles to see if they have all the tiles required
            for (int k = 0;k < word.length();k++) {
                badCounter = 0;
                for (int l = 0;l < 7;l++) {
                    if (noWords == false) {
                        if (word[k] == '0') {
                            // assign a value to the intersecting placeholder
                            cout << "What character do you intend to use in this space?";
                            cin.clear();
                            cin >> newLetter;
                            spaceVal = k;
                            word[k] = newLetter;
                            assignChar(newLetter, newVal);
                            wordPoints[k] = newVal;
                            valid3 = true;
                            spaceCount++;
                            continue;
                        }
                    }
                    if (word[k] != p2Hand[l] || (word[k] == p2Hand[l] && boolHand2[l] == false)) {
                        badCounter++;
                    }
                    else {
                        // flags all the correct tiles to be overwritten and stores the int value of the character
                        boolHand2[l] = false;
                        wordPoints[l] = p2HandVals[l];
                        break;
                    }
                }
                if (badCounter == 7) {
                    // in case if the correct tile is not present
                    cout << "Invalid word at index " << k << endl;
                    for (int m = 0;m < 7;m++) {
                        boolHand2[m] = true;
                    }
                    break;
                }
            }
        }
        if (badCounter == 7) {
            // restarts the loop if invalid
            continue;
        }
        if (valid3 == false) {
            // restarts if there are no spaces
            cout << "You can't intersect without the space! Go input again." << endl;
            continue;
        }
        if (spaceCount > 1) {
            // restarts if there is more than 1 space
            cout << "In this version you unfortunately cannot intersect more than once. Please input again." << endl;
            spaceCount = 0;
            continue;
        }
        wordCheck(word, valid); // checks if the word is valid in the dictionary
        if (valid == false) {
            cout << "Invalid" << endl;
        }
        else {
            break;
        }
    }
    wordAdd(board, hand, handVals, p2Hand, p2HandVals, noWords, word, isP2, wordPoints, score1, score2, spaceVal, newLetter); // now add the word to the board
}

int assignChar(char newLetter, int& newVal) {
    // assigning the intersect character value again, this could have been prevented if I used classes better. Happens.
    if (newLetter == 'E' || newLetter == 'A' || newLetter == 'I' || newLetter == 'U' || newLetter == 'O' || newLetter == 'N' || newLetter == 'R' || newLetter == 'T' || newLetter == 'S' || newLetter == 'L') {
        newVal = 1;
    }
    else if (newLetter == 'D' || newLetter == 'G') {
        newVal = 2;
    }
    else if (newLetter == 'B' || newLetter == 'C' || newLetter == 'M' || newLetter == 'P') {
        newVal = 3;
    }
    else if (newLetter == 'F' || newLetter == 'H' || newLetter == 'V' || newLetter == 'W' || newLetter == 'Y') {
        newVal = 4;
    }
    else if (newLetter == 'K') {
        newVal = 5;
    }
    else if (newLetter == 'X' || newLetter == 'J') {
        newVal = 8;
    }
    else {
        newVal = 10;
    }
    return newVal;
}

void wordAdd(char board[][15], char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool& noWords, string word, bool& isP2, int wordPoints[], int& score1, int& score2, int spaceVal, char newLetter) {
    int dirOp = 0;
    bool validPlace = false;
    int startPosX = 0;
    int startPosY = 0;
    int counter = 0;
    int multiplier = 1;
    char option;
    // initializing variables
    while (validPlace == false) {
        cout << "Now input a coordinate to place the first letter of your word (input x axis and then y axis, goes from 0-14)" << endl;
        startPosX = numCheck(startPosX);
        startPosY = numCheck(startPosY);
        // inputting coordinates for the word
        cout << "Now, which direction will you put the piece?" << endl;
        cout << "[1] Left\n[2] Right\n[3] Up\n[4] Down\n" << endl;
        dirOp = numCheck(dirOp);
        // swtich case for the direction of the string 
        switch (dirOp) {
            case 1: {
                // left
                if (noWords == true) {
                    if (startPosX < 7 || startPosX >= 7 + word.length() || startPosY != 7) {
                        // if there are no words they must cross the middle
                        cout << "Please choose another direction or input another coordinate." << endl;
                        break;
                    }
                }
                else {
                    if (board[startPosY][startPosX - spaceVal] != newLetter) {
                        // in the case that the intersecting letters are not equal
                        cout << "Please choose another direction or input another coordinate" << endl;
                        break;
                    }
                }
                if (startPosX - word.length() < 0) {
                    // in case if the coordinate cannot be uesd
                    cout << "Please choose another direction or input another coordinate." << endl;
                    break;
                }
                else {
                    for (int l = startPosX;l > startPosX - word.length();l--) {
                        board[startPosY][l] = word[counter]; // overwrite the index of the board with your word
                        // checking for extra point tiles
                        if (noWords == false) {
                            if (l == startPosX - spaceVal) {
                                counter++; // if an intersecting tile is on a multiplier it cannot be used again
                            }
                            else {
                                if ((startPosY == 0 && (l == 0 || l == 7 || l == 14)) || (startPosY == 7 && (l == 0 || l == 14)) || (startPosY == 14 && (l == 0 || l == 7 || l == 14))) {
                                    multiplier = 3;
                                }
                                else if (((startPosY == 0 || startPosY == 14) && (l == 3 || l == 11)) || ((startPosY == 2 || startPosY == 12) && (l == 6 || l == 8)) || ((startPosY == 3 || startPosY == 11) && (l == 0 || l == 7 || l == 14)) || ((startPosY == 6 || startPosY == 8) && (l == 2 || l == 6 || l == 8 || l == 12)) || (startPosY == 7 && (l == 3 || l == 11))) {
                                    wordPoints[counter] *= 2;
                                }
                                else if ((startPosY == 1 || startPosY == 13) && (l == 5 || l == 9) || ((startPosY == 5 || startPosY == 9) && (l == 1 || l == 5 || l == 9 || l == 13))) {
                                    wordPoints[counter] *= 3;
                                }
                                else if (startPosY == l || 14 - startPosY == l) {
                                    multiplier = 2;
                                }
                                counter++; // output the next letter
                            }
                        }
                        else {
                            // I am so so sorry but it had to be done
                            // I could have made this a function but there are too many specifics and other more pressing things to worry about at the moment I am typing this comment (7:50PM)
                            if ((startPosY == 0 && (l == 0 || l == 7 || l == 14)) || (startPosY == 7 && (l == 0 || l == 14)) || (startPosY == 14 && (l == 0 || l == 7 || l == 14))) {
                                multiplier = 3;
                            }
                            else if (((startPosY == 0 || startPosY == 14) && (l == 3 || l == 11)) || ((startPosY == 2 || startPosY == 12) && (l == 6 || l == 8)) || ((startPosY == 3 || startPosY == 11) && (l == 0 || l == 7 || l == 14)) || ((startPosY == 6 || startPosY == 8) && (l == 2 || l == 6 || l == 8 || l == 12)) || (startPosY == 7 && (l == 3 || l == 11))) {
                                wordPoints[counter] *= 2;
                            }
                            else if ((startPosY == 1 || startPosY == 13) && (l == 5 || l == 9) || ((startPosY == 5 || startPosY == 9) && (l == 1 || l == 5 || l == 9 || l == 13))) {
                                wordPoints[counter] *= 3;
                            }
                            else if (startPosY == l || 14 - startPosY == l) {
                                multiplier = 2;
                            }
                            counter++; // output the next letter
                        }
                    }
                    validPlace = true; // that word was correct
                    noWords = false;
                }
                break;
            }
            case 2: {
                // right
                if (noWords == true) {
                    if (startPosX > 7 || startPosX <= 7 - word.length() || startPosY != 7) {
                        // in the case of a wrong coordinate
                        cout << "Please choose another direction or input another coordinate." << endl;
                        break;
                    }
                }
                else {
                    if (board[startPosY][startPosX + spaceVal] != newLetter) {
                        // in case the intersecting letter does not match
                        cout << "Please choose another direction or input another coordinate" << endl;
                        break;
                    }
                }
                if (startPosX + word.length() > 14) {
                    // we don't want to send this outside of the board
                    cout << "Please choose another direction or input another coordinate." << endl;
                    break;
                }
                else {
                    for (int l = startPosX;l < startPosX + word.length();l++) {
                        board[startPosY][l] = word[counter]; // overwrites the board
                        // checking for multilpliers
                        if (noWords == false) {
                            if (l == startPosX + spaceVal) {
                                counter++; // if an intersecting tile is on a multiplier it cannot be used again
                            }
                            else {
                                if ((startPosY == 0 && (l == 0 || l == 7 || l == 14)) || (startPosY == 7 && (l == 0 || l == 14)) || (startPosY == 14 && (l == 0 || l == 7 || l == 14))) {
                                    multiplier = 3;
                                }
                                else if (((startPosY == 0 || startPosY == 14) && (l == 3 || l == 11)) || ((startPosY == 2 || startPosY == 12) && (l == 6 || l == 8)) || ((startPosY == 3 || startPosY == 11) && (l == 0 || l == 7 || l == 14)) || ((startPosY == 6 || startPosY == 8) && (l == 2 || l == 6 || l == 8 || l == 12)) || (startPosY == 7 && (l == 3 || l == 11))) {
                                    wordPoints[counter] *= 2;
                                }
                                else if ((startPosY == 1 || startPosY == 13) && (l == 5 || l == 9) || ((startPosY == 5 || startPosY == 9) && (l == 1 || l == 5 || l == 9 || l == 13))) {
                                    wordPoints[counter] *= 3;
                                }
                                else if (startPosY == l || 14 - startPosY == l) {
                                    multiplier = 2;
                                }
                                counter++; // output the next letter
                            }
                        }
                        else {
                            if ((startPosY == 0 && (l == 0 || l == 7 || l == 14)) || (startPosY == 7 && (l == 0 || l == 14)) || (startPosY == 14 && (l == 0 || l == 7 || l == 14))) {
                                multiplier = 3;
                            }
                            else if (((startPosY == 0 || startPosY == 14) && (l == 3 || l == 11)) || ((startPosY == 2 || startPosY == 12) && (l == 6 || l == 8)) || ((startPosY == 3 || startPosY == 11) && (l == 0 || l == 7 || l == 14)) || ((startPosY == 6 || startPosY == 8) && (l == 2 || l == 6 || l == 8 || l == 12)) || (startPosY == 7 && (l == 3 || l == 11))) {
                                wordPoints[counter] *= 2;
                            }
                            else if ((startPosY == 1 || startPosY == 13) && (l == 5 || l == 9) || ((startPosY == 5 || startPosY == 9) && (l == 1 || l == 5 || l == 9 || l == 13))) {
                                wordPoints[counter] *= 3;
                            }
                            else if (startPosY == l || 14 - startPosY == l) {
                                multiplier = 2;
                            }
                            counter++; // output the next letter
                        }
                    }
                    validPlace = true; // the word is valid
                    noWords = false;
                }
                break;
            }
            case 3: {
                // up
                if (noWords == true) {
                    if (startPosY < 7 || startPosY >= 7 + word.length() || startPosX != 7) {
                        // in case of a wrong coordinate
                        cout << "Please choose another direction or input another coordinate." << endl;
                        break;
                    }
                }
                else {
                    if (board[startPosY - spaceVal][startPosX] != newLetter) {
                        // in the case of a wrong coordinate
                        cout << "Please choose another direction or input another coordinate" << endl;
                        break;
                    }
                }
                if (startPosY - word.length() < 0) {
                    // so that it does not go outside of the boundary
                    cout << "Please choose another direction or input another coordinate." << endl;
                    break;
                }
                else {
                    for (int k = startPosY;k > startPosY - word.length();k--) {
                        board[k][startPosX] = word[counter]; // overwrites the board with the chosen word
                        // checking for multiplier tiles
                        if (noWords == false) {
                            if (k == startPosY - spaceVal) {
                                counter++; // if an intersecting tile is on a multiplier it cannot be used again
                            }
                            else {
                                if ((k == 0 && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || (k == 7 && (startPosX == 0 || startPosX == 14)) || (k == 14 && (startPosX == 0 || startPosX == 7 || startPosX == 14))) {
                                    multiplier = 3;
                                }
                                else if (((k == 0 || k == 14) && (startPosX == 3 || startPosX == 11)) || ((k == 2 || k == 12) && (startPosX == 6 || startPosX == 8)) || ((k == 3 || k == 11) && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || ((k == 6 || k == 8) && (startPosX == 2 || startPosX == 6 || startPosX == 8 || startPosX == 12)) || (k == 7 && (startPosX == 3 || startPosX == 11))) {
                                    wordPoints[counter] *= 2;
                                }
                                else if ((k == 1 || k == 13) && (startPosX == 5 || startPosX == 9) || ((k == 5 || k == 9) && (startPosX == 1 || startPosX == 5 || startPosX == 9 || startPosX == 13))) {
                                    wordPoints[counter] *= 3;
                                }
                                else if (k == startPosX || 14 - k == startPosX) {
                                    multiplier = 2;
                                }
                                counter++;
                            }
                        }
                        else {
                            if ((k == 0 && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || (k == 7 && (startPosX == 0 || startPosX == 14)) || (k == 14 && (startPosX == 0 || startPosX == 7 || startPosX == 14))) {
                                multiplier = 3;
                            }
                            else if (((k == 0 || k == 14) && (startPosX == 3 || startPosX == 11)) || ((k == 2 || k == 12) && (startPosX == 6 || startPosX == 8)) || ((k == 3 || k == 11) && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || ((k == 6 || k == 8) && (startPosX == 2 || startPosX == 6 || startPosX == 8 || startPosX == 12)) || (k == 7 && (startPosX == 3 || startPosX == 11))) {
                                wordPoints[counter] *= 2;
                            }
                            else if ((k == 1 || k == 13) && (startPosX == 5 || startPosX == 9) || ((k == 5 || k == 9) && (startPosX == 1 || startPosX == 5 || startPosX == 9 || startPosX == 13))) {
                                wordPoints[counter] *= 3;
                            }
                            else if (k == startPosX || 14 - k == startPosX) {
                                multiplier = 2;
                            }
                            counter++;
                        }
                    }
                    validPlace = true; // word is valid
                    noWords = false;
                }
                break;
            }
            case 4: {
                // down
                if (noWords == true) {
                    if (startPosY > 7 || startPosY <= 7 - word.length() || startPosX != 7) {
                        // in case of a wrong coordinate
                        cout << "Please choose another direction or input another coordinate." << endl;
                        break;
                    }
                }
                else {
                    if (board[startPosY][startPosX + spaceVal] != newLetter) {
                        // in case 2 intersecting letters don't match
                        cout << "Please choose another direction or input another coordinate" << endl;
                        break;
                    }
                }
                if (startPosY + word.length() > 14) {
                    // do not go outside the board
                    cout << "Please choose another direction or input another coordinate." << endl;
                    break;
                }
                else {
                    for (int k = startPosY;k < startPosY + word.length();k++) {
                        board[k][startPosX] = word[counter]; // overwrites the board
                        // checking for multiplier tiles
                        if (noWords == false) {
                            if (k == startPosY + spaceVal) {
                                counter++; // if an intersecting tile is on a multiplier it cannot be used again
                            }
                            else {
                                if ((k == 0 && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || (k == 7 && (startPosX == 0 || startPosX == 14)) || (k == 14 && (startPosX == 0 || startPosX == 7 || startPosX == 14))) {
                                    multiplier = 3;
                                }
                                else if (((k == 0 || k == 14) && (startPosX == 3 || startPosX == 11)) || ((k == 2 || k == 12) && (startPosX == 6 || startPosX == 8)) || ((k == 3 || k == 11) && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || ((k == 6 || k == 8) && (startPosX == 2 || startPosX == 6 || startPosX == 8 || startPosX == 12)) || (k == 7 && (startPosX == 3 || startPosX == 11))) {
                                    wordPoints[counter] *= 2;
                                }
                                else if ((k == 1 || k == 13) && (startPosX == 5 || startPosX == 9) || ((k == 5 || k == 9) && (startPosX == 1 || startPosX == 5 || startPosX == 9 || startPosX == 13))) {
                                    wordPoints[counter] *= 3;
                                }
                                else if (k == startPosX || 14 - k == startPosX) {
                                    multiplier = 2;
                                }
                                counter++;
                            }
                        }
                        else {
                            if ((k == 0 && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || (k == 7 && (startPosX == 0 || startPosX == 14)) || (k == 14 && (startPosX == 0 || startPosX == 7 || startPosX == 14))) {
                                multiplier = 3;
                            }
                            else if (((k == 0 || k == 14) && (startPosX == 3 || startPosX == 11)) || ((k == 2 || k == 12) && (startPosX == 6 || startPosX == 8)) || ((k == 3 || k == 11) && (startPosX == 0 || startPosX == 7 || startPosX == 14)) || ((k == 6 || k == 8) && (startPosX == 2 || startPosX == 6 || startPosX == 8 || startPosX == 12)) || (k == 7 && (startPosX == 3 || startPosX == 11))) {
                                wordPoints[counter] *= 2;
                            }
                            else if ((k == 1 || k == 13) && (startPosX == 5 || startPosX == 9) || ((k == 5 || k == 9) && (startPosX == 1 || startPosX == 5 || startPosX == 9 || startPosX == 13))) {
                                wordPoints[counter] *= 3;
                            }
                            else if (k == startPosX || 14 - k == startPosX) {
                                multiplier = 2;
                            }
                            counter++;
                        }
                    }
                    validPlace = true; // word is valid
                    noWords = false;
                }
                break;
            }
            default: {
                // in case of a wrong input
                cout << "Invalid" << endl;
                break;
            }
        }
    }
    scoring(wordPoints, multiplier, score1, score2, isP2, word); // scores the word
    // next turn
    cout << "Press a to go back to the menu" << endl;
    cin >> option;
    while (option != 'a') {
        cout << "Please input a (lowercase)" << endl;
        cin >> option;
    }
    system("cls");
    if (isP2 == false) {
        isP2 = true;
    }
    else {
        isP2 = false;
    }
}

void scoring(int wordPoints[], int& multiplier, int& score1, int& score2, bool& isP2, string word) {
    int points = 0;
    for (int i = 0;i < 7;i++) {
        points += wordPoints[i]; // adds on the points based on each character's value
    }
    points *= multiplier; // if there was a multiplier multiply the points
    if (word.length() == 7) {
        // in case if the user gets a bingo
        cout << "You got a bingo! That's 50 more points!" << endl;
        points += 50;
    }
    cout << "You scored " << points << " this turn!" << endl;
    if (isP2 == false) {
        score1 += points; // stores the score and shows the total
        cout << "Your total score is now " << score1 << endl;
    }
    else {
        score2 += points; // stores the score and shows the total
        cout << "Your total score is now " << score2 << endl;
    }
}

void viewScore(int& score1, int& score2, string names[]) {
    char option;
    cout << names[0] << ": " << score1 << "\n\n" << names[1] << ": " << score2 << endl; // shows player 1 and 2 scores
    cout << "Press a to go back to the menu" << endl;
    cin >> option;
    while (option != 'a') {
        cout << "Please input a (lowercase)" << endl;
        cin >> option;
    }
    system("cls");
}

void handGen(char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool boolHand[], bool boolHand2[], TileBag& bag) {
    srand(time(NULL));
    Tile tempTile;
    for (int i = 0;i < 7;i++) {
        if (boolHand[i] == false) {
            tempTile = bag.takeTile(); // take a tile out of the bag
            hand[i] = tempTile.letter;
            handVals[i] = tempTile.value;
            boolHand[i] = true;
            // assign the int and char value of the tile then flag the index
        }
        else {
            // if the index is flagged just skip it
            continue;
        }

    }
    for (int j = 0;j < 7;j++) {
        if (boolHand2[j] == false) {
            tempTile = bag.takeTile(); // take a tile out of the bag
            p2Hand[j] = tempTile.letter;
            p2HandVals[j] = tempTile.value;
            boolHand2[j] = true;
            // assign the letter and char value of the tile then flag the index
        }
        else {
            // if the index is flagged just skip it
            continue;
        }
    }
}

void exchange(char hand[], int handVals[], char p2Hand[], int p2HandVals[], bool boolHand[], bool boolHand2[], bool& isP2, TileBag& bag) {
    int exArr[7];
    Tile goneTile;
    char option;
    cout << "Welcome to exchange menu. Which pieces would you like to put back in the bag for some new ones?" << endl;
    cout << "You will input 1 if you want to remove the piece and 0 if you want to keep it" << endl;
    if (isP2 == false) {
        for (int i = 0;i < 7;i++) {
            cout << hand[i] << "(" << handVals[i] << ")" << " "; // showing hand
        }
        cout << endl;
        for (int j = 0;j < 7;j++) {
            exArr[j] = numCheck(exArr[j]);
            while (exArr[j] > 1 || exArr[j] < 0) {
                // if the input is not 1 or 0
                cout << "Invalid." << endl;
                exArr[j] = numCheck(exArr[j]);
            }
            if (exArr[j] == 1) {
                boolHand[j] = false; // if 1 is inputted exchange tile and flag the index
            }
            else {
                continue; // is 0 is inputted do nothing
            }
        }
        for (int k = 0;k < 7;k++) {
            if (boolHand[k] == false) {
                // replace the tile of each flagged index by talking the tile and putting it back in the bag
                goneTile.letter = hand[k];
                goneTile.value = handVals[k];
                bag.returnTile(goneTile);
            }
        }
        handGen(hand, handVals, p2Hand, p2HandVals, boolHand, boolHand2, bag); // give user their now missing tiles
        cout << "Here is your new hand:" << endl;
        for (int l = 0;l < 7;l++) {
            cout << hand[l] << "(" << handVals[l] << ")" << " "; // show the user's hand
        }
        cout << endl;
        isP2 = true; // change the player
        cout << "Press a to go back to the menu" << endl;
        cin >> option;
        while (option != 'a') {
            cout << "Please input a (lowercase)" << endl;
            cin >> option;
        }
        system("cls");
    }
    else {
        for (int i = 0;i < 7;i++) {
            cout << p2Hand[i] << "(" << p2HandVals[i] << ")" << " "; // showing hand
        }
        cout << endl;
        for (int j = 0;j < 7;j++) {
            exArr[j] = numCheck(exArr[j]);
            while (exArr[j] > 1 || exArr[j] < 0) {
                // if input is not 1 or 0
                cout << "Invalid." << endl;
                exArr[j] = numCheck(exArr[j]);
            }
            if (exArr[j] == 1) {
                boolHand2[j] = false; // if 1 is inputted exchange tile and flag the index
            }
            else {
                continue; // is 0 is inputted do nothing
            }
        }
        for (int k = 0;k < 7;k++) {
            if (boolHand2[k] == false) {
                // replace the tile of each flagged index by talking the tile and putting it back in the bag
                goneTile.letter = p2Hand[k];
                goneTile.value = p2HandVals[k];
                bag.returnTile(goneTile);
            }
        }
        handGen(hand, handVals, p2Hand, p2HandVals, boolHand, boolHand2, bag); // give user their now missing tiles
        cout << "Here is your new hand:" << endl;
        for (int l = 0;l < 7;l++) {
            cout << p2Hand[l] << "(" << p2HandVals[l] << ")" << " "; // show the user's hand
        }
        cout << endl;
        isP2 = false; // change player
        cout << "Press a to go back to the menu" << endl;
        cin >> option;
        while (option != 'a') {
            cout << "Please input a (lowercase)" << endl;
            cin >> option;
        }
        system("cls");
    }
}

void boardGen(char board[][15]) {
    for (int i = 0;i < 15;i++) {
        // rows
        for (int j = 0;j < 15;j++) {
            // columns
            // if statements to print out the multilpier tiles
            // print out just * so that it is a new fresh board
            if ((i == 0 && (j == 0 || j == 7 || j == 14)) || (i == 7 && (j == 0 || j == 14)) || (i == 14 && (j == 0 || j == 7 || j == 14))) {
                board[i][j] = '*';
                cout << Bred << board[i][j] << " " << normal;
            }
            else if (((i == 0 || i == 14) && (j == 3 || j == 11)) || ((i == 2 || i == 12) && (j == 6 || j == 8)) || ((i == 3 || i == 11) && (j == 0 || j == 7 || j == 14)) || ((i == 6 || i == 8) && (j == 2 || j == 6 || j == 8 || j == 12)) || (i == 7 && (j == 3 || j == 11))) {
                board[i][j] = '*';
                cout << cyan << board[i][j] << " " << normal;
            }
            else if ((i == 1 || i == 13) && (j == 5 || j == 9) || ((i == 5 || i == 9) && (j == 1 || j == 5 || j == 9 || j == 13))) {
                board[i][j] = '*';
                cout << blue << board[i][j] << " " << normal;
            }
            else if (i == j || 14 - i == j) {
                board[i][j] = '*';
                cout << red << board[i][j] << " " << normal;
            }
            else {
                board[i][j] = '*';
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void boardPrint(char board[][15]) {
    for (int m = 0;m < 15;m++) {
        // rows
        for (int n = 0;n < 15;n++) {
            // columns
            // if statements to print out the multilpier tiles
            // outputs the index of the board to show any edits that either player has made
            if ((m == 0 && (n == 0 || n == 7 || n == 14)) || (m == 7 && (n == 0 || n == 14)) || (m == 14 && (n == 0 || n == 7 || n == 14))) {
                cout << Bred << board[m][n] << " " << normal;
            }
            else if (((m == 0 || m == 14) && (n == 3 || n == 11)) || ((m == 2 || m == 12) && (n == 6 || n == 8)) || ((m == 3 || m == 11) && (n == 0 || n == 7 || n == 14)) || ((m == 6 || m == 8) && (n == 2 || n == 6 || n == 8 || n == 12)) || (m == 7 && (n == 3 || n == 11))) {
                cout << cyan << board[m][n] << " " << normal;
            }
            else if ((m == 1 || m == 13) && (n == 5 || n == 9) || ((m == 5 || m == 9) && (n == 1 || n == 5 || n == 9 || n == 13))) {
                cout << blue << board[m][n] << " " << normal;
            }
            else if (m == n || 14 - m == n) {
                cout << red << board[m][n] << " " << normal;
            }
            else {
                cout << board[m][n] << " ";
            }
        }
        cout << endl;
    }
}

int numCheck(int ash) {
    while (true) {
        cin >> ash;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(80, '\n');
            cout << "Please input an integer.\n";
            continue;
        }
        break;
    }
    return ash;
}

void rules() {
    int theOption = 0;
    char theOption2;
    while (theOption != 4) {
        // rules menu loop
        system("cls");
        cout << R"(   ___  __  ____   ________
  / _ \/ / / / /  / __/ __/
 / , _/ /_/ / /__/ _/_\ \  
/_/|_|\____/____/___/___/  
                           
Welcome to the rules menu. What would you like to know about?

[1] General rules

[2] Gameplay flow

[3] Scoring

[4] Back to menu

)";
        theOption = numCheck(theOption);
        system("cls");
        // switch case to explain different rules of scrabble
        switch (theOption) {
            case 1: {
                // general rules menu
                cout << R"(  _____                      __
 / ___/__ ___  ___ _______ _/ /
/ (_ / -_) _ \/ -_) __/ _ `/ / 
\___/\__/_//_/\__/_/  \_,_/_/  

The game starts out with 98 tiles (normally 100 but there are no blank tiles in this version) and a board.
At the start, each player gets a hand with 7 tiles then the game begins. The game will end once there are either no more tiles in the bag or if there are no more possible moves
(in the event of the latter, an option to force quit the game will be present)
After this, the first turn will be forced to be played in the middle of the board, and all resulting plays have to be made off of another word

This program uses the sowpods dictionary: https://sowpods-scrabble-dictionary.updatestar.com/                              
)";
                cout << "Press a to go back to the rules menu" << endl;
                cin >> theOption2;
                while (theOption2 != 'a') {
                    cout << "Please input a (lowercase)" << endl;
                    cin >> theOption2;
                }
                break;
            }
            case 2: {
                // gameplay menu
                cout << R"(  _____                    __         
 / ___/__ ___ _  ___ ___  / /__ ___ __
/ (_ / _ `/  ' \/ -_) _ \/ / _ `/ // /
\___/\_,_/_/_/_/\__/ .__/_/\_,_/\_, / 
                  /_/          /___/

On any given turn, each player has the option to:

Play a word
 - Please type your words in UPPERCASE!
 - The user will type in a word with their given tiles, and the program will run a check to see if the word is valid and if the user has the tiles to make it
 - Then they will be prompted to choose a starting place (which needs to be inputted as a coordinate) and a direction for the word. 
 - If there are no words on the board the word must cross the middle.
 - If there are words on the board the word must intersect, so input a space where a word would intersect. Unfortunately you cannot do more then 1 intersection with an inputted word in this version.
 - This will end your turn.

Check the instructions again
 - In case if you wanted to read this again ;)

Check the dictionary
 - The user can type a word check if it is valid in the dictionary

Replace tiles
 - The user can choose a certain amount of tiles to replace from the existing tile bag
 - The program will prompt you to input either 1 or 0 7 times
 - Input 1 to replace the given tile and 0 to keep the given tile
 - This action ends your turn.

View the scores
 - This one is self-explanatory.

Force quit out of the game
 - In case if there are no availible moves or if you are bored of playing scrabble, this will end the game and tally the scores for each user. After, 2 more turns will happen and then the winner willbe decided

)";
                cout << "Press a to go back to the rules menu" << endl;
                cin >> theOption2;
                while (theOption2 != 'a') {
                    cout << "Please input a (lowercase)" << endl;
                    cin >> theOption2;
                }
                break;

            }
            case 3: {
                // scoring menu
                cout << R"(   ____             _          
  / __/______  ____(_)__  ___ _
 _\ \/ __/ _ \/ __/ / _ \/ _ `/
/___/\__/\___/_/ /_/_//_/\_, / 
                        /___/  

When a word is played, all of the letters that were played are counted and added to your point tally.
If you play all seven of your letters on the board, you get a BINGO, which is worth 50 additional points.
There are point multipliers across the screen too. They are:

)";
                cout << red << " Red" << normal << " - The value of your WORD is doubled" << "\n\n";

                cout << cyan << " Blue / cyan" << normal << " - The value of the LETTER on the tile is doubled" << "\n\n";

                cout << Bred << " Bright red " << normal << " - The value of your WORD is tripled" << "\n\n";

                cout << blue << " Dark blue" << normal << " - The value of the LETTER on the tile is tripled" << "\n\n";

                cout << R"(
Each individual value of your hand is displayed next to the letter. As a reminder, here are the values:

E, A, I, O, N, R, T, L, S, U - 1 point

D, G - 2 points 

B, C, M, P - 3 points

F, H, V, W, Y - 4 points

K - 5 points

J, X - 8 points

Q, Z - 10 points


Once the game ends, the player with the highest score wins. 
In this version, the rule to count another word when a letter is added onto it is not included, sorry. :/
)";
                cout << "Press a to go back to the rules menu" << endl;
                cin >> theOption2;
                while (theOption2 != 'a') {
                    cout << "Please input a (lowercase)" << endl;
                    cin >> theOption2;
                }
                break;
            }
            case 4: {
                // leave to whatever menu again
                break;
            }
            default: {
                cout << "Invalid." << endl;
                break;
            }
        }
    }

}

void dictionary() {
    char option;
    string theWord;
    string readFromText;
    bool isValidWord = false;
    cout << "Please input your word to check if it is valid or not:" << endl;
    cin.clear();
    getline(cin >> ws, theWord); // input word you want to verify
    ifstream Checking("dictionary.txt"); // open file
    while (getline(Checking, readFromText)) { // read the file line by line
        if (readFromText == theWord) {
            isValidWord = true; // if given word is equal to a word in the file
        }
    }
    Checking.close(); // close document
    if (isValidWord == true) {
        // if word is correct
        cout << "Your word is valid to use!" << endl;
    }
    else {
        // if word is incorrect
        cout << "You cannot use that as a word." << endl;
    }
    cout << "Press a to go back to the menu" << endl;
    cin >> option;
    while (option != 'a') {
        cout << "Please input a (lowercase)" << endl;
        cin >> option;
    }
    system("cls");
}

bool wordCheck(string givenWord, bool& valid) {
    string textRead;
    ifstream Checker("dictionary.txt"); // open document
    while (getline(Checker, textRead)) {
        if (textRead == givenWord) {
            valid = true; // if word is equal to a word in the document
        }
    }
    Checker.close(); // close document
    return valid;
}
