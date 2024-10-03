#include "simulation.hpp"
#include <vector>

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;

    vector<pair<int,int>> offsets = 
    {
        {-1, 0}, // North
        {-1, 1}, // Northeast
        {0, 1}, //East
        {1, 1}, //Southeast
        {1, 0}, // South
        {1, -1}, // Southwest
        {0, -1}, //West
        {-1, -1} //Northwest
    };

    for (const auto& offset : offsets)
    {
        // liveNeighbors += grid.GetValue(row + offset.first, column + offset.second); // since live cell = 1  add living cell to live neighbours
        
        //implementing grid wrap for unbounded grid.
        liveNeighbors += grid.GetValue((row + offset.first + grid.GetRows()) % grid.GetRows(), (column + offset.second + grid.GetCols()) % grid.GetCols()); // Takes neighbours on other side of the grid into account
    }
    return liveNeighbors;
}

void Simulation::Update()
{
    if(IsRunning())
    {
        for (int row = 0; row < grid.GetRows(); row++)
        {
            for (int col = 0; col < grid.GetCols(); col++)
            {
                int liveNeighbors = CountLiveNeighbors(row, col);
                int cellValue = grid.GetValue(row, col);

                // Cell is alive
                if (cellValue)
                {
                    if (liveNeighbors > 3 || liveNeighbors < 2) // Cell will die if live neighbours are more than 3 or less than 2
                    {
                        tempGrid.SetValue(row, col, 0);
                    }
                    else
                    {
                        tempGrid.SetValue(row, col, 1);
                    }
                }
                else // Cell is dead
                {
                    if (liveNeighbors == 3) // A dead cell with exactly 3 live neighbors will become alive
                    {
                        tempGrid.SetValue(row, col, 1);
                    }
                    else
                    {
                        tempGrid.SetValue(row, col, 0);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::ClearGrid()
{
    if (!IsRunning())
    {
        grid.Clear();
    }
}

void Simulation::MakeRandomState()
{
    if (!IsRunning())
    {
        grid.RandomStart();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if (!IsRunning())
    {
        grid.ToggleCell(row, column);
    }
}

void Simulation::Hovering(int row, int column)
{
    if (!IsRunning())
    {
        grid.Hover(row, column);
    }
}

int Simulation::Type(int row, int column, int letter)
{
    if (!IsRunning())
    {
        return (grid.Letters(row, column, letter) + 3);
    }
    
}

void Simulation::DrawHeart(int row, int column, int rotate)
{
    if (!IsRunning())
    {
        grid.Heart(row, column, rotate);
    }
}

void Simulation::DrawGlider(int row, int column, int rotate)
{
    if (!IsRunning())
    {
        grid.Glider(row, column, rotate);
    }
}

void Simulation::DrawEater(int row, int column, int rotate)
{
    if (!IsRunning())
    {
        grid.Eater(row, column, rotate);
    }
}

void Simulation::DrawGliderGun(int row, int column, int rotate)
{
    if (!IsRunning())
    {
        grid.GliderGun(row, column, rotate);
    }
}

void Simulation::DrawNotGate(int row, int column)
{
    if (!IsRunning())
    {
        grid.GateNot(row, column);
    }
}