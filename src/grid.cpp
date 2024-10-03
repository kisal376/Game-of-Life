#include "grid.hpp"
#include <raylib.h>

using namespace std;

void Grid::Draw()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            Color color;
            switch (cells[row][col])
            {
            case 1:
                color = Color {0, 255, 0, 255};
                break;
            
            case 0:
                color = Color{60, 60, 60, 255};
                break;
            
            case 2:
                color = Color{0, 255, 0, 125};

            default:
                break;
            }
            // Color color = cells[row][col] ? Color{0, 255, 0, 255} : Color{60, 60, 60, 255}; // Set colour to green or a lighter gray (to make a grid visible) depending on in the cell is alive
            DrawRectangle(col*cellSize, row*cellSize, cellSize-1, cellSize-1, color); // Size of cells offset by 1 pixel to make a grid 2 pixels thick
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(IsValid(row, column))
    {
        cells[row][column] = value;
    }
}

int Grid::GetValue(int row, int column)
{
    if (IsValid(row, column))
    {
        return cells[row][column];
    }
    return 0;
}

bool Grid::IsValid(int row, int column)
{
    if (row >= 0 && row < rows && column >= 0 && column < columns)
    {
        return true;
    }
    return false;
}

void Grid::RandomStart()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            int val = GetRandomValue(0, 4); // 20% chance of cell being alive
            cells[row][col] = (val == 1) ? 1 : 0;
        }
    }
}

void Grid::Clear()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            cells[row][col] = 0;
        }
    }
}

void Grid::ToggleCell(int row, int column)
{
    if (IsValid(row, column))
    {
        int val = prevCell.second;

        switch (val)
        {
        case 0:
            cells[row][column] = 1;
            prevCell.second = 1;
            break;
        
        case 1:
            cells[row][column] = 0;
            prevCell.second = 0;
            break;

        default:
            break;
        }
    }
}

void Grid::Hover(int row, int column)
{
    if (IsValid(row, column))
    {
        if (prevCell.second == -1)
        {
            prevCell.first.first = row;
            prevCell.first.second = column;
            prevCell.second = GetValue(row, column);
            SetValue(row, column, 2);
        }

        if (prevCell.first.first != row || prevCell.first.second != column)
        {
            SetValue(prevCell.first.first, prevCell.first.second, prevCell.second);
            prevCell.first.first = row;
            prevCell.first.second = column;
            prevCell.second = GetValue(row, column);
            SetValue(row, column, 2);
        } 

    }
}


void Grid::DrawShape(int row, int column, vector<pair<int, int>> offsets)
{
    for (const auto &offset : offsets)
    {
        SetValue((row + offset.first + GetRows()) % GetRows(), (column + offset.second + GetCols()) % GetCols(), 1);
        if (offset.first == 0 && offset.second == 0)
        {
            prevCell.second = 1; // taking care of saved value for hovering to work
        }
    }
}

