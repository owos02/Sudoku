//
// Created by Ara on 02.05.2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <algorithm>
#include <array>
#include <functional>
#include <map>

#include "Settings.h"

namespace Sudoku {
    class Algorithm {
        using field = std::array<std::array<int, 9>, 9> &;

        /* The rules of Sudoku
         *
         * 1. Only use numbers from 1-9;
         * 2. No repeating numbers in a row or column
         * 3. No repeating numbers in a 3x3 designated block
         **/

    public:
        static std::map<int, int> generateEmptyMap() {
            std::map<int, int> tmp;
            for (int i = 0; i <= 9; i++)
                tmp.insert(std::pair(i, 0));
            tmp[0] = -99;
            return tmp;
        }

        static bool fieldConsistency(const field area) {
            //Check if all cells contain valid numbers
            for (auto row: area) {
                for (const int cell: row) {
                    if (cell == 0) return false;
                }
            }

            //Check Rows
            for (const auto &row: area) {
                auto rowsCheck = generateEmptyMap();
                for (const auto &cell: row) {
                    if (rowsCheck[cell] > 0)
                        return false;
                    rowsCheck[cell] = 1;
                }
            }

            //Check Columns
            for (int cellIndex = 0; cellIndex < 9; cellIndex++) {
                auto columnsCheck = generateEmptyMap();
                for (int rowIndex = 0; rowIndex < 9; rowIndex++) {
                    if (columnsCheck.at(area[rowIndex][cellIndex]) > 0)
                        return false;
                    columnsCheck[area[rowIndex][cellIndex]] = 1;
                }
            }

            //Check Every Block
            for (int blockVerticalIndex = 0; blockVerticalIndex < 3; blockVerticalIndex++) {
                for (int blockHorizontalIndex = 0; blockHorizontalIndex < 3; blockHorizontalIndex++) {
                    auto blockCheck = generateEmptyMap();
                    for (int rowIndex = 3 * blockVerticalIndex; rowIndex < 3 * blockVerticalIndex + 3; rowIndex++) {
                        for (int cellIndex = 3 * blockHorizontalIndex; cellIndex < 3 * blockHorizontalIndex + 3;
                             cellIndex++) {
                            if (blockCheck.at(area[rowIndex][cellIndex]) > 0)
                                return false;
                            blockCheck[area[rowIndex][cellIndex]] = 1;
                        }
                    }
                }
            }
            return true;
        }

        static bool sanityCheck(const field area, const int row, const int column, const int value) {
            // Check X axis

            for (int i = 0; i < 9; i++) {
                if (value == area[i][column]) {
                    return false;
                }
            }
            // Check X axis
            for (int i = 0; i < 9; i++) {
                if (value == area[row][i]) {
                    return false;
                }
            }
            const int yLimit = ((row / 3) * 3), xLimit = ((column / 3) * 3);
            for (int y = yLimit; y < yLimit + 3; y++) {
                for (int x = xLimit ; x < xLimit + 3; x++) {
                    if (value == area[y][x]) {
                        return false;
                    }
                }
            }
            return true;
        }

        static void startAlgorithm([[maybe_unused]] const Algorithm selected) {
            // switch (selected) {
            //     default:
            //         break;
            // }
        }

        static bool backtrace(field& area, const int row, const int column) {
            //Calculate next row
            int nextRow = row, nextColumn = column + 1;
            if (nextColumn % 9 == 0) {
                nextColumn = 0;
                nextRow++;
            }

            //Check if last row & cell is being used
            if (row == 8 && column == 8) { return true; }

            //Cell has number
            if (_original[row][column] != 0) {
                return backtrace(area, nextRow, nextColumn);
            }

            //https://pencilprogrammer.com/algorithms/sudoku-using-backtracking/
            for (int nextNumber = 1; nextNumber <= 9; nextNumber++) {
                area[row][column] = nextNumber;
                if (isValid()) {
                    //TODO
                    if (backtrace(area, nextRow, nextColumn));
                }
            }


            return backtrace(area, nextRow, nextColumn );
            
        }
    };
}


#endif //ALGORITHM_H
