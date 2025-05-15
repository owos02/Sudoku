//
// Created by Oliver W. on 4/28/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <array>
#include <algorithm>
#include <string>
#include <random>
#include <SDL.h>
#include <thread>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "Algorithm.h"
#include "Gui.h"
#include "Settings.h"
#include "ApiHandler.h"

namespace Sudoku {
    class Application {
    public:
        Application( ) {
            curl_global_init( CURL_GLOBAL_DEFAULT );
            _curl = curl_easy_init( );
            Gui::setStyling( );
            resetFields( );
        }

        static void resetFields( ) {
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

        static void run( ) {
            Gui::show( );
            update( );
        }


        static void generateSudoku( ) {
            ApiHandler::execute( static_cast< APIs >( _selectedAPI ) );
            std::ranges::transform( _sudokuDifficulty, _sudokuDifficulty.begin( ), toupper );
        }

        ~Application( ) {
            curl_easy_cleanup( _curl );
            curl_global_cleanup( );
        }

        static void update( ) {
            if ( _generateSudoku ) {
                generateSudoku( );
                _generateSudoku = false;
            }
            if ( _checkSudoku ) {
                _isSolved    = Algorithm::fieldConsistency( _field );
                _checkSudoku = false;
            }
            if ( _solveSudoku ) {
                switch ( static_cast< Algorithms >( _algorithmSelectedIndex ) ) {
                    case Algorithms::BACKTRACE:
                        deploySolvingAlgorithm( Algorithms::BACKTRACE );
                        break;
                    default: ;
                }
                _solveSudoku = false;
            }
            if ( _resetFields )
                resetFields( );
            if ( _loadPuzzle ) {
                resetFields(  );
                switch ( ( LoadSudoku ) _sudokusSelectedIndex ) {
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

        static void deploySolvingAlgorithm(
            const Algorithms algorithm
        ) {
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

            //Function fields: field &area, const int row, const int column
            solver.detach( );
            //Algorithm::backtrace( field, 0, 0 );
        }
    };
}
#endif //APPLICATION_H
