//
//  CEntity.cpp
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/30/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "CEntity.h"



CEntity::CEntity() {
    Surf_Entity = NULL;
    
    X = Y = 0.0f;
    
    Width = Height = 0;
    
    AnimState = 0;
}

CEntity::~CEntity() {
}

bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if((Surf_Entity = Csurface::OnLoad(File)) == NULL) {
        return false;
    }
    

    
    this->Width = Width;
    this->Height = Height;
    
    Anim_Control.MaxFrames = MaxFrames;
    
    return true;
}

void CEntity::OnLoop() {
    Anim_Control.OnAnimate();
}

void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    
    Csurface::OnDraw(Surf_Display, Surf_Entity, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height);
}

void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
    
    Surf_Entity = NULL;
}