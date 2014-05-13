//
//  Interface.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/22/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_Interface_h
#define HelloSDL_Interface_h

#include "CEntity.h"
#include "Define.h"
#include "CArea.h"
#include "Camara.h"




class Game
{
private:
    SDL_Surface *screen;
    bool running;
    bool FullScreen;
    bool dale;
    
    CEntity Efis;
    CEntity Brure;
    CEntity Fira;
    CEntity Chara;
    CMap    Map;
    CCamera Camara;

public:
    Game();                                             // Constructor
    int SurfMenu(int option);                           // Cambiar Superficie del menu
    int OnExecute(SDL_Event *Event_Menu);               // Ciclo principal de la aplicacion

    int  OnGame();                                      // Ciclo principal del juego
    bool OnInit();                                      // Inicializar modulos de SDL
    bool OnEvent(SDL_Event *Event);                     // Acciones a tomar cuando ocurre un Evento
    void OnLoop();                                      // Acciones a tomar si no ocurre un Evento
    int  OnRender();                                    // Renderizar todos objetos
    void OnCleanup();                                   // Cerrar y Limpiar aputadores de SDL
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

Game::Game()
{
    dale=true;
    running = true;
    FullScreen=false;
}

void Game::OnCleanup()
{
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnCleanup();
    }
    
    CEntity::EntityList.clear();
    CArea::AreaControl.OnCleanup();
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_UP:      CCamera::CameraControl.OnMove( 0,  5); break;
        case SDLK_DOWN:  CCamera::CameraControl.OnMove( 0, -5); break;
        case SDLK_LEFT:  CCamera::CameraControl.OnMove( 5,  0); break;
        case SDLK_RIGHT: CCamera::CameraControl.OnMove(-5,  0); break;
            
        default: {
        }
    }
}


#endif
