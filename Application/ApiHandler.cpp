//
// Created by Oliver W. on 5/4/25.
//

#include <string>
#include <print>
#include <random>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <imgui.h>

#include "ApiHandler.h"

namespace Sudoku {
    void ApiHandler::execute(const APIs api) {
        switch (api) {
            case APIs::YDS:
                ydsApiFetch();
                break;
            case APIs::DOSUKU:
                dosukuApiFetch();
                break;
        }
    }

    static size_t curlWriteCallback(const char *ptr, const size_t size, const size_t nmemb, void *userdata) {
        static_cast<std::string *>(userdata)->append(ptr, size * nmemb);
        return size * nmemb;
    }

    void ApiHandler::dosukuApiFetch() {
        std::string gameData;
        const auto difficulty = static_cast<Difficulties>(_difficultiesSelectedIndex);
        std::string uri;
        switch (difficulty) {
            case Difficulties::EASY:
                uri = "https://sudoku-api.vercel.app/api/dosuku?where={difficulty=Easy}";
                break;
            case Difficulties::MEDIUM:
                uri = "https://sudoku-api.vercel.app/api/dosuku?where={difficulty=Medium}";
                break;
            case Difficulties::HARD:
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
        _original = _field;
    }


    void ApiHandler::ydsApiFetch() {
        std::string gameData;
        auto difficulty = static_cast<Difficulties>(_difficultiesSelectedIndex);
        const std::string uri = "https://you-do-sudoku-api.vercel.app/api";


        std::string postBody = R"({"difficulty" : "medium","solution" : true,"array" : false})";
        auto randomSeed = std::random_device();
        std::mt19937 randomizedEngine(randomSeed());
        std::uniform_int_distribution difficultySelector(0, 2);
        if (difficulty == Difficulties::RANDOM)
            difficulty = static_cast<Difficulties>(difficultySelector(randomizedEngine));
        switch (difficulty) {
            case Difficulties::EASY:
                postBody = R"({"difficulty" : "easy","solution" : true,"array" : false})";
                break;
            case Difficulties::MEDIUM:
                postBody = R"({"difficulty" : "medium","solution" : true,"array" : false})";
                break;
            case Difficulties::HARD:
                postBody = R"({"difficulty" : "hard","solution" : true,"array" : false})";
                break;
            default: break;
        }
        curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(_curl, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(_curl, CURLOPT_POST, true);
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, postBody.c_str());
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &gameData);

        if (const CURLcode curlResult = curl_easy_perform(_curl); curlResult != CURLE_OK) {
            std::println("[ERROR]: Connection Error\nWebsite Error Code: {}", curl_easy_strerror(curlResult));
            return;
        }
        nlohmann::json fieldData = nlohmann::json::parse(gameData);

        _sudokuDifficulty = fieldData["difficulty"];

        std::println("[INFO]: Fetching Puzzle & Solution");
        const std::string field = fieldData["puzzle"];
        const std::string solution = fieldData["solution"];
        for (size_t index = 0; index < field.size(); index++) {
            _field[std::floor(index / 9)][index % 9] = field.at(index) - '0';
            _solution[std::floor(index / 9)][index % 9] = solution.at(index) - '0';
        }
        _original = _field;
    }
} // Sudoku
