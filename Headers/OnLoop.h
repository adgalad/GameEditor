//
//  OnLoop.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/25/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "Game.h"

#ifndef HelloSDL_OnLoop_h
#define HelloSDL_OnLoop_h



void Game::OnLoop()
{
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnLoop();
    }

}





#endif
