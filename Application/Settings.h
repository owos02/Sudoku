//
// Created by Ara on 02.05.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <array>
#include <curl/curl.h>
// "FIXME Rename File "

namespace Sudoku {
    enum class Difficulties:int {
        RANDOM,
        EASY,
        MEDIUM,
        HARD
    };
    enum class Algorithms:int {
        BACKTRACE,
        PLACEHOLDER
    };

    inline CURL *_curl;
    inline std::array<std::array<int, 9>, 9> _original;
    inline std::array<std::array<int, 9>, 9> _field;
    inline std::array<std::array<int, 9>, 9> _solution;
    inline std::string _sudokuDifficulty = "Random";
    inline const char *_difficulties[4] = {"Random", "Easy", "Medium", "Hard"};
    inline int _difficultiesSelectedIndex = 0;
    inline const char *_solvingAlgorithms[2] = {"Backtrace", "Placeholder"};
    inline int _algorithmSelectedIndex = 0;
    inline bool _generateSudoku = false;
    inline bool _solveSudoku = false;
    inline bool _checkSudoku = false;
    inline bool _isSolved = false;
    inline int _selectedAPI = 0;
    enum class APIs:int {
        YDS,
        DOSUKU
    };

    namespace Settings {
    }
    namespace Colors {
        inline constexpr auto warningRed = ImVec4(237.0f / 255,135.0f / 255, 150.0f / 255,1.0);
        inline constexpr auto red = ImVec4(210.0f / 255,15.0f / 255, 57.0f / 255,1.0);
        inline constexpr auto green = ImVec4(64.0f / 255,160.0f / 255, 43.0f / 255,1.0);

    }
}

#endif //SETTINGS_H
