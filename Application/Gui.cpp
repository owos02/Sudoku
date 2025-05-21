//
// Created by Ara on 02.05.2025.
//

#include <imgui.h>
#include <format>
#include <thread>
#include <chrono>

#include "Gui.h"
#include "Settings.h"

void Sudoku::Gui::show( ) {
    ImGui::DockSpaceOverViewport( 100, nullptr, ImGuiDockNodeFlags_PassthruCentralNode );
    showField( );
    showOptions( );
}

void Sudoku::Gui::showField( ) {
    const auto oldFrameBgColor = ImGui::GetStyle( ).Colors[ ImGuiCol_FrameBg ];
    const auto originalText    = ImGui::GetStyle( ).Colors[ ImGuiCol_Text ];

    ImGui::GetStyle( ).CellPadding = {
        ( 70.0f - ImGui::GetFontSize( ) ) / 2, ( 70.0f - ImGui::GetFontSize( ) ) / 2 - 1
    };
    ImGui::Begin( "Sudoku##Sudoku", nullptr, ImGuiWindowFlags_None );
    ImGui::BeginTable( "SudokuArea", 9, ImGuiTableFlags_Borders, { 70 * 9, 70 * 9 } );

    bool flipColoring = true;
    for ( int row_index = 0; auto &row : _field ) {
        if ( row_index % 3 == 0 ) {
            flipColoring = !flipColoring;
        }
        ImGui::TableNextRow( ImGuiTableRowFlags_None );
        for ( int cell_index = 0; auto &cell : row ) {
            if ( cell_index % 3 == 0 && cell_index != 0 ) {
                flipColoring = !flipColoring;
            }
            if ( !flipColoring ) {
                ImGui::GetStyle( ).Colors[ ImGuiCol_FrameBg ] = Colors::gameBoardGrey;
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ]    = Colors::gameBoardText;
            } else {
                ImGui::GetStyle( ).Colors[ ImGuiCol_FrameBg ] = Colors::gameBoardWhite;
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ]    = Colors::gameBoardText;
            }
            auto cellNumber = std::format( "##{}", ( row_index * _field.size( ) + cell_index ) );
            ImGui::TableSetColumnIndex( cell_index );
            ImGui::SetNextItemWidth( 70.0 );
            const auto oldTextColor = ImGui::GetStyle( ).Colors[ ImGuiCol_Text ];
            if ( cell == 0 ) {
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] = Colors::transparent;
            }
            if ( _original[ row_index ][ cell_index ] != 0 ) {
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] = Colors::overlay0;
            }
            if ( row_index == _visualiseY && cell_index == _visualiseX && cell != 0 ) {
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] = Colors::red;
            }
            ImGui::InputInt(
                cellNumber.c_str( ), &cell, 0, 0,
                ImGuiInputTextFlags_AlwaysOverwrite |
                ImGuiInputTextFlags_CharsDecimal
            );

            // Only allow decimals 0-9
            cell = cell % 10;

            if ( static_cast< Mode >(_mode) == Mode::CREATE ) {
                _original[ row_index ][ cell_index ] = cell;
            }

            if ( _original[ row_index ][ cell_index ] != 0 ) {
                // Only write to empty spaces
                cell = _original[ row_index ][ cell_index ];
            }

            if ( cell == 0 ) {
                ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] = oldTextColor;
            }
            if ( flipColoring ) {
                const ImU32 white = ImGui::GetColorU32( Colors::gameBoardWhite );
                ImGui::TableSetBgColor( ImGuiTableBgTarget_CellBg, white );
            } else {
                const ImU32 black = ImGui::GetColorU32( Colors::gameBoardGrey );
                ImGui::TableSetBgColor( ImGuiTableBgTarget_CellBg, black );
            }
            cell_index++;
        }
        row_index++;
    }
    ImGui::EndTable( );
    ImGui::End( );
    ImGui::GetStyle( ).Colors[ ImGuiCol_FrameBg ] = oldFrameBgColor;
    ImGui::GetStyle( ).Colors[ ImGuiCol_Text ]    = originalText;
}

