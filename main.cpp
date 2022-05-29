#include "Sudokulib.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <unistd.h>


using namespace std;


int main() {

    cout << "|||||||||||HELLO IN MY GAME - SUDOKU|||||||||||" << endl;
    int playAgain = 0;

    do {
        cout << "|||||||||||CHOOSE THE DIFFICULTY LEVEL|||||||||||" << endl;
        string input;
        cout << "TYPE 'a' FOR EASY MODE" << endl << "TYPE 'b' FOR NORMAL MODE" << endl << "TYPE 'c' FOR HARD MODE"
             << endl;
        cin >> input;
        while (input != "a" && input != "b" && input != "c") {
            cout << "TYPE 'a', 'b', or 'c'" << endl;
            cin >> input;
        }

        cout << "Enter 'stop' anytime you want to exit." << endl;
        if (input == "a") {
            cout << "   ||||||EASY MODE||||||" << endl;
            EasyMode game;
            game.playSudoku();
        } else if (input == "b") {
            cout << "   ||||||NORMAL MODE||||||" << endl;
            NormalMode game;
            game.playSudoku();
        } else if (input == "c") {
            cout << "   |||||||HARD MODE|||||||" << endl;
            HardMode game;
            game.playSudoku();
        }
        cout << "Do you want to play again?\nEnter 1 if yes, enter anything else if no" << endl;
        cin >> playAgain;

    } while(playAgain == 1);
    return 0;
}
