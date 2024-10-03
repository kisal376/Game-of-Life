#pragma once
#include <vector>

using namespace std;

class Grid
{
    public:
        Grid(int width, int height, int cellSize)
        : rows(height/cellSize), columns(width/cellSize), cellSize(cellSize), cells(rows, vector<int>(columns, 0)), prevCell(pair<int,int>(0,0), -1) {}; // Initialiser List

        void Draw();

        void SetValue(int row, int column, int value);

        int GetValue(int row, int column);

        bool IsValid(int row, int column);

        int GetRows(){return rows;};
        int GetCols(){return columns;};

        void RandomStart();

        void Clear();

        void ToggleCell(int row, int column);

        void Hover(int row, int column);

        void DrawShape(int row, int column, vector<pair<int, int>> offsets);
        
        int Letters(int row, int column, int letter);
        void Heart(int row , int column, int rotate);

        void Glider(int row, int column, int rotate);
        void Eater(int row, int column, int rotate);
        void GliderGun(int row, int column, int rotate);

        void GateNot(int row, int column);


    private:
        int rows;
        int columns;
        int cellSize;
        vector<vector<int>> cells;
        pair<pair<int, int>, int> prevCell;
};