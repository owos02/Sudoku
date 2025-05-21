//
// Created by Ara on 02.05.2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <array>
#include <map>

/* The rules of Sudoku
 *
 * 1. Only use numbers from 1-9;
 * 2. No repeating numbers in a row or column
 * 3. No repeating numbers in a 3x3 designated block
 **/


namespace Sudoku {
    class Algorithm final {
        using field = std::array< std::array< int, 9 >, 9 > &;

        static void slowDownAndVisualize( const int row, const int col );

    public:
        static std::map< int, int > generateEmptyMap( );

        static bool fieldConsistency( const field area );

        static bool isValid( const field area, const int row, const int column );

        static bool backtrace( field &area, const int row, const int column );
    };
}


#endif //ALGORITHM_H
