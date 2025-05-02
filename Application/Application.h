//
// Created by Oliver W. on 4/28/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <array>
#include <print>
#include <SDL.h>
#include <SDL_net.h>
#include "Gui.h"
#include "Settings.h"

namespace Sudoku {
    class Application {
    public:
        Application() {
            Gui::setStyling();
            for (auto &row: _field) {
                row.fill(0);
            }
        }

        void run() {
            Gui::show();
            update();
        }

        void generateSudoku() {
            IPaddress ip;
            SDLNet_ResolveHost(&ip, "https://sudoku-api.vercel.app", 443);
            TCPsocket socket = SDLNet_TCP_Open(&ip);

            std::string request;
            request.append("GET /api/dosuku HTTP1.1\r\n");
            request.append("Host: sudoku-api.vercel.app\r\n");
            int requestLength = static_cast<int>(request.length());
            int sentLength = SDLNet_TCP_Send(
                socket,
                request.c_str(),
                requestLength
            );
            if (sentLength != requestLength) {
                std::println("[WARNING]: Network Error");
            }

            constexpr int bufferSize = 4096;
            std::string recievedData;
            auto buffer = std::make_unique<std::array<char, bufferSize> >();
            int length;
            do {
                length = SDLNet_TCP_Recv(socket, (void *) buffer.get(), bufferSize);
                for (const auto data: buffer) {
                    recievedData.push_back(data);
                }
            } while (length > 0);

            std::print("{}", recievedData);
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
