/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

// types and structures:
typedef enum ChangeState{
    MENU = 0,
    GAMEPLAY,
    INVENTORY,
    PAUSE,
    GAMEOVER,
    ENDGAME
    
}ChangeState;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    ChangeState current_screen = MENU;
    
    int frame_counter = 0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        // making a state machine to the game
        switch(current_screen){
            case MENU{
                
                frame_counter++;
                
                if(frame_counter>120){
                    if(IsKeyPressed(KEY_ENTER)){
                       current_screen = GAMEPLAY;
                    }
                }
                
                
            }break;
            case GAMEPLAY {
                
                if(IsKeyPressed(KEY_p)){
                    
                    current_screen = PAUSE;
                    
                }
                
            }break;
            case PAUSE{
                
                if(IsKeyPressed(KEY_p)){
                    
                    current_screen = GAMEPLAY;
                    
                }
                
            }break;
            default:break;
            
        }
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            switch(current_screen){
                case MENU{
                
                    DrawText("Menu Principal", 20,20,40, LIGHTGRAY);
                    DrawText("Press ENTER to start the adventure", 290,300,20, LIGHTGRAY);
                
                }break;
                case GAMEPLAY{
                    
                    DrawText("Now you're playing", 20,20,40, LIGHTGRAY);
                    DrawText("Press P to pause the game", 290,300,20, LIGHTGRAY);
                
                }break;
                case PAUSE{
                    
                    DrawText("Game Paused", 20,20,40, LIGHTGRAY);
                    DrawText("Press P to return", 290,300,20, LIGHTGRAY);
                
                }break;
                default: break;
            }
        

            

           

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}