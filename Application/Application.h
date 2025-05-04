//
// Created by Oliver W. on 4/28/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <array>
#include <print>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
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
        Application() {
            curl_global_init(CURL_GLOBAL_DEFAULT);
            _curl = curl_easy_init();
            Gui::setStyling();
            for (auto &row: _field) {
                row.fill(0);
            }
            for (auto &row: _solution) {
                row.fill(0);
            }
        }

        static void run() {
            Gui::show();
            update();
        }


        static void generateSudoku() {
            ApiHandler::execute(static_cast<APIs>(_selectedAPI));
            std::ranges::transform(_sudokuDifficulty, _sudokuDifficulty.begin(), ::toupper);
        }

        ~Application() {
            curl_easy_cleanup(_curl);
            curl_global_cleanup();
        }

        static void update() {
            if (_generateSudoku) {
                generateSudoku();
                _generateSudoku = false;
            }
            if (_checkSudoku) {
                _isSolved = Algorithm::fieldConsistency(_field);
                _checkSudoku = false;
            }
            if (_solveSudoku) {
                switch (static_cast<Algorithms>(_algorithmSelectedIndex)) {
                    case Algorithms::BACKTRACE:
                        deploySolvingAlgorithm(_field, &Algorithm::backtrace);
                        break;
                    default: ;
                }
                _solveSudoku = false;
            }
        }

        static void deploySolvingAlgorithm(
            std::array<std::array<int, 9>, 9> &field,
            const std::function<void(std::array<std::array<int, 9>, 9> &)> &solveAlgorithm
        ) {
            // std::thread solver(solveAlgorithm, field);
            // solver.detach();
            (solveAlgorithm)(field);
        }
    };
}
#endif //APPLICATION_H
