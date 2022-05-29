//
// Created by piotr on 03.05.2022.
//

#ifndef PROJECT_SUDOKULIB_H
#define PROJECT_SUDOKULIB_H

class Field{
private:
    int value = 0;
    bool isGenerated = false;
public:
    int getValue() const;

    void setValue(int value);

    bool isGeneratedFunction() const;

    void setIsGenerated(bool isGenerated);
};

class SudokuGenerator {

    friend void friendFunction(SudokuGenerator &sudoku);
public:
    SudokuGenerator(int difficultyLevel);
    SudokuGenerator(const SudokuGenerator& sudoku);
    ~SudokuGenerator();
    void playSudoku();
    int getElement(int i, int j);

protected:
    int getN() const;
    Field fields[9][9];
    bool changeNumber(int number, int i, int j);
    virtual void printSudoku();

private:
    //to play sudoku
    bool isDone();
    bool isBoxesCorrect();
    bool isBoxCorrect(int rowStart, int columnStart);
    bool isRowsCorrect();
    bool isColumnsCorrect();

    void generateSudoku();
    // setting generated
    void setToGenerated();
    // deleting k number of elements
    void removeKElements();
    // generating whole sudoku complete
    void fillValues();
    void zeroSudokuBoard();
    void fillDiagonal();
    void fillBox(int row, int col);
    bool fillRemaining(int i, int j);
    //-------------------------------------
    // checking if lines are good
    bool unUsedInBox(int number, int row, int col);
    bool checkIfSafe(int number, int i, int j);
    bool unUsedInColumn(int j, int number);
    bool unUsedInRow(int i, int number);
    //-------------------------------------
    int getRandomNumber(int min, int max);

    int N;
    int SRN; // square root of n
    bool first;
    int mode;


};


class EasyMode : public SudokuGenerator{
public:
    EasyMode();
   ~EasyMode();
    EasyMode operator + (EasyMode const & obj);
    void printSudoku() override;
private:


};

class NormalMode : public SudokuGenerator{
public:
    NormalMode();
    ~NormalMode();
    void printSudoku() override;

private:

};

class HardMode : public SudokuGenerator{
public:
    HardMode();
    ~HardMode();
    void printSudoku() override;

private:

};


#endif //PROJECT_SUDOKULIB_H
