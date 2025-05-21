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
    class Application final {
    public:
        Application( );

        static void resetFields( );

        static void run( );

        static void generateSudoku( );

        ~Application( );

        static void update( );

        static void deploySolvingAlgorithm(
            Algorithms algorithm
        );
    };
}
#endif //APPLICATION_H