void Sudoku::Gui::showOptions( ) {
    ImGui::Begin( "General##Solving" );
    ImGui::SeparatorText( "Status" );
    ImGui::Text( "Mode" );
    ImGui::SameLine( );
    ImGui::RadioButton( "Solving Mode", &_mode, 0 );
    ImGui::SameLine( );
    ImGui::RadioButton( "Create Mode", &_mode, 1 );
    if ( static_cast< Mode >(_mode) == Mode::CREATE ) {
        ImGui::SameLine( );
        if ( ImGui::Button( " Clear Field " ) )
            _resetFields = true;
    }

    if ( _isSolved )
        ImGui::TextColored( Colors::green, "Solved" );
    else
        ImGui::TextColored( Colors::red, "Not Solved" );

    if ( _invalidPuzzle )
        ImGui::TextColored( Colors::mauve, "[ERROR]: INVALID PUZZLE" );
    ImGui::Text( std::format( "Current Difficulty: {}", _sudokuDifficulty ).c_str( ) );
    if ( ImGui::Button( " Check " ) ) {
        _checkSudoku = true;
    }
    ImGui::SameLine( );
    if ( ImGui::Button( " Reset " ) ) {
        _field    = _original;
        _isSolved = false;
    }
    ImGui::SameLine( );
    ImGui::BeginDisabled( _enableShowWebSolution );
    if ( ImGui::Button( " Show Solution " ) ) {
        _mode  = static_cast< int >(Mode::SOLVING);
        _field = _solution;
    }
    if ( ImGui::BeginItemTooltip( ) ) {
        ImGui::Text( "Only usable when fetched from an online API." );
        ImGui::EndTooltip( );
    }
    ImGui::EndDisabled( );

    ImGui::SeparatorText( "Generation" );
    ImGui::Text( "Fetch API: " );
    ImGui::SameLine( );
    ImGui::RadioButton( "YDS", &_selectedAPI, static_cast< int >(APIs::YDS) );
    ImGui::SameLine( );
    ImGui::RadioButton( "Dosuku", &_selectedAPI, static_cast< int >(APIs::DOSUKU) );
    if ( static_cast< APIs >(_selectedAPI) == APIs::DOSUKU ) {
        ImGui::TextColored( Colors::warningRed, "[INFO]: Dosuku ignores the difficulty parameter" );
    }
    if ( const char *difficultyPreview = _difficulties[ _difficultiesSelectedIndex ];
        ImGui::BeginCombo( "Difficulty##Sudoku_Difficulty", difficultyPreview ) ) {
        for ( int n = 0; n < IM_ARRAYSIZE( _difficulties ); n++ ) {
            const bool selected = ( _difficultiesSelectedIndex == n );
            if ( ImGui::Selectable( _difficulties[ n ], selected ) )
                _difficultiesSelectedIndex = n;

            if ( selected )
                ImGui::SetItemDefaultFocus( );
        }
        ImGui::EndCombo( );
    }

    if ( ImGui::Button( " Fetch " ) ) {
        _mode                  = static_cast< int >(Mode::SOLVING);
        _generateSudoku        = true;
        _enableShowWebSolution = false;
    }

    ImGui::SeparatorText( "Algorithms" );
    if ( const char *algorithmPreview = _solvingAlgorithms[ _algorithmSelectedIndex ];
        ImGui::BeginCombo( "Solving Algorithm", algorithmPreview, ImGuiComboFlags_WidthFitPreview ) ) {
        for ( int n = 0; n < IM_ARRAYSIZE( _solvingAlgorithms ); n++ ) {
            const bool selected = ( _algorithmSelectedIndex == n );
            if ( ImGui::Selectable( _solvingAlgorithms[ n ], selected ) )
                _algorithmSelectedIndex = n;

            if ( selected )
                ImGui::SetItemDefaultFocus( );
        }
        ImGui::EndCombo( );
    }
    ImGui::Text( "Solving Delay" );
    ImGui::RadioButton( "None", &_solvingDelay, 0 );
    ImGui::SameLine( );
    ImGui::RadioButton( "Little", &_solvingDelay, 1 );
    ImGui::SameLine( );
    ImGui::RadioButton( "Some", &_solvingDelay, 2 );
    ImGui::SameLine( );
    ImGui::RadioButton( "A Lot", &_solvingDelay, 3 );
    ImGui::SameLine( );
    ImGui::RadioButton( "Manual", &_solvingDelay, 4 );
    if ( _solvingDelay == 4 ) {
        ImGui::SameLine( );
        if ( ImGui::Button( " Advance " ) )
            _notAdvance = false;
    }
    if ( ImGui::Button( " Solve " ) ) {
        _mode        = static_cast< int >(Mode::SOLVING);
        _solveSudoku = true;
    }
    if ( _visualiseX != -1 && _visualiseY != -1 ) {
        ImGui::SameLine( );
        const std::string solvingFor = std::format(
            "Currently Solving for: [X:{0},Y:{1}]", _visualiseX + 1, _visualiseY + 1
        );
        ImGui::Text( solvingFor.c_str( ) );
    }
    if ( ImGui::Button( " Stop Solving " ) ) {
        using namespace std::chrono_literals;
        _mode         = static_cast< int >(Mode::SOLVING);
        _breakSolving = true;
        std::this_thread::sleep_for( 100ms );
        _breakSolving = false;
    }

    ImGui::SeparatorText( "Example Sudokus" );
    if ( const char *sudokusPreview = _exampleSudokus[ _sudokusSelectedIndex ];
        ImGui::BeginCombo( "Puzzle", sudokusPreview, ImGuiComboFlags_WidthFitPreview ) ) {
        for ( int n = 0; n < IM_ARRAYSIZE( _exampleSudokus ); n++ ) {
            const bool selected = ( _sudokusSelectedIndex == n );
            if ( ImGui::Selectable( _exampleSudokus[ n ], selected ) )
                _sudokusSelectedIndex = n;

            if ( selected )
                ImGui::SetItemDefaultFocus( );
        }
        ImGui::EndCombo( );
    }
    if ( ImGui::Button( "Load" ) )
        _loadPuzzle = true;
    ImGui::End( );
}
