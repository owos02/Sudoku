//
// Created by Oliver W. on 02.05.2025.
//

#include <array>
#include <imgui.h>
#include <string>
#include <curl/curl.h>

namespace Sudoku {
    std::array< std::array< int, 9 >, 9 > _original;
    std::array< std::array< int, 9 >, 9 > _field;
    std::array< std::array< int, 9 >, 9 > _solution;

    CURL *      _curl;
    std::string _sudokuDifficulty          = "Random";
    const char *_difficulties[ 4 ]         = { "Random", "Easy", "Medium", "Hard" };
    int         _difficultiesSelectedIndex = 0;
    const char *_solvingAlgorithms[ 2 ]    = { "Backtrace", "Placeholder" };
    int         _algorithmSelectedIndex    = 0;
    bool        _generateSudoku            = false;
    bool        _solveSudoku               = false;
    bool        _breakSolving              = false;
    bool        _checkSudoku               = false;
    bool        _enableShowWebSolution     = true;
    bool        _isSolved                  = false;
    bool        _invalidPuzzle             = false;
    int         _selectedAPI               = 0;
    int         _solvingDelay              = 0;
    int         _mode                      = 0;
    bool        _resetFields               = false;
    bool        _loadPuzzle                = false;

    int         _sudokusSelectedIndex = 0;
    const char *_exampleSudokus[ 3 ]  = { "Choose", "Anti Backtrace Sudoku", "Placeholder" };

    // For coloring current solving cell
    int  _visualiseX = -1;
    int  _visualiseY = -1;
    bool _notAdvance = true;

    namespace Colors {
        auto gameBoardWhite = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f );
        auto gameBoardGrey  = ImVec4( 0.85f, 0.85f, 0.85f, 1.0f );
        auto gameBoardText  = ImVec4( 0, 0, 0, 1.0f );

        auto transparent = ImVec4( 0, 0, 0, 0.0f );

        // Colors from Catppuccin Macchiato
        auto overlay0   = ImVec4( 110.0f / 255, 115.0f / 255, 141.0f / 255, 1.0 );
        auto warningRed = ImVec4( 237.0f / 255, 135.0f / 255, 150.0f / 255, 1.0 );
        auto red        = ImVec4( 210.0f / 255, 15.0f / 255, 57.0f / 255, 1.0 );
        auto green      = ImVec4( 64.0f / 255, 160.0f / 255, 43.0f / 255, 1.0 );
        auto blue       = ImVec4( 138.0f / 255, 173.0f / 255, 244.0f / 255, 1.0 );
        auto mauve      = ImVec4( 198.0f / 255, 160.0f / 255, 246.0f / 255, 1.0 );
    }

#pragma region Sudokus
    std::array< std::array< int, 9 >, 9 >
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
        }
    };
#pragma endregion
}