int Grid::Letters(int row, int column, int letter)
{
    vector<pair<int, int>> offsets;

    if (IsValid(row, column))
    {
        switch (letter)
        {
        case 1:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 1},
                    {-3, 2},
                    {-4, 3},
                    {-1, 6},
                    {-2, 5},
                    {-3, 4},
                    {0, 6},
                    {-2, 2},
                    {-2, 3},
                    {-2, 4},
                };
            DrawShape(row, column, offsets);
            return 6;
        case 2:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-3, 3},
                    {-2, 2},
                    {-2, 1},
                    {-1, 3},
                    {0, 2},
                    {0, 1},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 3:
            offsets =
                {
                    {0, 3},
                    {0, 2},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-4, 2},
                    {-4, 3},

                };
            DrawShape(row, column, offsets);
            return 3;
        case 4:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-3, 3},
                    {-2, 3},
                    {-1, 3},
                    {0, 2},
                    {0, 1},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 5:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-4, 3},
                    {-2, 3},
                    {-2, 2},
                    {-2, 1},
                    {0, 3},
                    {0, 2},
                    {0, 1},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 6:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-4, 3},
                    {-2, 3},
                    {-2, 2},
                    {-2, 1},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 7:
            offsets =
                {
                    {0, 3},
                    {0, 2},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-4, 2},
                    {-4, 3},
                    {-1, 3},
                    {-1, 4},
                    {-1, 5},
                    {0, 5},

                };
            DrawShape(row, column, offsets);
            return 5;
        case 8:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 3},
                    {-2, 3},
                    {-2, 2},
                    {-2, 1},
                    {0, 3},
                    {-3, 3},
                    {-1, 3},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 9:
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {0, 2},
                    {0, 3},
                    {0, 4},
                    {-1, 2},
                    {-2, 2},
                    {-3, 2},
                    {-4, 2},
                    {-4, 0},
                    {-4, 1},
                    {-4, 3},
                    {-4, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 10:
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},

                    {-1, 2},
                    {-2, 2},
                    {-3, 2},
                    {-4, 2},
                    {-4, 0},
                    {-4, 1},
                    {-4, 3},
                    {-4, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 11:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-2, 1},
                    {-1, 2},
                    {-3, 2},
                    {-4, 3},
                    {0, 3},
                    {-3, 0},
                    {-4, 0},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 12:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {0, 1},
                    {0, 2},
                    {0, 3},
                    {0, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 13:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-3, 1},
                    {-2, 2},
                    {-3, 3},
                    {-4, 4},
                    {-3, 4},
                    {-2, 4},
                    {-1, 4},
                    {-0, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 14:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-3, 1},
                    {-2, 2},
                    {-1, 3},
                    {0, 4},
                    {-4, 4},
                    {-3, 4},
                    {-2, 4},
                    {-1, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 15:
            offsets =
                {
                    {0, 3},
                    {0, 2},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-4, 2},
                    {-4, 3},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-1, 4},
                    {-2, 5},
                    {-3, 4},
                };
            DrawShape(row, column, offsets);
            return 5;
        case 16:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-3, 3},
                    {-2, 2},
                    {-2, 1},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 17:
            offsets =
                {
                    {0, 3},
                    {0, 2},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-4, 2},
                    {-4, 3},
                    {-1, 1},
                    {-2, 0},
                    {-3, 1},
                    {-1, 4},
                    {-2, 5},
                    {-3, 4},
                    {-2, 3},
                    {0, 5},
                };
            DrawShape(row, column, offsets);
            return 5;
        case 18:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-3, 3},
                    {-2, 2},
                    {-2, 1},
                    {-1, 3},
                    {0, 4},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 19:
            offsets =
                {
                    {0, 0}, // Current position
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 1},
                    {-4, 2},
                    {-4, 3},
                    {-2, 3},
                    {-2, 2},
                    {-2, 1},
                    {0, 3},
                    {0, 1},
                    {0, 2},
                    {-1, 3},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 20:
            offsets =
                {
                    {0, 2},
                    {-1, 2},
                    {-2, 2},
                    {-3, 2},
                    {-4, 2},
                    {-4, 0},
                    {-4, 1},
                    {-4, 3},
                    {-4, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 21:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 3},
                    {-2, 3},
                    {0, 3},
                    {0, 1},
                    {0, 2},
                    {-3, 3},
                    {-1, 3},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 22:
            offsets =
                {
                    {-1, 1},
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-4, 3},
                    {-2, 3},
                    {-1, 2},
                    {0, 1},
                    {0, 2},
                    {-3, 3},
                    {-1, 3},
                };
            DrawShape(row, column, offsets);
            return 3;
        case 23:
            offsets =
                {
                    {0, 2},
                    {-1, 2},
                    {-2, 2},
                    {-3, 2},
                    {-1, 1},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-1, 3},
                    {-2, 4},
                    {-3, 4},
                    {-4, 4},

                };
            DrawShape(row, column, offsets);
            return 4;
        case 24:
            offsets =
                {
                    {0, 0}, // Current position
                    {-1, 1},
                    {-2, 2},
                    {-3, 3},
                    {-4, 4},
                    {-4, 0},
                    {-3, 1},
                    {-1, 3},
                    {0, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 25:
            offsets =
                {
                    {-2, 2},
                    {-3, 3},
                    {-4, 4},
                    {-4, 0},
                    {-3, 1},
                    {-1, 2},
                    {0, 2},
                };
            DrawShape(row, column, offsets);
            return 4;
        case 26:
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {0, 2},
                    {0, 3},
                    {0, 4},
                    {-1, 1},
                    {-2, 2},
                    {-3, 3},
                    {-4, 2},
                    {-4, 0},
                    {-4, 1},
                    {-4, 3},
                    {-4, 4},
                };
            DrawShape(row, column, offsets);
            return 4;
        default:
            break;
        }
    }
    return 0;
}

