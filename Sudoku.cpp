//
// Created by piotr on 28.04.2022.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "Sudokulib.h"



using namespace std;



SudokuGenerator::SudokuGenerator(int difficultyLevel){ // SudokuGenerator constructor

    mode = difficultyLevel;
    N = 9;
    Field fields[9][9];
    double temp = sqrt(N);

    SRN = (int) round(temp);
    first = true;

    generateSudoku();
}

SudokuGenerator::~SudokuGenerator() {
    cout << "Destroying Sudoku" << endl;
}

SudokuGenerator::SudokuGenerator(const SudokuGenerator &sudoku) {

    mode = sudoku.mode;
    N = sudoku.N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fields[i][j] = sudoku.fields[i][j];
        }
    }
    SRN = sudoku.SRN;
    first = sudoku.first;
    generateSudoku();
}

int SudokuGenerator::getElement(int i, int j) {

    if(i < 0 || i > 8){
        return -1;
    }
    if(j < 0 || j > 8){
        return -1;
    }
    return fields[i][j].getValue();
}




void SudokuGenerator::generateSudoku() {
    zeroSudokuBoard();
    fillValues();
    removeKElements();
    setToGenerated();
}

void SudokuGenerator::setToGenerated() {

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(fields[i][j].getValue() != 0){
                fields[i][j].setIsGenerated(true);
            }
        }
    }


}

void SudokuGenerator::zeroSudokuBoard() { // zeruje tablice
    int counter = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fields[i][j].setValue(0);
            fields[i][j].setIsGenerated(false);
        }
    }

}

void SudokuGenerator::fillValues() {

    fillDiagonal();

    fillRemaining(0, SRN);

}


void SudokuGenerator::fillDiagonal(){
    for(int i = 0; i < N; i = i + 3){
        fillBox(i, i);
    }
}

void SudokuGenerator::fillBox(int row, int col) {

    int number;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            do{
                number = getRandomNumber(1, 9);
            }while(!unUsedInBox(number, row, col));

            fields[row+i][col+j].setValue(number);
        }
    }

}

bool SudokuGenerator::unUsedInBox(int number, int row, int col) {

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(fields[row + i][col + j].getValue() == number){
                return false;
            }
        }
    }
    return true;
}

int SudokuGenerator::getRandomNumber(int min, int max) {

    if(first){
        srand(time(NULL));
        first = false;
    }

    return min + rand() % max;

}

bool SudokuGenerator::fillRemaining(int i, int j) {

    if (j>=N && i<N-1)
    {
        i = i + 1;
        j = 0;
    }
    if (i>=N && j>=N)
        return true;

    if (i < SRN)
    {
        if (j < SRN)
            j = SRN;
    }
    else if (i < N-SRN)
    {
        if (j==(int)(i/SRN)*SRN)
            j =  j + SRN;
    }
    else
    {
        if (j == N-SRN)
        {
            i = i + 1;
            j = 0;
            if (i>=N)
                return true;
        }
    }

    for (int num = 1; num<=N; num++)
    {
        if (checkIfSafe(num, i, j))
        {
            fields[i][j].setValue(num);
            if (fillRemaining(i, j+1))
                return true;

            fields[i][j].setValue(0);
        }
    }
    return false;
}



bool SudokuGenerator::checkIfSafe(int number, int i, int j) {
    return (unUsedInRow(i, number) &&
            unUsedInColumn(j, number) &&
            unUsedInBox(number, i - i%3, j - j%3));
}

bool SudokuGenerator::unUsedInRow(int i, int number) {

    for(int j = 0; j < N; j++){
        if(fields[i][j].getValue() == number){
            return false;
        }
    }
    return true;
}

bool SudokuGenerator::unUsedInColumn(int j, int number) {

    for(int i = 0; i < N; i++){
        if(fields[i][j].getValue() == number){
            return false;
        }
    }
    return true;
}

//deleting elementsToDelete number of elements



void SudokuGenerator::removeKElements() {

    int counter;

    if (mode == 1){
        counter = getRandomNumber(38, 10);
    } else if(mode == 2){
        counter = getRandomNumber(48, 4);
    } else if(mode == 3){
        counter = getRandomNumber(56, 2);
    } else {
        cout << "THIS MODE IS NOT AVAILABLE" << endl;
        return;
    }

    while(counter != 0){
        int i = getRandomNumber(0, 9);
        int j = getRandomNumber(0, 9);

        if(fields[i][j].getValue() != 0) {
            fields[i][j].setValue(0);
            counter--;
        }
    }


}

