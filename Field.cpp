//
// Created by piotr on 02.05.2022.
//

#include "Sudokulib.h"

int Field::getValue() const {
    return value;
}

void Field::setValue(int value) {
    Field::value = value;
}

bool Field::isGeneratedFunction() const {
    return isGenerated;
}

void Field::setIsGenerated(bool isGenerated) {
    Field::isGenerated = isGenerated;
}