void Grid::Heart(int row, int column, int rotate)
{
    if (IsValid(row, column))
    {
        vector<pair<int, int>> offsets;

        switch (rotate)
        {
        case 1: // Heading Southeast
            offsets =
                {
                    {0, -1}, // Main body
                    {0, -2},
                    {0, -3},
                    {0, -4},
                    {0, -5},
                    {-1, -6},
                    {-2, -6},
                    {-2, -5},
                    {-2, -4},
                    {-3, -4},
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-5, 0},
                    {-6, -1},
                    {-6, -2},
                    {-5, -2},
                    {-4, -2},
                    {-4, -3},
                    {2, -3}, // Bottom star
                    {3, -2},
                    {3, -4},
                    {4, -3},
                    {-3, 2}, // Top star
                    {-2, 3},
                    {-3, 4},
                    {-4, 3},
                };
            break;
        case 2: // Heading Northwest
            offsets =
                {
                    {0, -1}, // Main body
                    {0, -2},
                    {0, -3},
                    {0, -4},
                    {0, -5},
                    {1, -6},
                    {2, -6},
                    {2, -5},
                    {2, -4},
                    {3, -4},
                    {1, 0},
                    {2, 0},
                    {3, 0},
                    {4, 0},
                    {5, 0},
                    {6, -1},
                    {6, -2},
                    {5, -2},
                    {4, -2},
                    {4, -3},
                    {-2, -3}, // Bottom star
                    {-3, -2},
                    {-3, -4},
                    {-4, -3},
                    {3, 2}, // Top star
                    {2, 3},
                    {3, 4},
                    {4, 3},
                };
            break;
        case 3: // Heading Northeast
            offsets =
                {
                    {0, 1}, // Main body
                    {0, 2},
                    {0, 3},
                    {0, 4},
                    {0, 5},
                    {1, 6},
                    {2, 6},
                    {2, 5},
                    {2, 4},
                    {3, 4},
                    {1, 0},
                    {2, 0},
                    {3, 0},
                    {4, 0},
                    {5, 0},
                    {6, 1},
                    {6, 2},
                    {5, 2},
                    {4, 2},
                    {4, 3},
                    {-2, 3}, // Bottom star
                    {-3, 2},
                    {-3, 4},
                    {-4, 3},
                    {3, -2}, // Top star
                    {2, -3},
                    {3, -4},
                    {4, -3},
                };
            break;
        default: // Heading Southwest
            offsets =
                {
                    {0, 1}, // Main body
                    {0, 2},
                    {0, 3},
                    {0, 4},
                    {0, 5},
                    {-1, 6},
                    {-2, 6},
                    {-2, 5},
                    {-2, 4},
                    {-3, 4},
                    {-1, 0},
                    {-2, 0},
                    {-3, 0},
                    {-4, 0},
                    {-5, 0},
                    {-6, 1},
                    {-6, 2},
                    {-5, 2},
                    {-4, 2},
                    {-4, 3},
                    {2, 3}, // Bottom star
                    {3, 2},
                    {3, 4},
                    {4, 3},
                    {-3, -2}, // Top star
                    {-2, -3},
                    {-3, -4},
                    {-4, -3},
                };
            break;
        }

        DrawShape(row, column, offsets);
    }
}

void Grid::Glider(int row, int column, int rotate)
{
    if (IsValid(row, column))
    {
        vector<pair<int, int>> offsets;

        switch (rotate)
        {
        case 1: // Heading Southeast 
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {0, 2},
                    {-1, 0},
                    {-2, 1}
                };
            break;
        case 2: // Heading Northwest
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {0, 2},
                    {1, 0},
                    {2, 1}
                };
            break;
        case 3: // Heading Northeast
            offsets =
                {
                    {0, 0}, // Current position
                    {0, -1},
                    {0, -2},
                    {1, 0},
                    {2, -1}
                };
            break;
        default: // Heading Southwest
            offsets =
                {
                    {0, 0}, // Current position
                    {0, -1},
                    {0, -2},
                    {-1, 0},
                    {-2, -1}
                };
            break;
        }

        DrawShape(row, column, offsets);
    }
}

void Grid::Eater(int row, int column, int rotate)
{
    if (IsValid(row, column))
    {
        vector<pair<int, int>> offsets;

        switch (rotate)
        {
        case 1: // Eats from Southwest
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {-1, 1},
                    {-2, 1},
                    {-2, 3},
                    {-3, 3},
                    {-3, 2}
                };
            break;
        case 2: // Eats from Northwest
            offsets =
                {
                    {0, 0}, // Current position
                    {0, 1},
                    {1, 1},
                    {2, 1},
                    {2, 3},
                    {3, 3},
                    {3, 2}
                };
            break;
        case 3: // Eats from Northeast
            offsets =
                {
                    
                    {0, 0}, // Current position
                    {0, -1},
                    {1, -1},
                    {2, -1},
                    {2, -3},
                    {3, -3},
                    {3, -2}
                };
            break;
        default: // Eats from Southeast
            offsets =
                {
                    {0, 0}, // Current position
                    {0, -1},
                    {-1, -1},
                    {-2, -1},
                    {-2, -3},
                    {-3, -3},
                    {-3, -2}
                };
            break;
        }

        DrawShape(row, column, offsets);
    }
}

