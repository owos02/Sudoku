//
// Created by Ara on 02.05.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <array>

// "FIXME Rename File "

namespace Sudoku {
    inline std::array<std::array<int, 9>, 9> _field;
    inline std::array<std::array<int, 9>, 9> _solution;
    inline std::string _sudokuDifficulty;
    inline const char *_solvingAlgorithms[2] = {"Backtrace", "Placeholder"};
    inline int _algorithmSelectedIndex = 0;
    inline bool _generateSudoku = true;
    namespace Settings {
    }
}

#endif //SETTINGS_H
