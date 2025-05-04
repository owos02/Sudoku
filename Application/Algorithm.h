//
// Created by Ara on 02.05.2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <algorithm>
#include <array>
#include <map>
#include <print>

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
                tmp.insert(std::pair<int, int>(i, 0));
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

        static bool softChecks(const field area) {
            //Check Rows
            for (const auto &row: area) {
                auto rowsCheck = generateEmptyMap();
                for (const auto &cell: row) {
                    if (rowsCheck[cell] > 0 && cell != 0)
                        return false;
                    rowsCheck[cell] = 1;
                }
            }

            //Check Columns
            for (int cellIndex = 0; cellIndex < 9; cellIndex++) {
                auto columnsCheck = generateEmptyMap();
                for (int rowIndex = 0; rowIndex < 9; rowIndex++) {
                    if (columnsCheck.at(area[rowIndex][cellIndex]) > 0 && area[rowIndex][cellIndex] != 0)
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
                            if (blockCheck.at(area[rowIndex][cellIndex]) > 0 && area[rowIndex][cellIndex] != 0)
                                return false;
                            blockCheck[area[rowIndex][cellIndex]] = 1;
                        }
                    }
                }
            }
            return true;
        }

        static void backtrace(field area) {

            // Do backtrace
        }

    };
}


#endif //ALGORITHM_H
