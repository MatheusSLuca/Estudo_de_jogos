#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "rlgl.h"
#include <math.h>

#define MAX_BULLETS 100
#define MAX_ENEMIES 20

// sintaxe de vetores
// <type> <name>[<size>];


struct ammo{
    int dano;
    Model model;
    Texture2D texture;
    Vector3 position;
    float x_speed;
    
    
};

struct ammo_enemy{
    int dano;
    Model model;
    Texture2D texture;
    Vector3 position;
    float x_speed;
    
    
};

struct enemy{
    Model model;
    Vector3 position;
    float x_speed;
    float y_speed;
    int life;
};

typedef struct ammo Ammo;
typedef struct ammo_enemy Enemy_ammo;
typedef struct enemy Enemy;



int main(void){
    int counter = 0;
    float enemycounter = 0;
    float time;
    double current_time;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 10.0f}; // posição da camera
    camera.target = (Vector3){0.0f,0.0f,0.0f}; // camera loking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f}; //camera up vector (rotaion toward the target)
    camera.fovy = 100.0f; //field of view y
    camera.projection = CAMERA_PERSPECTIVE; //camera mode
    
    Vector3 cubeposition = {0.0f,0.0f,0.0f};
    Vector3 sizecube = {1.0f,1.0f,1.0f};
    
    //munições
    Model ammo = LoadModel("bala/45/45.obj");
    BoundingBox ammo_box = GetModelBoundingBox(Model ammo);
    Model enemy_ammo = LoadModel("bala/45/45.obj");
    BoundingBox enemy_ammo_box = GetModelBoundingBox(Model enemy_ammo);
    Texture2D texture = LoadTexture("bala/45/tex_2/bullet.jpg");
    ammo.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    enemy_ammo.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    
    //nave inimiga
    Model spaceship = LoadModel("nave_inimiga.glb");
    Vector3 enemy_position = {15.0f,0.0f,0.0f};
    Enemy enemy = {spaceship,enemy_position,0.5f,1.0f,3};
    Enemy array_enemies[MAX_ENEMIES];
    float nave_rotation = 0.0f;
    
    Vector3 ammo_position = {5.0f,0.0f,0.0f};
    Vector3 ammo_enemy_pos = {0.0f,0.0f,0.0f};
    BoundingBox bounds = GetMeshBoundingBox(ammo.meshes[0]);   // Set model bounds
    Ammo array_ammo[MAX_BULLETS];
    Enemy_ammo array_enemie_ammo[MAX_BULLETS];
    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    
    bool laser_shot = false;
    bool enemy_can_shoot = false;
    SetTargetFPS(60);
    
    
    
    void MovePlayer(){
    if(IsKeyDown(KEY_RIGHT)){
            cubeposition.x += 0.5f;
        }
        if(IsKeyDown(KEY_LEFT)){
            cubeposition.x -= 0.5f;
        }
        if(IsKeyDown(KEY_UP)){
            cubeposition.y += 0.5f;
        }
        if(IsKeyDown(KEY_DOWN)){
            cubeposition.y -= 0.5f;
        }
      
};
    
    while(!WindowShouldClose()){
        
        current_time = GetTime();
        
        // Verify the x position of the bullet and then delete it if it's higher than screenWidth
        for (int i = 0; i < counter; i++){
            if(array_ammo[i].position.x > screenWidth){
                counter-=1;
                array_ammo[i] = array_ammo[i+1];
                
            }
        }
        
        
        MovePlayer();
        
        //update move from enemy
        
        //Enemy follow player on Y-axis
        ammo_enemy_pos = enemy.position;
        if(enemy.position.y > cubeposition.y){
            enemy.position.y -= 0.1f;
        }
        if(enemy.position.y < cubeposition.y){
            enemy.position.y += 0.1f;
        }
        //enemy shoot
        if(enemy.position.y == cubeposition.y){
            time = GetFrameTime();
            enemy_can_shoot = true;
        }
        
        if(enemy_can_shoot){
            Enemy_ammo new_ammunition = {10,enemy_ammo, texture, ammo_enemy_pos, 2.0f};
            new_ammunition.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = new_ammunition.texture;
            BoundingBox bounds = GetMeshBoundingBox(new_ammunition.model.meshes[0]); 
            
            array_enemie_ammo[(int)enemycounter] = new_ammunition;
            enemycounter += 0.01f;
            for(int i = 0; i < (int)enemycounter; i++){
                array_enemie_ammo[i].position.x -= array_enemie_ammo[i].x_speed;
            }
        }
        
        
        
        
        // atirar e "instanciar" um novo ammo struct
        if(IsKeyPressed(KEY_SPACE)){
            ammo_position = cubeposition;
            Ammo new_ammo = {10,ammo, texture, ammo_position, 2.0f};
            new_ammo.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = new_ammo.texture;
            BoundingBox bounds = GetMeshBoundingBox(new_ammo.model.meshes[0]);
            array_ammo[counter] = new_ammo;
            counter+=1;
            laser_shot = true;
            
        }
        if(laser_shot){
            for(int i = 0; i < counter; i++){
                
                 array_ammo[i].position.x += array_ammo[i].x_speed;
                
            }
            
        }
        if()
        
        
        //drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            
                DrawCubeV(cubeposition,sizecube, BLUE);
                if(laser_shot){
                    
                    for(int i = 0; i < counter; i++){
                        DrawModel(array_ammo[i].model, array_ammo[i].position, 1.0f, WHITE);
                    }
                }
                
                
                rlPushMatrix();
                    rlRotatef(nave_rotation, 0.0f, 1.0f, 0.0f);
                    DrawModel(enemy.model,enemy.position,1.0f,WHITE);
                    
                rlPopMatrix();
                if(enemy_can_shoot){
                     for(int i = 0; i < (int)enemycounter; i++){
                         DrawModel(array_enemie_ammo[i].model,array_enemie_ammo[i].position, 1.0f, WHITE);
                     }
                }
                
                DrawGrid(10, 1.0f);
            EndMode3D();
            
        EndDrawing();
    }
    
    UnloadTexture(texture);     // Unload texture
    UnloadModel(ammo);        
    CloseWindow();
    
    return 0;
}