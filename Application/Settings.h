//
// Created by Ara on 02.05.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include <array>
#include <imgui.h>
#include <string>
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

    enum class Mode:int {
        SOLVING,
        CREATE
    };

    enum class LoadSudoku:int {
        NONE,
        ANTI_BACKTRACE,
        PLACEHOLDER
    };

    inline CURL *                                _curl;
    inline std::array< std::array< int, 9 >, 9 > _original;
    inline std::array< std::array< int, 9 >, 9 > _field;
    inline std::array< std::array< int, 9 >, 9 > _solution;
    inline std::string                           _sudokuDifficulty          = "Random";
    inline const char *                          _difficulties[ 4 ]         = { "Random", "Easy", "Medium", "Hard" };
    inline int                                   _difficultiesSelectedIndex = 0;
    inline const char *                          _solvingAlgorithms[ 2 ]    = { "Backtrace", "Placeholder" };
    inline int                                   _algorithmSelectedIndex    = 0;
    inline bool                                  _generateSudoku            = false;
    inline bool                                  _solveSudoku               = false;
    inline bool                                  _breakSolving              = false;
    inline bool                                  _checkSudoku               = false;
    inline bool                                  _enableShowWebSolution     = true;
    inline bool                                  _isSolved                  = false;
    inline bool                                  _invalidPuzzle             = false;
    inline int                                   _selectedAPI               = 0;
    inline int                                   _solvingDelay              = 0;
    inline int                                   _mode                      = 0;
    inline bool                                  _resetFields               = false;
    inline bool                                  _loadPuzzle                = false;

    inline int         _sudokusSelectedIndex = 0;
    inline const char *_exampleSudokus[ 3 ]  = { "Choose", "Anti Backtrace Sudoku", "Placeholder" };


    // For coloring current solving cell
    inline int  _visualiseX = -1;
    inline int  _visualiseY = -1;
    inline bool _notAdvance = true;

    enum class APIs:int {
        YDS,
        DOSUKU
    };

    namespace Settings { }

    namespace Colors {
        inline constexpr auto gameBoardWhite = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f );
        inline constexpr auto gameBoardGrey  = ImVec4( 0.85f, 0.85f, 0.85f, 1.0f );
        inline constexpr auto gameBoardText  = ImVec4( 0, 0, 0, 1.0f );

        inline constexpr auto transparent = ImVec4( 0, 0, 0, 0.0f );


        // Colors from Catppuccin Macchiato
        inline constexpr auto overlay0   = ImVec4( 110.0f / 255, 115.0f / 255, 141.0f / 255, 1.0 );
        inline constexpr auto warningRed = ImVec4( 237.0f / 255, 135.0f / 255, 150.0f / 255, 1.0 );
        inline constexpr auto red        = ImVec4( 210.0f / 255, 15.0f / 255, 57.0f / 255, 1.0 );
        inline constexpr auto green      = ImVec4( 64.0f / 255, 160.0f / 255, 43.0f / 255, 1.0 );
        inline constexpr auto blue       = ImVec4( 138.0f / 255, 173.0f / 255, 244.0f / 255, 1.0 );
        inline constexpr auto mauve      = ImVec4( 198.0f / 255, 160.0f / 255, 246.0f / 255, 1.0 );
    }

#pragma region Sudokus
    inline std::array< std::array< int, 9 >, 9 >
    _sudoku_anti_backtrace = {
        {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 3, 0, 8, 5 },
            { 0, 0, 1, 0, 2, 0, 0, 0, 0 },
            { 0, 0, 0, 5, 0, 7, 0, 0, 0 },
            { 0, 0, 4, 0, 0, 0, 1, 0, 0 },
            { 0, 9, 0, 0, 0, 0, 0, 0, 0 },
            { 5, 0, 0, 0, 0, 0, 0, 7, 3 },
            { 0, 0, 2, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 4, 0, 0, 0, 9 }
        }};
#pragma endregion

    }

#endif //SETTINGS_H
