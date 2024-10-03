#pragma once
#include "grid.hpp"

class Simulation
{
    public:
        Simulation(int width, int height, int cellSize)
            : grid(width, height, cellSize), tempGrid(width, height, cellSize), run(false) {};

        void Draw();

        void SetCellValue(int row, int column, int value);

        int CountLiveNeighbors(int row, int column);

        void Update();

        bool IsRunning(){return run;};
        void Stop(){run = false;};
        void Start(){run = true;};

        void ClearGrid();

        void MakeRandomState();

        void ToggleCell(int row, int column);

        void Hovering(int row, int column);

        int Type(int row, int column, int letter);
        void DrawHeart(int row, int column, int rotate);

        void DrawGlider(int row, int column, int rotate);
        void DrawEater(int row, int column, int rotate);
        void DrawGliderGun(int row, int column, int rotate);

        void DrawNotGate(int row, int column);

    private:
        Grid grid;
        Grid tempGrid;
        bool run;
};