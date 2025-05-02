//
// Created by Ara on 02.05.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <array>
#include <curl/curl.h>
// "FIXME Rename File "

namespace Sudoku {
    enum class Difficulty:int {
        RANDOM,
        EASY,
        MEDIUM,
        HARD
    };

    inline CURL *_curl;
    inline std::array<std::array<int, 9>, 9> _field;
    inline std::array<std::array<int, 9>, 9> _solution;
    inline std::string _sudokuDifficulty;
    inline const char *_difficulties[4] = {"Random", "Easy", "Medium", "Hard"};
    inline int _difficultiesSelectedIndex = 0;
    inline const char *_solvingAlgorithms[2] = {"Backtrace", "Placeholder"};
    inline int _algorithmSelectedIndex = 0;
    inline bool _generateSudoku = false;

    namespace Settings {
    }
    namespace Colors {
        inline auto warningRed = ImVec4(237.0f / 255,135.0f / 255, 150.0f / 255,1.0);

    }
}

#endif //SETTINGS_H
