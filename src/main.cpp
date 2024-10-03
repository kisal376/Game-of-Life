#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

using namespace std;

int main()
{
    // Initialize constants
    const int WINDOW_WIDTH = 1500;
    const int WINDOW_HEIGHT = 1500;
    int CELL_SIZE = 10;
    int defaultFPS = 10;
    int highFPS = 40;
    int lowFPS = 1;
    Color GREY = {30, 30, 30, 255}; // type Color takes in rgbα values

    vector<bool> selected{true, false, false, false, false, false};
    const int NONE = 0;
    const int HEART = 1;
    const int GLIDER = 2;
    const int EATER = 3;
    const int GLIDERGUN = 4;
    const int NOTGATE = 5;
    int currentSelection = NONE;
    Vector2 position;
    Vector2 cursor;
    int rotation = 0;

    bool keyboardMode = false;
    bool typing = false;

    // Create simulation window at the desired position
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life, Read Instructions, or press P");
    SetTargetFPS(defaultFPS);
    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    // Simulation loop
    while (WindowShouldClose() == false)
    {
        // 1. Event Handling

        // Toggle keyboard mode
        if (!typing)
        {
            if (IsKeyPressed(KEY_K))
            {
                keyboardMode = !keyboardMode;
                if (keyboardMode)
                {
                    SetWindowTitle("In Keyboard Mode");
                    position.x = WINDOW_WIDTH / 2;
                    position.y = WINDOW_HEIGHT / 2;
                }
                else
                {
                    SetWindowTitle("In Mouse Mode");
                    position = GetMousePosition();
                }
            }
        }

        // Handle movement in keyboard mode
        if (keyboardMode)
        {
            if (IsKeyDown(KEY_LEFT) || IsKeyPressed(KEY_LEFT))
            {
                position.x = (position.x > CELL_SIZE) ? position.x - CELL_SIZE : 0;
            }
            else if (IsKeyDown(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT))
            {
                position.x = (position.x < WINDOW_WIDTH - CELL_SIZE) ? position.x + CELL_SIZE : WINDOW_WIDTH;
            }
            else if (IsKeyDown(KEY_DOWN) || IsKeyPressed(KEY_DOWN))
            {
                position.y = (position.y < WINDOW_HEIGHT - CELL_SIZE) ? position.y + CELL_SIZE : WINDOW_HEIGHT;
            }
            else if (IsKeyDown(KEY_UP) || IsKeyPressed(KEY_UP))
            {
                position.y = (position.y > CELL_SIZE) ? position.y - CELL_SIZE : 0;
            }

            // Place glider or toggle cell in keyboard mode
            if (IsKeyDown(KEY_J))
            {
                if (selected[NONE])
                {
                    simulation.ToggleCell(position.y / CELL_SIZE, position.x / CELL_SIZE);
                }
                else if (selected[GLIDER])
                {
                    simulation.DrawGlider(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[EATER])
                {
                    simulation.DrawEater(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[GLIDERGUN])
                {
                    simulation.DrawGliderGun(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[NOTGATE])
                {
                    simulation.DrawNotGate(position.y / CELL_SIZE, position.x / CELL_SIZE);
                }
                else if (selected[HEART])
                {
                    simulation.DrawHeart(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
            }

            simulation.Hovering(position.y / CELL_SIZE, position.x / CELL_SIZE);
        }
        else // Mouse mode
        {
            position = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (selected[NONE])
                {
                    simulation.ToggleCell(position.y / CELL_SIZE, position.x / CELL_SIZE);
                }
                else if (selected[GLIDER])
                {
                    simulation.DrawGlider(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[EATER])
                {
                    simulation.DrawEater(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[GLIDERGUN])
                {
                    simulation.DrawGliderGun(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
                else if (selected[NOTGATE])
                {
                    simulation.DrawNotGate(position.y / CELL_SIZE, position.x / CELL_SIZE);
                }
                else if (selected[HEART])
                {
                    simulation.DrawHeart(position.y / CELL_SIZE, position.x / CELL_SIZE, rotation);
                }
            }
            else
            {
                simulation.Hovering(position.y / CELL_SIZE, position.x / CELL_SIZE);
            }
        }

        // Simulation state controls
        if (IsKeyPressed(KEY_ENTER))
        {
            SetWindowTitle("Simulation running, Press right shift to stop");
            selected[currentSelection] = false;
            selected[NONE] = true;
            currentSelection = NONE;
            simulation.Start();
        }
        else if (IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            SetWindowTitle("Paused, Click to populate, Press Enter to continue");
            selected[currentSelection] = false;
            selected[NONE] = true;
            currentSelection = NONE;
            simulation.Stop();
        }

        // FPS controls
        if (!typing)
        {
            if (IsKeyPressed(KEY_F))
            {
                if (defaultFPS < highFPS)
                {
                    defaultFPS += 2;
                    SetTargetFPS(defaultFPS);
                }
            }
            else if (IsKeyPressed(KEY_S))
            {
                if (defaultFPS > 2)
                {
                    defaultFPS -= 2;
                    SetTargetFPS(defaultFPS);
                }
                if (defaultFPS == 2)
                {
                    defaultFPS = 1;
                    SetTargetFPS(defaultFPS);
                }
            }

            if (simulation.IsRunning())
            {
                if (IsKeyDown(KEY_LEFT_SHIFT))
                {
                    SetWindowTitle("Simulation Running at Max Speed");
                    SetTargetFPS(highFPS);
                }
                else if (IsKeyReleased(KEY_LEFT_SHIFT))
                {
                    SetWindowTitle("Simulation running, Press right shift to stop");
                }
                else if (IsKeyDown(KEY_LEFT_CONTROL))
                {
                    SetWindowTitle("Simulation Running at Min Speed");
                    SetTargetFPS(lowFPS);
                }
                else if (IsKeyReleased(KEY_LEFT_CONTROL))
                {
                    SetWindowTitle("Simulation running, Press right shift to stop");
                }
                else
                {
                    SetTargetFPS(defaultFPS);
                }
            }

            // Grid controls
            if (IsKeyPressed(KEY_C))
            {
                simulation.ClearGrid();
            }
            else if (IsKeyPressed(KEY_P))
            {
                SetWindowTitle("Randomly populated, Press Enter to start simulation");
                simulation.MakeRandomState();
            }

            // Draw shape toggle
            else if (IsKeyPressed(KEY_H))
            {
                if (selected[HEART])
                {
                    selected[HEART] = false;
                    currentSelection = NONE;
                    SetWindowTitle("Paused, Click to populate, Press Enter to continue");
                    selected[NONE] = true;
                }
                else
                {
                    selected[currentSelection] = false;
                    currentSelection = HEART;
                    SetWindowTitle("Selected Heart, Click to populate, Press Enter to start simulation");
                    selected[HEART] = true;
                    rotation = 0;
                }
            }
            else if (IsKeyPressed(KEY_G))
            {
                if (selected[GLIDER])
                {
                    selected[GLIDER] = false;
                    currentSelection = NONE;
                    SetWindowTitle("Paused, Click to populate, Press Enter to continue");
                    selected[NONE] = true;
                }
                else
                {
                    selected[currentSelection] = false;
                    currentSelection = GLIDER;
                    SetWindowTitle("Selected Glider, Click to populate, Press Enter to start simulation");
                    selected[GLIDER] = true;
                    rotation = 0;
                }
            }
            else if (IsKeyPressed(KEY_E))
            {
                if (selected[EATER])
                {
                    selected[EATER] = false;
                    currentSelection = NONE;
                    SetWindowTitle("Paused, Click to populate, Press Enter to continue");
                    selected[NONE] = true;
                }
                else
                {
                    selected[currentSelection] = false;
                    currentSelection = EATER;
                    SetWindowTitle("Selected Eater, Click to populate, Press Enter to start simulation");
                    selected[EATER] = true;
                    rotation = 0;
                }
            }
            else if (IsKeyPressed(KEY_Q))
            {
                if (selected[GLIDERGUN])
                {
                    selected[GLIDERGUN] = false;
                    currentSelection = NONE;
                    SetWindowTitle("Paused, Click to populate, Press Enter to continue");
                    selected[NONE] = true;
                }
                else
                {
                    selected[currentSelection] = false;
                    currentSelection = GLIDERGUN;
                    SetWindowTitle("Selected Glider Gun, Click to populate, Press Enter to start simulation");
                    selected[GLIDERGUN] = true;
                    rotation = 0;
                }
            }
            else if (IsKeyPressed(KEY_N))
            {
                if (selected[NOTGATE])
                {
                    selected[NOTGATE] = false;
                    currentSelection = NONE;
                    SetWindowTitle("Paused, Click to populate, Press Enter to continue");
                    selected[NONE] = true;
                }
                else
                {
                    selected[currentSelection] = false;
                    currentSelection = NOTGATE;
                    SetWindowTitle("Selected Not Gate, Click to populate, Press Enter to start simulation");
                    selected[NOTGATE] = true;
                    rotation = 0;
                }
            }
            else if (IsKeyPressed(KEY_R))
            {
                if (!selected[NONE])
                {
                    rotation++;
                    rotation %= 4;
                }
            }
        }else
        {
            if (cursor.x > WINDOW_WIDTH - (CELL_SIZE*10))
            {
                cursor.x = CELL_SIZE * 10;
                cursor.y += CELL_SIZE * 10;
            }
            if (cursor.y > WINDOW_HEIGHT - (CELL_SIZE*5))
            {
                cursor.x = CELL_SIZE * 10;
                cursor.y = CELL_SIZE * 10;
            }
            if (IsKeyPressed(KEY_A))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 1) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_B))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 2) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_C))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 3) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_D))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 4) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_E))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 5) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_F))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 6) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_G))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 7) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_H))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 8) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_I))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 9) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_I))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 9) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_J))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 10) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_K))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 11) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_L))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 12) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_M))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 13) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_N))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 14) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_O))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 15) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_P))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 16) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_Q))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 17) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_R))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 18) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_S))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 19) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_T))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 20) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_U))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 21) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_V))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 22) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_W))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 23) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_X))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 24) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_Y))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 25) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_Z))
            {
                cursor.x = cursor.x + (simulation.Type(cursor.y / CELL_SIZE, cursor.x / CELL_SIZE, 26) * (CELL_SIZE));
            }
            else if (IsKeyPressed(KEY_SPACE))
            {
                cursor.x = cursor.x + 7 * (CELL_SIZE);
            }
        }

        if (IsKeyPressed(KEY_TAB))
        {
            typing = !typing;
            if (typing)
            {
                keyboardMode = false;
                selected[currentSelection] = false;
                cursor.x = 10*CELL_SIZE;
                cursor.y = 10*CELL_SIZE;
            }
            else
            {
                keyboardMode = keyboardMode; 
                selected[currentSelection] = true;
            }
            
        }
        
        

        // 2. Updating the State
        simulation.Update();

        // 3. Drawing
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

    // Destroy simulation window
    CloseWindow();
}
