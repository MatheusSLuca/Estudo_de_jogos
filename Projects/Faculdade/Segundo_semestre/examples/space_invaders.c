
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LASERS 1;
#define SHIP_SIZE 40
#define LASER_SPEED 10


struct Laser{
    Vector2 pos;
    bool active;
}Laser;

struct Ship{
    Vector2 pos;
}Ship;

void Move_Player(Ship *ship){
    if (IsKeyDown(KEY_RIGHT)) ship->pos.x += pj_speed;
    if (IsKeyDown(KEY_LEFT)) ship->pos.x -= pj_speed;
    if (IsKeyDown(KEY_DOWN)) ship->pos.y += pj_speed;
    if (IsKeyDown(KEY_UP)) ship->pos.y -= pj_speed;
}
void Verify_out__screen(Ship *ship){
    if (ship->pos.x <= 0 && !IsKeyDown(KEY_RIGHT)){
            pj_speed = 0.0;
            }
        if(ship->pos.x > (float)screen_width && !IsKeyDown(KEY_LEFT) | IsKeyDown(KEY_RIGHT)){
            
            pj_speed = 0;
            
        }
        if (ship->pos.x >= (float)screen_width && IsKeyDown(KEY_LEFT)){
            
            pj_speed = 10.0;
            
        }
        if (ship->pos.x <= 0 && IsKeyDown(KEY_RIGHT)){
                pj_speed = 10.0;
                
            }
            
        // não deixar o player sair da tela no eixo y
        if (ship->pos.y <= 0 && !IsKeyDown(KEY_DOWN)){
            pj_speed = 0.0;
            }
        if(ship->pos.y > (float)screen_height && !IsKeyDown(KEY_UP) | IsKeyDown(KEY_DOWN)){
            
            pj_speed = 0;
            
        }
        if (ship->pos.y >= (float)screen_height && IsKeyDown(KEY_UP)){
            
            pj_speed = 10.0;
            
        }
        if (ship->pos.y <= 0 && IsKeyDown(KEY_DOWN)){
                pj_speed = 10.0;
                
            }
            
}
void FireLaser(Laser *lasers, Ship *ship, int *nextLaser) {
    if (IsKeyDown(KEY_SPACE)) {
        lasers[*nextLaser].active = true;
        lasers[*nextLaser].pos.x = ship->pos.x + SHIP_SIZE;
        lasers[*nextLaser].pos.y = ship->pos.y + SHIP_SIZE / 2;
        *nextLaser = (*nextLaser + 1) % MAX_LASERS;
    }
}

// Função para atualizar a posição dos lasers
void UpdateLasers(Laser *lasers) {
    for (int i = 0; i < MAX_LASERS; i++) {
        if (lasers[i].active) {
            lasers[i].pos.x += LASER_SPEED;
        }
    }
}

// Função para desenhar a cena
void Draw(Ship *ship, Laser *lasers) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(ship->pos.x, ship->pos.y, SHIP_SIZE, SHIP_SIZE, BLUE);
    for (int i = 0; i < MAX_LASERS; i++) {
        if (lasers[i].active) {
            DrawRectangle(lasers[i].pos.x, lasers[i].pos.y, 10, 2, RED);
        }
    }
    EndDrawing();
}
int main(void){


    Color grey = {29, 29, 27, 255};
    const int screen_height = 800;
    const int screen_width = 1200;
    
    InitWindow(screen_width,screen_height,"SpaceInvaders");
    
    SetTargetFPS(60);

    //character attributes
    Ship ship = { {screen_width / 4, screen_height / 2} };
    Laser lasers[MAX_LASERS] = { 0 };
    int nextLaser = 0;

    
    
    
    
    while(!WindowShouldClose()){
        
        MoveShip(&ship);
        FireLaser(lasers, &ship, &nextLaser);
        UpdateLasers(lasers);
        Draw(&ship, lasers);
        
        
        
    }
    
    
        
        
        
    
    
    CloseWindow();
    return 0;
}