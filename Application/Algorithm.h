//
// Created by Ara on 02.05.2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <algorithm>
#include <array>
#include <map>
#include <thread>
#include <chrono>

#include "Settings.h"

namespace Sudoku {
    class Algorithm {
        using field = std::array< std::array< int, 9 >, 9 > &;

        /* The rules of Sudoku
         *
         * 1. Only use numbers from 1-9;
         * 2. No repeating numbers in a row or column
         * 3. No repeating numbers in a 3x3 designated block
         **/

        static void slowDownAndVisualize( const int row, const int col ) {
            _visualiseX = col;
            _visualiseY = row;
            using namespace std::chrono_literals;
            switch ( _solvingDelay ) {
                case 4:
                    _notAdvance = true;
                    // Condition can be changed from GUI & is therefore correct
                    while ( _notAdvance && _solvingDelay == 4 ) {
                        std::this_thread::sleep_for( 100ms );
                    }
                    break;
                case 3:
                    std::this_thread::sleep_for( 100ms );
                    break;
                case 2:
                    std::this_thread::sleep_for( 25ms );
                    break;
                case 1:
                    std::this_thread::sleep_for( 5ms );
                    break;
                default:
                case 0:
                    return;
                    break;
            }
        }

    public:
        static std::map< int, int > generateEmptyMap( ) {
            std::map< int, int > tmp;
            for ( int i = 0; i <= 9; i++ )
                tmp.insert( std::pair( i, 0 ) );
            tmp[ 0 ] = -99;
            return tmp;
        }

        static bool fieldConsistency( const field area ) {
            //Check if all cells contain valid numbers
            for ( auto row : area ) {
                for ( const int cell : row ) {
                    if ( cell == 0 )
                        return false;
                }
            }

            //Check Rows
            for ( const auto &row : area ) {
                auto rowsCheck = generateEmptyMap( );
                for ( const auto &cell : row ) {
                    if ( rowsCheck[ cell ] > 0 )
                        return false;
                    rowsCheck[ cell ] = 1;
                }
            }

            //Check Columns
            for ( int cellIndex = 0; cellIndex < 9; cellIndex++ ) {
                auto columnsCheck = generateEmptyMap( );
                for ( int rowIndex = 0; rowIndex < 9; rowIndex++ ) {
                    if ( columnsCheck.at( area[ rowIndex ][ cellIndex ] ) > 0 )
                        return false;
                    columnsCheck[ area[ rowIndex ][ cellIndex ] ] = 1;
                }
            }

            //Check Every Block
            for ( int blockVerticalIndex = 0; blockVerticalIndex < 3; blockVerticalIndex++ ) {
                for ( int blockHorizontalIndex = 0; blockHorizontalIndex < 3; blockHorizontalIndex++ ) {
                    auto blockCheck = generateEmptyMap( );
                    for ( int rowIndex = 3 * blockVerticalIndex; rowIndex < 3 * blockVerticalIndex + 3; rowIndex++ ) {
                        for ( int cellIndex = 3 * blockHorizontalIndex; cellIndex < 3 * blockHorizontalIndex + 3;
                              cellIndex++ ) {
                            if ( blockCheck.at( area[ rowIndex ][ cellIndex ] ) > 0 )
                                return false;
                            blockCheck[ area[ rowIndex ][ cellIndex ] ] = 1;
                        }
                    }
                }
            }
            return true;
        }

        static bool isValid( const field area, const int row, const int column ) {
            // Horizontal Check
            for ( int i = 0; i < 9; i++ ) {
                if ( ( area[ row ][ i ] == area[ row ][ column ] ) && ( i != column ) )
                    return false;
            }
            //Vertical Check
            for ( int i = 0; i < 9; i++ ) {
                if ( ( area[ i ][ column ] == area[ row ][ column ] ) && ( i != row ) )
                    return false;
            }
            //Get Grid
            const int startRow    = ( row / 3 ) * 3;
            const int startColumn = ( column / 3 ) * 3;
            //Block Check
            for ( int i = startRow; i < startRow + 3; i++ ) {
                for ( int j = startColumn; j < startColumn + 3; j++ ) {
                    if ( area[ row ][ column ] == area[ i ][ j ] && ( row != i ) && ( column != j ) )
                        return false;
                }
            }
            return true;
        }


        static bool backtrace( field &area, const int row, const int column ) {
            //Calculate next row
            int nextRow = row, nextColumn = column + 1;
            if ( nextColumn == 9 ) {
                nextColumn = 0;
                nextRow++;
            }

            //Check if past game field
            if ( row == 9 ) {
                _visualiseX = -1;
                _visualiseY = -1;
                if ( fieldConsistency( area ) ) {
                    _isSolved = true;
                }
                else
                    _invalidPuzzle = true;

                return true;
            }

            //Cell has number
            if ( _original[ row ][ column ] != 0 ) {
                return backtrace( area, nextRow, nextColumn );
            }

            //Test Cell
            for ( int nextNumber = 1; nextNumber <= 9; nextNumber++ ) {
                if ( _breakSolving )
                    return true;
                slowDownAndVisualize( row, column );

                area[ row ][ column ] = nextNumber;
                if ( isValid( area, row, column ) ) {
                    // When valid -> go to next field
                    if ( backtrace( area, nextRow, nextColumn ) ) {
                        return true;
                    }
                }
            }

            // If nothing is valid: go back
            area[ row ][ column ] = 0;
            return false;
        }
    };
}


#endif //ALGORITHM_H
