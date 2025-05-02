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
#include <SDL.h>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Gui.h"
#include "Settings.h"

namespace Sudoku {
    class Application {
    private:
        static size_t curlWriteCallback(char *ptr, const size_t size, const size_t nmemb, void *userdata) {
            static_cast<std::string *>(userdata)->append((char *) ptr, size * nmemb);
            return size * nmemb;
        }

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

        void run() {
            Gui::show();
            update();
        }

        void generateSudoku() const {
            //TODO: Add multiple generation api's

            std::string gameData;
            const auto difficulty = static_cast<Difficulty>(_difficultiesSelectedIndex);
            std::string uri;
            switch (difficulty) {
                case Difficulty::EASY:
                    uri = "https://sudoku-api.vercel.app/api/dosuku?where={difficulty=Easy}";
                    break;
                case Difficulty::MEDIUM:
                    uri = "https://sudoku-api.vercel.app/api/dosuku?where={difficulty=Medium}";
                    break;
                case Difficulty::HARD:
                    uri = "https://sudoku-api.vercel.app/api/dosuku?where={difficulty=Hard}";
                    break;
                default: uri = "https://sudoku-api.vercel.app/api/dosuku";
            }

            curl_easy_setopt(_curl, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(_curl, CURLOPT_HTTPGET, true);
            curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
            curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &gameData);

            if (const CURLcode curlResult = curl_easy_perform(_curl); curlResult != CURLE_OK) {
                std::println("[ERROR]: Connection Error\nWebsite Error Code: {}", curl_easy_strerror(curlResult));
                return;
            }
            std::erase(gameData, '\n');
            nlohmann::json fieldData = nlohmann::json::parse(gameData);

            _sudokuDifficulty = fieldData["newboard"]["grids"][0]["difficulty"];

            std::println("[INFO]: Fetching Puzzle & Solution");
            for (int otherRow = 0; otherRow < 9; otherRow++) {
                for (int other = 0; other < 9; other++) {
                    _field[otherRow][other] = fieldData["newboard"]["grids"][0]["value"][otherRow][other];
                    _solution[otherRow][other] = fieldData["newboard"]["grids"][0]["solution"][otherRow][other];
                }
            }
        }

        ~Application() {
            curl_easy_cleanup(_curl);
            curl_global_cleanup();
        }

        void update() {
            if (_generateSudoku) {
                generateSudoku();
                _generateSudoku = false;
            }
        }
    };
}
#endif //APPLICATION_H