void SudokuGenerator::printSudoku() {
    cout << "-------------------------" << endl;

    for (int i = 0; i < N; i++){
        if(i == 3 || i == 6){
            cout << "-------------------------" << endl;
        }
        for(int j = 0; j < N; j++){
            if(j == 0 || j == 3 || j == 6){
                cout << "| ";
            }
            if(fields[i][j].getValue() == 0){
                cout << "x ";
            } else {
                cout << fields[i][j].getValue() << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << "-------------------------" << endl;

}


int SudokuGenerator::getN() const {
    return N;
}

bool SudokuGenerator::changeNumber(int number, int i, int j) {

    i--;
    j--;

    if(number == 0 && !fields[i][j].isGeneratedFunction()){
        fields[i][j].setValue(number);
        return true;
    }

    if(number < 1 || number > 9){
        cout << "||||||CHOOSE NUMBER FROM 1 TO 9||||||" << endl;
        return false;
    }

    if(fields[i][j].isGeneratedFunction()){
        cout << "||||||YOU CANNOT CHANGE THIS NUMBER, IT WAS GENERATED||||||" << endl;
        return false;
    }

    if(checkIfSafe(number, i, j)){
        fields[i][j].setValue(number);
        return true;
    }

    cout << "||||||CANNOT CHANGE THIS NUMBER, LOOK ROWS COLUMNS AND BOXES||||||" << endl;
    return false;

}

void SudokuGenerator::playSudoku() {

    boolean solved = true;
    while(!isDone()) {
        string number;
        string i;
        string j;
        printSudoku();
        cout << "ENTER NUMBER, ROW AND COLUMN YOU WANT TO CHANGE" << endl;
        cout << "column = " << endl;
        cin >> j;
        if(j == "stop"){
            solved = false;
            break;
        }
        cout << "row = " << endl;
        cin >> i;
        if(i == "stop"){
            solved = false;
            break;
        }
        cout << "number = " << endl;
        cin >> number;
        if(number == "stop"){
            solved = false;
            break;
        }

        int iValue, jValue, numberValue;

        try{
            iValue = stoi(i);
        }
        catch(invalid_argument &e){
            continue;
        }
        catch (out_of_range& e){
            continue;
        }

        try{
            numberValue = stoi(number);
        }
        catch(invalid_argument &e){
            continue;
        }
        catch (out_of_range& e){
            continue;
        }

        try{
            jValue = stoi(j);
        }
        catch(invalid_argument &e){
            continue;
        }
        catch (out_of_range& e){
            continue;
        }

        if(numberValue < 1 || numberValue > 9){
            cout << "number has to be from 1 do 9" << endl;
            continue;
        }
        if(iValue < 1 || iValue > 9){
            cout << "row index has to be from 1 to 9" << endl;
            continue;
        }
        if(jValue < 1 || jValue > 9){
            cout << "column index has to be from 1 to 9" << endl;
            continue;
        }

        changeNumber(numberValue, iValue, jValue);
    }

    if(solved) {
        printSudoku();
        cout << "||||||CONGRATULATIONS, YOU HAVE SOLVED SUDOKU||||||" << endl;
    } else {
        cout << "||||||TRY ANOTHER LEVEL||||||" << endl;
    }

}

bool SudokuGenerator::isBoxCorrect(int rowStart, int columnStart) {

    for(int number = 1; number <= 9; number++) {
        int counter = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(fields[i][j].getValue() == 0){
                    return false;
                }
                if(fields[rowStart + i][columnStart + j].getValue() == number){
                    counter++;
                }
                if (counter > 1){
                    return false;
                }
            }
        }
    }

    return true;
}

bool SudokuGenerator::isBoxesCorrect() {
    int rowStart = 0;
    int columnStart = 0;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    rowStart = 3;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    rowStart = 6;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    columnStart = 3;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    columnStart = 6;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    rowStart = 3;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    columnStart = 3;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    rowStart = 0;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }
    columnStart = 6;
    if(!isBoxCorrect(rowStart, columnStart)){
        return false;
    }

    return true;
}

bool SudokuGenerator::isRowsCorrect() {

    for(int number = 1; number <= 9; number ++){
        for(int i = 0; i < N; i++){
            int counter = 0;
            for(int j = 0; j < N; j++){
                if(fields[i][j].getValue() == 0){
                    return false;
                }
                if(fields[i][j].getValue() == number){
                    counter++;
                }
                if(counter > 1){
                    return false;
                }
            }
        }
    }

    return true;
}

