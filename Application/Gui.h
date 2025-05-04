//
// Created by Ara on 02.05.2025.
//

#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <format>

#include "Settings.h"

namespace Sudoku {
    class Gui {
    public:
        static void show() {
            ImGui::DockSpaceOverViewport(100, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
            showField();
            showOptions();
        };

        static void showField() {
            const auto oldFrameBgColor = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
            const auto originalText = ImGui::GetStyle().Colors[ImGuiCol_Text];

            ImGui::GetStyle().CellPadding = {
                (70.0f - ImGui::GetFontSize()) / 2, (70.0f - ImGui::GetFontSize()) / 2 - 1
            };
            ImGui::Begin("Sudoku##Sudoku", nullptr, ImGuiWindowFlags_None);
            ImGui::BeginTable("SudokuArea", 9, ImGuiTableFlags_Borders, {70 * 9, 70 * 9});

            bool flipColoring = true;
            for (int row_index = 0; auto &row: _field) {
                if (row_index % 3 == 0) {
                    flipColoring = !flipColoring;
                }
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                for (int cell_index = 0; auto &cell: row) {
                    if (cell_index % 3 == 0 && cell_index != 0) {
                        flipColoring = !flipColoring;
                    }
                    if (!flipColoring) {
                        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = Colors::gameBoardGrey;
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = Colors::gameBoardText;
                    } else {
                        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = Colors::gameBoardWhite;
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = Colors::gameBoardText;
                    }
                    auto cellNumber = std::format("##{}", (row_index * _field.size() + cell_index));
                    ImGui::TableSetColumnIndex(cell_index);
                    ImGui::SetNextItemWidth(70.0);
                    auto oldTextColor = ImGui::GetStyle().Colors[ImGuiCol_Text];
                    if (cell == 0) {
                        auto tmp = Colors::warningRed;
                        tmp.w = 0;
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = tmp;
                    }
                    ImGui::InputInt(cellNumber.c_str(), &cell, 0, 0,
                                    ImGuiInputTextFlags_AlwaysOverwrite |
                                    ImGuiInputTextFlags_CharsDecimal);
                    cell = cell % 10; // Only allow decimals 0-9

                    if (cell == 0) {
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = oldTextColor;
                    }
                    if (flipColoring) {
                        const ImU32 white = ImGui::GetColorU32(Colors::gameBoardWhite);
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, white);
                    } else {
                        const ImU32 black = ImGui::GetColorU32(Colors::gameBoardGrey);
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, black);
                    }
                    cell_index++;
                }
                row_index++;
            }
            ImGui::EndTable();
            ImGui::End();
            ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = oldFrameBgColor;
            ImGui::GetStyle().Colors[ImGuiCol_Text] = originalText;

        };

        static void showOptions() {
            ImGui::Begin("General##Solving");
            ImGui::SeparatorText("Status");
            if (_isSolved)
                ImGui::TextColored(Colors::green, "Solved");
            else
                ImGui::TextColored(Colors::red, "Not Solved");

            ImGui::Text(std::format("Current Difficulty: {}", _sudokuDifficulty).c_str());
            if (ImGui::Button(" Check ")) {
                _checkSudoku = true;
            }
            ImGui::SameLine();
            if (ImGui::Button(" Reset ")) {
                _field = _original;
                _isSolved = false;
            }
            ImGui::SameLine();
            ImGui::BeginDisabled(_enableShowWebSolution);
            if (ImGui::Button(" Show Solution ")) {
                _field = _solution;
            }
            if (ImGui::BeginItemTooltip()) {
                ImGui::Text("Only usable when fetched from an online API.");
                ImGui::EndTooltip();
            }
            ImGui::EndDisabled();

            ImGui::SeparatorText("Generation");
            ImGui::Text("Fetch API: ");
            ImGui::SameLine();
            ImGui::RadioButton("YDS", &_selectedAPI, static_cast<int>(APIs::YDS));
            ImGui::SameLine();
            ImGui::RadioButton("Dosuku", &_selectedAPI, static_cast<int>(APIs::DOSUKU));
            if (static_cast<APIs>(_selectedAPI) == APIs::DOSUKU) {
                ImGui::TextColored(Colors::warningRed, "[INFO]: Dosuku ignores the difficulty parameter");
            }
            if (const char *difficultyPreview = _difficulties[_difficultiesSelectedIndex];
                ImGui::BeginCombo("Difficulty##Sudoku_Difficulty", difficultyPreview)) {
                for (int n = 0; n < IM_ARRAYSIZE(_difficulties); n++) {
                    const bool selected = (_difficultiesSelectedIndex == n);
                    if (ImGui::Selectable(_difficulties[n], selected))
                        _difficultiesSelectedIndex = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button(" Fetch ")) {
                _generateSudoku = true;
                _enableShowWebSolution = false;
            }

            ImGui::SeparatorText("Algorithms");
            if (const char *algorithmPreview = _solvingAlgorithms[_algorithmSelectedIndex];
                ImGui::BeginCombo("Solving Algorithm", algorithmPreview, ImGuiComboFlags_WidthFitPreview)) {
                for (int n = 0; n < IM_ARRAYSIZE(_solvingAlgorithms); n++) {
                    const bool selected = (_algorithmSelectedIndex == n);
                    if (ImGui::Selectable(_solvingAlgorithms[n], selected))
                        _algorithmSelectedIndex = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            if (ImGui::Button(" Solve ")) {
                _solveSudoku = true;
            }
            ImGui::End();
        }

        static void setStyling() {
        }
    };
}


#endif //GUI_H
