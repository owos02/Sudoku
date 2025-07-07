//
// Created by Oliver W. on 4/28/25.
//

#include "Application.h"

Sudoku::Application::Application( ) {
    curl_global_init( CURL_GLOBAL_DEFAULT );
    _curl = curl_easy_init( );
    resetFields( );
}

void Sudoku::Application::resetFields( ) {
    for ( auto &row : _field ) {
        row.fill( 0 );
    }
    for ( auto &row : _solution ) {
        row.fill( 0 );
    }
    for ( auto &row : _original ) {
        row.fill( 0 );
    }
    _resetFields = false;
}

void Sudoku::Application::run( ) {
    Gui::show( );
    update( );
}

void Sudoku::Application::generateSudoku( ) {
    ApiHandler::execute( static_cast< APIs >(_selectedAPI) );
    std::ranges::transform( _sudokuDifficulty, _sudokuDifficulty.begin( ), toupper );
}

Sudoku::Application::~Application( ) {
    curl_easy_cleanup( _curl );
    curl_global_cleanup( );
}

void Sudoku::Application::update( ) {
    if ( _generateSudoku ) {
        generateSudoku( );
        _generateSudoku = false;
    }
    if ( _checkSudoku ) {
        _isSolved    = Algorithm::fieldConsistency( _field );
        _checkSudoku = false;
    }
    if ( _solveSudoku ) {
        switch ( static_cast< Algorithms >(_algorithmSelectedIndex) ) {
            case Algorithms::BACKTRACE:
                deploySolvingAlgorithm( Algorithms::BACKTRACE );
                break;
            default:;
        }
        _solveSudoku = false;
    }
    if ( _resetFields )
        resetFields( );
    if ( _loadPuzzle ) {
        resetFields( );
        switch ( static_cast< LoadSudoku >(_sudokusSelectedIndex) ) {
            default:
            case LoadSudoku::NONE:
                break;
            case LoadSudoku::ANTI_BACKTRACE:
                _original = _sudoku_anti_backtrace;
                break;
        }
        _loadPuzzle = false;
    }
}

void Sudoku::Application::deploySolvingAlgorithm( const Algorithms algorithm ) {
    std::thread solver;
    switch ( algorithm ) {
        default:
        case Algorithms::BACKTRACE:
            solver = std::thread(
                Algorithm::backtrace,
                std::ref( _field ), 0, 0
            );
            break;
    }
    solver.detach( );
}
