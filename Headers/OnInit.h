//
//  OnInit.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/26/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "Game.h"

bool Game::OnInit()
{
    
    /* Init SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }
    const SDL_VideoInfo *VideoInfo;
    VideoInfo = SDL_GetVideoInfo();

       /* Set Video Mode */
    if ((screen=SDL_SetVideoMode(VideoInfo->current_w,VideoInfo->current_h-200, 32, SDL_HWSURFACE|SDL_DOUBLEBUF))==NULL)
    {
        return false;
    }
    
    /* Set Unicode Translate */
    SDL_EnableUNICODE(1);
    
    /* Enable Key Repeat */
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    
    /* LOAD MAP */
    Camara.SetPos(500,500);
    if(CArea::AreaControl.OnLoad("1.area") == false) {
        return false;
    }
    
    /* LOAD ENTITIES */

    if(Efis.OnLoad("Efis.png", 32, 32, 3) == false) {
        return false;
    }
    if(Brure.OnLoad("Brure.png", 32, 32, 3) == false) {
        return false;
    }
    if(Chara.OnLoad("Chara.png", 32, 32, 3) == false) {
        return false;
    }
    if(Fira.OnLoad("Fira.png", 32, 32, 3) == false) {
        return false;
    }
    Brure.X=400;
    Brure.Y=600;
    Fira.X =600;
    Fira.Y =400;
    Chara.Y = 700;
    Chara.X = 600;
    Efis.X=600;
    Efis.Y=500;

    
    
    CEntity::EntityList.push_back(&Efis);
    
    CEntity::EntityList.push_back(&Fira);
    
    CEntity::EntityList.push_back(&Brure);
    
    CEntity::EntityList.push_back(&Chara);
    
    CArea::AreaControl.OnRender(screen, 500,500);

    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnRender(screen);
    }

    SDL_Flip(screen);

    return 0;

    
    return true;
}
