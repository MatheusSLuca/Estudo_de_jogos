#include "raylib.h" 

// Estados do player
typedef enum PlayerStates{
    IDLE = 0,
    WALKING,
    RUNNING,
    PAUSED,
    ATTACKING,
    TAKINGDAMAGE
}PlayerStates;


// Classe player
typedef struct{
    //parametros:
    const max_speed;
    float current_speed;
    Texture2D sprite_rec;
    Vector2 position;
    Rectangle frameRec;
    
    
    
    //metodos:
    int (*change_animation)(int);
    int (*draw_animation)(Texture2D, Color);
    
}Player;

//funções e metodos:
int ChangeAnimation(int index);
int FuncaoConstrutura(Player*ObjetoAlvo);

//funcao construtura
int FuncaoConstrutura(Player * ObjetoAlvo){
    if(ObjetoAlvo == Null){
        return 0;
    }
    ObjetoAlvo-> max_speed = 50.0;
    ObjetoAlvo-> 
    
}

void main(void){
    
    
    
    
    
    
}


