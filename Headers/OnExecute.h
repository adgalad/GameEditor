//
//  main.h
//  HelloSDL
//
//  Created by Richard Carter on 5/30/11.
//  Copyright 2011 Richard Carter. All rights reserved.
//
#include <iostream>
#include "OnGame.h"
#include "OnInit.h"

int Game::SurfMenu(int option)
{
    
    return 0;
}



int Game::OnExecute(SDL_Event *Event_Menu)
{
    OnInit();
    OnGame();
    SDL_Quit();
    return 0;
}



