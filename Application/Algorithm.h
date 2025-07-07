//
// Created by Oliver W. on 02.05.2025.
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
    static constexpr int SIZE  = 9;
    static constexpr int BLOCK = 3;

    class Algorithm final {
        using field = std::array< std::array< int, SIZE >, SIZE >;

        static void slowDownAndVisualize( const int row, const int col );

        [[nodiscard]] static std::map< int, int > generateEmptyMap( );

    public:
        [[nodiscard]] static bool fieldConsistency( const field area );

        [[nodiscard]] static bool isValid( const field area, const int row, const int column );

        [[nodiscard]] static bool backtrace( field& area, const int row, const int column );
    };
}

#endif //ALGORITHM_H
