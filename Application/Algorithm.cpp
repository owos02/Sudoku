//
// Created by Oliver W. on 02.05.2025.
//

#include <thread>
#include <chrono>
#include <algorithm>

#include "Settings.h"
#include "Algorithm.h"


void Sudoku::Algorithm::slowDownAndVisualize( const int row, const int col ) {
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
            std::this_thread::sleep_for( 50ms );
            break;
        case 2:
            std::this_thread::sleep_for( 10ms );
            break;
        case 1:
            std::this_thread::sleep_for( 50us );
            break;
        default:
        case 0:
            break;
    }
}

std::map< int, int > Sudoku::Algorithm::generateEmptyMap( ) {
    std::map< int, int > tmp;
    for ( int i = 0; i <= SIZE; i++ )
        tmp.insert( std::pair( i, 0 ) );
    tmp[ 0 ] = -99;
    return tmp;
}

// Checks for whole field
// No field reference for speed
bool Sudoku::Algorithm::fieldConsistency(const field area ) {
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
    for ( int cellIndex = 0; cellIndex < SIZE; cellIndex++ ) {
        auto columnsCheck = generateEmptyMap( );
        for ( int rowIndex = 0; rowIndex < SIZE; rowIndex++ ) {
            if ( columnsCheck.at( area[ rowIndex ][ cellIndex ] ) > 0 )
                return false;
            columnsCheck[ area[ rowIndex ][ cellIndex ] ] = 1;
        }
    }

    //Check Every Block
    for ( int blockVerticalIndex = 0; blockVerticalIndex < BLOCK; blockVerticalIndex++ ) {
        for ( int blockHorizontalIndex = 0; blockHorizontalIndex < BLOCK; blockHorizontalIndex++ ) {
            auto blockCheck = generateEmptyMap( );
            for ( int rowIndex = BLOCK * blockVerticalIndex; rowIndex < BLOCK * blockVerticalIndex + BLOCK; rowIndex
                  ++ ) {
                for ( int cellIndex = BLOCK * blockHorizontalIndex; cellIndex < BLOCK * blockHorizontalIndex + BLOCK;
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

// Checks for one cell
// No field reference for speed
bool Sudoku::Algorithm::isValid( const field area, const int row, const int column ) {
    // Horizontal Check
    for ( int i = 0; i < SIZE; i++ ) {
        if ( ( area[ row ][ i ] == area[ row ][ column ] ) && ( i != column ) )
            return false;
    }
    //Vertical Check
    for ( int i = 0; i < SIZE; i++ ) {
        if ( ( area[ i ][ column ] == area[ row ][ column ] ) && ( i != row ) )
            return false;
    }
    //Get Grid
    const int startRow    = ( row / BLOCK ) * BLOCK;
    const int startColumn = ( column / BLOCK ) * BLOCK;
    //Block Check
    for ( int i = startRow; i < startRow + BLOCK; i++ ) {
        for ( int j = startColumn; j < startColumn + BLOCK; j++ ) {
            if ( area[ row ][ column ] == area[ i ][ j ] && ( row != i ) && ( column != j ) )
                return false;
        }
    }
    return true;
}

bool Sudoku::Algorithm::backtrace( field& area, const int row, const int column ) {
    //Calculate next row
    int nextRow = row, nextColumn = column + 1;
    if ( nextColumn == SIZE ) {
        nextColumn = 0;
        nextRow++;
    }

    //Check if past game field
    if ( row == SIZE ) {
        _visualiseX = -1;
        _visualiseY = -1;
        if ( fieldConsistency( area ) ) {
            _isSolved = true;
        } else
            _invalidPuzzle = true;

        return true;
    }

    //Cell has number
    if ( _original[ row ][ column ] != 0 ) {
        return backtrace( area, nextRow, nextColumn );
    }

    //Test Cell
    for ( int nextNumber = 1; nextNumber <= SIZE; nextNumber++ ) {
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
