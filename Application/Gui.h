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
            const auto old_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];

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
                        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    } else {
                        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                        ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                    }
                    auto cellNumber = std::format("##{}", (row_index * _field.size() + cell_index));
                    ImGui::TableSetColumnIndex(cell_index);
                    ImGui::SetNextItemWidth(70.0);
                    ImGui::InputInt(cellNumber.c_str(), &cell, 0, 0,
                                    ImGuiInputTextFlags_AlwaysOverwrite |
                                    ImGuiInputTextFlags_CharsDecimal);
                    cell = cell % 10; // Only allow decimals 0-9

                    if (flipColoring) {
                        const ImU32 white = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, white);
                    } else {
                        const ImU32 black = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, black);
                    }
                    cell_index++;
                }
                row_index++;
            }
            ImGui::EndTable();
            ImGui::End();
            ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = old_color;
        };

        static void showOptions() {
            ImGui::Begin("General##Solving");
            ImGui::SeparatorText("Generation");
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
            if (true) {
                const auto oldColor = ImGui::GetStyle().Colors[ImGuiCol_Text];
                ImGui::GetStyle().Colors[ImGuiCol_Text] = Colors::warningRed;
                ImGui::Text("[FIXME]: Dosuku ignores the difficulty parameter");
                ImGui::GetStyle().Colors[ImGuiCol_Text] = oldColor;
            }

            ImGui::Text(std::format("Current Difficulty: {}", _sudokuDifficulty).c_str());
            if (ImGui::Button(" Fetch ")) {
                _generateSudoku = true;
            }
            ImGui::SeparatorText("Algorithms");
            if (ImGui::Button(" Solve ")) {
            }
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
            ImGui::End();
        }

        static void setStyling() {
        }
    };
}


#endif //GUI_H
