//
// Created by Oliver W. on 5/4/25.
//

#ifndef APIHANDLER_H
#define APIHANDLER_H


#include "Settings.h"

namespace Sudoku {
    class ApiHandler {
    public:
        static void execute( APIs api );

    private:
        static void ydsApiFetch( );

        static void dosukuApiFetch( );
    };
} // Sudoku

#endif //APIHANDLER_H
