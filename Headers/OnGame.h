//
//  OnGame.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/25/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "OnEvent.h"
#include "OnLoop.h"
#include "OnRender.h"

#ifndef HelloSDL_OnGame_h
#define HelloSDL_OnGame_h




int Game::OnGame()
{
    SDL_Event Event;
    while(running)
    {
        while(SDL_PollEvent(&Event)){
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
    }
    return 0;
}


#endif
