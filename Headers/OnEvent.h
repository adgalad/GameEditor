//
//  OnEvent.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/25/14.
//  Copyright (c) 2014 Student. All rights reserved.
//
#include "Game.h"

#ifndef HelloSDL_OnEvent_h
#define HelloSDL_OnEvent_h

bool Game::OnEvent(SDL_Event *Event)
{
    switch (Event->type) {
        case SDL_KEYDOWN:
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->Anim=true;
            }
            if (Event->key.keysym.sym == SDLK_DOWN)
            {
                Efis.AnimState=1;
            Fira.AnimState=1;
            Chara.AnimState=1;
            Brure.AnimState=1;
                CCamera::CameraControl.OnMove(0, -5);
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->Y++;
            }
            }
            
            else if (Event->key.keysym.sym == SDLK_LEFT)
            {
                Efis.AnimState=2;
            Fira.AnimState=2;
            Chara.AnimState=2;
            Brure.AnimState=2;
                CCamera::CameraControl.OnMove(5,  0);
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->X--;
            }
            }
            
            else if (Event->key.keysym.sym == SDLK_RIGHT)
            {
                Efis.AnimState=3;
            Fira.AnimState=3;
            Chara.AnimState=3;
            Brure.AnimState=3;
                CCamera::CameraControl.OnMove(-5,  0);
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->X++;
            }
            }
            
            else if (Event->key.keysym.sym == SDLK_UP)
            {
                Efis.AnimState=4;
            Fira.AnimState=4;
            Chara.AnimState=4;
            Brure.AnimState=4;
                CCamera::CameraControl.OnMove(0,  5);
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->Y--;
            }
            }
            else if (Event->key.keysym.sym == SDLK_ESCAPE)
            {
                running=false;
            }
            break;
        case SDL_KEYUP:
            for(int i = 0;i < CEntity::EntityList.size();i++) {
                if(!CEntity::EntityList[i]) continue;
                
                CEntity::EntityList[i]->Anim=false;
            }
            break;
        case SDL_QUIT:
            running=false;
            break;
        default:
            break;
    }
    
    return 0;
}


#endif
