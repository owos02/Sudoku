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
#include <imgui_stdlib.h>
#include <memory>

class Application {
    std::array<std::array<int, 9>, 9> field = {
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
    int cellX = -1, cellY = -1;
    int buffer = 0;
    float inputSize = 38;

public:
    void run() {
        ImGui::DockSpaceOverViewport(100, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        update();
        showGui();
    }

    void update() {

    }

    void gameWindow() {
        auto old_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];

        ImGui::Begin("Sudoku##Sudoku", nullptr, 0);
        ImGui::BeginTable("SudokuArea", 9, ImGuiTableFlags_Borders , {70 * 9, (70) * 9});
        ImGui::GetStyle().CellPadding = {(70.0f - ImGui::GetFontSize()) / 2, (70.0f - ImGui::GetFontSize()) / 2 - 1};
        bool flip = true;
        for (int row_index = 0; auto &row: field) {
            if (row_index % 3 == 0)
                flip = !flip;
            ImGui::TableNextRow(ImGuiTableRowFlags_None);
            for (int cell_index = 0; auto &cell: row) {
                if (cell_index % 3 == 0 && cell_index != 0)
                    flip = !flip;
                if (!flip) {
                    ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                }else {
                    ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                }
                auto fmt = std::format("##{}", (row_index * field.size() + cell_index));
                ImGui::TableSetColumnIndex(cell_index);
                ImGui::SetNextItemWidth(70.0);
                ImGui::InputInt(fmt.c_str(), &cell, 0, 0, ImGuiInputTextFlags_None);
                cell = cell % 10;

                if (flip) {
                    ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                } else {
                    ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                }

                cell_index++;
            }

            row_index++;
        }
        ImGui::EndTable();
        ImGui::End();
        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = old_color;
    }

    void settingsWindow() {
        ImGui::Begin("Settings##Settings");
        ImGui::End();
    };

    void showGui() {
        gameWindow();
        settingsWindow();
    };

    void setStyling() {

    }
};
#endif //APPLICATON_H
