//
//  OnRender.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/25/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "Game.h"


#ifndef HelloSDL_OnRender_h
#define HelloSDL_OnRender_h



int Game::OnRender()
{
    CArea::AreaControl.OnRender(screen, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnRender(screen);
    }

    SDL_Flip(screen);
    return 0;
}


#endif