void Grid::GliderGun(int row, int column, int rotate)
{
    if (IsValid(row, column))
    {
        vector<pair<int, int>> offsets;

        switch (rotate)
        {
        case 1: // Shoots to Southwest
            offsets =
                {
                    // Main left body
                    {0, 0}, // Current position
                    {0, -2},
                    {0, -3},
                    {-1, -2},
                    {-2, -1},
                    {-3, 1},
                    {-3, 2},
                    {-2, 3},
                    {-1, 4},
                    {0, 4},
                    {1, 4},
                    {2, 3},
                    {3, 2},
                    {3, 1},
                    {2, -1},
                    {1, -2},
                    // Main right body
                    {-3, -6},
                    {-2, -6},
                    {-1, -6},
                    {-3, -7},
                    {-2, -7},
                    {-1, -7},
                    {0, -8},
                    {0, -10},
                    {1, -10},
                    {-4, -8},
                    {-4, -10},
                    {-5, -10},
                    // Right side square
                    {-3, -20},
                    {-3, -21},
                    {-2, -20},
                    {-2, -21},
                    // Left side square
                    {-1, 14},
                    {-1, 13},
                    {0, 13},
                    {0, 14}
                };
            break;
        case 2: // Eats from Northwest
            offsets =
                {
                    // Main left body
                    {0, 0}, // Current position
                    {0, -2},
                    {0, -3},
                    {1, -2},
                    {2, -1},
                    {3, 1},
                    {3, 2},
                    {2, 3},
                    {1, 4},
                    {0, 4},
                    {-1, 4},
                    {-2, 3},
                    {-3, 2},
                    {-3, 1},
                    {-2, -1},
                    {-1, -2},
                    // Main right body
                    {3, -6},
                    {2, -6},
                    {1, -6},
                    {3, -7},
                    {2, -7},
                    {1, -7},
                    {0, -8},
                    {0, -10},
                    {-1, -10},
                    {4, -8},
                    {4, -10},
                    {5, -10},
                    // Right side square
                    {3, -20},
                    {3, -21},
                    {2, -20},
                    {2, -21},
                    // Left side square
                    {1, 14},
                    {1, 13},
                    {0, 13},
                    {0, 14}
                };
            break;
        case 3: // Eats from Northeast
            offsets =
                {

                    {0, 0}, // Current position
                    {0, 2},
                    {0, 3},
                    {1, 2},
                    {2, 1},
                    {3, -1},
                    {3, -2},
                    {2, -3},
                    {1, -4},
                    {0, -4},
                    {-1, -4},
                    {-2, -3},
                    {-3, -2},
                    {-3, -1},
                    {-2, 1},
                    {-1, 2},
                    // Main right body
                    {3, 6},
                    {2, 6},
                    {1, 6},
                    {3, 7},
                    {2, 7},
                    {1, 7},
                    {0, 8},
                    {0, 10},
                    {-1, 10},
                    {4, 8},
                    {4, 10},
                    {5, 10},
                    // Right side square
                    {3, 20},
                    {3, 21},
                    {2, 20},
                    {2, 21},
                    // Left side square
                    {1, -14},
                    {1, -13},
                    {0, -13},
                    {0, -14}};
            break;
        default: // Shoots to Southeast
            offsets =
                {
                    // Main left body
                    {0, 0}, // Current position
                    {0, 2},
                    {0, 3},
                    {-1, 2},
                    {-2, 1},
                    {-3, -1},
                    {-3, -2},
                    {-2, -3},
                    {-1, -4},
                    {0, -4},
                    {1, -4},
                    {2, -3},
                    {3, -2},
                    {3, -1},
                    {2, 1},
                    {1, 2},
                    // Main right body
                    {-3, 6},
                    {-2, 6},
                    {-1, 6},
                    {-3, 7},
                    {-2, 7},
                    {-1, 7},
                    {0, 8},
                    {0, 10},
                    {1, 10},
                    {-4, 8},
                    {-4, 10},
                    {-5, 10},
                    // Right side square
                    {-3, 20},
                    {-3, 21},
                    {-2, 20},
                    {-2, 21},
                    // Left side square
                    {-1, -14},
                    {-1, -13},
                    {0, -13},
                    {0, -14}
                };
            break;
        }

        DrawShape(row, column, offsets);
    }
}

void Grid::GateNot(int row, int column)
{
    GliderGun(row, column, 0);
    GliderGun(row, column + 70, 1);
    Eater(row + 20, column + 25, 0);
    Eater(row + 50, column + 15, 1);
}
