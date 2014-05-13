//
//  Entity.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/30/14.
//  Copyright (c) 2014 Student. All rights reserved.
//
#include "CAnimation.h"
#include "Surface.h"
#ifndef HelloSDL_Entity_h
#define HelloSDL_Entity_h



const std::string path = "/Users/carlosspaggiari/Desktop/Game/Resource/";

class CEntity {
public:
    static std::vector<CEntity*>    EntityList;
    

    CAnimation      Anim_Control;
    
    SDL_Surface*    Surf_Entity;
    
public:
    float           X;
    float           Y;
    
    int             Width;
    int             Height;
    
    int             AnimState;
    bool            Anim;
    
public:
    CEntity();
    
    virtual ~CEntity();
    
public:
    virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);
    
    virtual void OnLoop();
    
    virtual void OnRender(SDL_Surface* Surf_Display);
    
    virtual void OnCleanup();
};






std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() {
    Surf_Entity = NULL;
    
    X = Y = 0.0f;
    
    Width = Height = 0;
    Anim=false;
    AnimState = 0;
}

CEntity::~CEntity() {
}




bool CEntity::OnLoad(std::string File, int Width, int Height, int MaxFrames) {
    File=path+File;
    std::cout <<File +"\n";
    if((Surf_Entity = Csurface::OnLoad(&File[0])) == NULL) {
        return false;
    }
    
     Csurface::Transparent(Surf_Entity, 255,100, 200);
    
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
    if (Anim)
        Csurface::OnDraw(Surf_Display, Surf_Entity, X, Y, Anim_Control.GetCurrentFrame()*Width,(AnimState -1) * Height, Width, Height);
    else
        Csurface::OnDraw(Surf_Display, Surf_Entity, X, Y, Width,(AnimState - 1) * Height, Width, Height);
}



void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
    
    Surf_Entity = NULL;
}

#endif
