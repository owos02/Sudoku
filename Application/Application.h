//
// Created by Oliver W. on 4/28/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <array>
#include <string>
#include <format>
#include <cmath>
#include <imgui.h>
#include <memory>

class Application {
    std::array<std::array<int, 9>, 9> _field = {
        std::array<int, 9>() = {1, 2, 3, 1, 2, 3, 1, 2, 3},
        std::array<int, 9>() = {4, 5, 6, 4, 5, 6, 4, 5, 6},
        std::array<int, 9>() = {7, 8, 9, 7, 8, 9, 7, 8, 9},
        std::array<int, 9>() = {1, 2, 3, 1, 2, 3, 1, 2, 3},
        std::array<int, 9>() = {4, 5, 6, 4, 5, 6, 4, 5, 6},
        std::array<int, 9>() = {7, 8, 9, 7, 8, 9, 7, 8, 9},
        std::array<int, 9>() = {1, 2, 3, 1, 2, 3, 1, 2, 3},
        std::array<int, 9>() = {4, 5, 6, 4, 5, 6, 4, 5, 6},
        std::array<int, 9>() = {7, 8, 9, 7, 8, 9, 7, 8, 9}
    };

public:
    Application() {
        setStyling();
        for (auto &row: _field) {
            row.fill(0);
        }
    }

    void run() {
        ImGui::DockSpaceOverViewport(100, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        update();
        showGui();
    }

    void update() {
    }

    void gameWindow() {
        const auto old_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];

        ImGui::GetStyle().CellPadding = {(70.0f - ImGui::GetFontSize()) / 2, (70.0f - ImGui::GetFontSize()) / 2 - 1};
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
    }

    const char *_solvingAlgorithms[2] = {"Backtrace", "Placeholder"};
    int _algorithmSelectedIndex = 0;

    void settingsWindow() {
        ImGui::Begin("Solving##Solving");

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
        }
        ImGui::End();
        ImGui::Begin("Settings##Settings");
        ImGui::End();
    };

    void showGui() {
        gameWindow();
        settingsWindow();
    };

    static void setStyling() {
    }
};
#endif //APPLICATION_H
