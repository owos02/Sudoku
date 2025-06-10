//
// Created by Ara on 02.05.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <array>
#include <imgui.h>
#include <string>
#include <curl/curl.h>

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

    enum class Mode:int {
        SOLVING,
        CREATE
    };

    enum class LoadSudoku:int {
        NONE,
        ANTI_BACKTRACE,
        PLACEHOLDER
    };

    enum class APIs:int {
        YDS,
        DOSUKU
    };

    extern std::array< std::array< int, 9 >, 9 > _original;
    extern std::array< std::array< int, 9 >, 9 > _field;
    extern std::array< std::array< int, 9 >, 9 > _solution;

    extern CURL *      _curl;
    extern std::string _sudokuDifficulty;
    extern const char *_difficulties[ 4 ];
    extern int         _difficultiesSelectedIndex;
    extern const char *_solvingAlgorithms[ 2 ];
    extern int         _algorithmSelectedIndex;
    extern bool        _generateSudoku;
    extern bool        _solveSudoku;
    extern bool        _breakSolving;
    extern bool        _checkSudoku;
    extern bool        _enableShowWebSolution;
    extern bool        _isSolved;
    extern bool        _invalidPuzzle;
    extern int         _selectedAPI;
    extern int         _solvingDelay;
    extern int         _mode;
    extern bool        _resetFields;
    extern bool        _loadPuzzle;

    extern int         _sudokusSelectedIndex;
    extern const char *_exampleSudokus[ 3 ];

    // For coloring current solving cell
    extern int  _visualiseX;
    extern int  _visualiseY;
    extern bool _notAdvance;


    namespace Colors {
        extern ImVec4 gameBoardWhite;
        extern ImVec4 gameBoardGrey;
        extern ImVec4 gameBoardText;

        extern ImVec4 transparent;

        // Colors from Catppuccin Macchiato
        extern ImVec4 overlay0;
        extern ImVec4 warningRed;
        extern ImVec4 red;
        extern ImVec4 green;
        extern ImVec4 blue;
        extern ImVec4 mauve;
    }

#pragma region Sudokus
    extern std::array< std::array< int, 9 >, 9 > _sudoku_anti_backtrace;
#pragma endregion
}
#endif //SETTINGS_H