void friendFunction(SudokuGenerator &sudoku){
    cout << "Hello in friend function" << endl;
    cout << "Value: " << sudoku.getElement(4, 4);
    cout << "WOW IT WORKS" << endl;
}

bool SudokuGenerator::isColumnsCorrect() {

    for(int number = 1; number <= 9; number ++){
        for(int i = 0; i < N; i++){
            int counter = 0;
            for(int j = 0; j < N; j++){
                if(fields[j][i].getValue() == 0){
                    return false;
                }
                if(fields[j][i].getValue() == number){
                    counter++;
                }
                if(counter > 1){
                    return false;
                }
            }
        }
    }

    return true;
}

bool SudokuGenerator::isDone() {
    return (isBoxesCorrect() && isColumnsCorrect() && isRowsCorrect());
}

EasyMode::EasyMode() : SudokuGenerator(1) {


}

EasyMode::~EasyMode() {
    cout << "Destroying EasyMode Sudoku" << endl;

}

EasyMode EasyMode::operator+(const EasyMode &obj) {
    EasyMode tempObj;
    cout << "What can I do :((" << endl;

    return tempObj;
}


void EasyMode::printSudoku() {

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << " | 1 2 3 | 4 5 6 | 7 8 9 |" << endl;
    cout << "-------------------------" << endl;

    for (int i = 0; i < getN(); i++){
        if(i == 3 || i == 6){
            cout << "-------------------------" << endl;
        }
        for(int j = 0; j < getN(); j++){
            if(j == 0){
                cout << i + 1;
            }
            if(j == 0 || j == 3 || j == 6){
                cout << "| ";
            }
            if(fields[i][j].getValue() == 0){
                SetConsoleTextAttribute(h, 8);
                cout << "x ";
                SetConsoleTextAttribute(h, 7);
            } else {
                if(fields[i][j].isGeneratedFunction()){
                    SetConsoleTextAttribute(h, 6);
                }
                cout << fields[i][j].getValue() << " ";
                SetConsoleTextAttribute(h, 7);
            }
        }
        cout << "|" << endl;
    }

    cout << "-------------------------" << endl;
}



NormalMode::NormalMode() : SudokuGenerator(2) {
}

NormalMode::~NormalMode() {
    cout << "Destroying normal mode" << endl;
}


void NormalMode::printSudoku() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << " | 1 2 3 | 4 5 6 | 7 8 9 |" << endl;
    cout << "-------------------------" << endl;

    for (int i = 0; i < getN(); i++){
        if(i == 3 || i == 6){
            cout << "-------------------------" << endl;
        }
        for(int j = 0; j < getN(); j++){
            if(j == 0){
                cout << i + 1;
            }
            if(j == 0 || j == 3 || j == 6){
                cout << "| ";
            }
            if(fields[i][j].getValue() == 0){
                SetConsoleTextAttribute(h, 8);
                cout << "x ";
                SetConsoleTextAttribute(h, 7);
            } else {
                if(fields[i][j].isGeneratedFunction()){
                    SetConsoleTextAttribute(h, 13);
                } else {
                    SetConsoleTextAttribute(h, 11);
                }
                cout << fields[i][j].getValue() << " ";
                SetConsoleTextAttribute(h, 7);
            }
        }
        cout << "|" << endl;
    }

    cout << "-------------------------" << endl;
}

HardMode::HardMode() : SudokuGenerator(3) {
}

HardMode::~HardMode() {
    cout << "Destroying hard mode" << endl;
}


void HardMode::printSudoku() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << " | 1 2 3 | 4 5 6 | 7 8 9 |" << endl;
    cout << "-------------------------" << endl;

    for (int i = 0; i < getN(); i++) {
        if (i == 3 || i == 6) {
            cout << "-------------------------" << endl;
        }
        for (int j = 0; j < getN(); j++) {
            if (j == 0) {
                cout << i + 1;
            }
            if (j == 0 || j == 3 || j == 6) {
                cout << "| ";
            }
            if (fields[i][j].getValue() == 0) {
                SetConsoleTextAttribute(h, 8);
                cout << "x ";
                SetConsoleTextAttribute(h, 7);
            } else {
                if (fields[i][j].isGeneratedFunction()) {
                    SetConsoleTextAttribute(h, 12);
                } else {
                    SetConsoleTextAttribute(h, 14);
                }
                cout << fields[i][j].getValue() << " ";
                SetConsoleTextAttribute(h, 7);
            }
        }
        cout << "|" << endl;
    }

    cout << "-------------------------" << endl;
}


