//
//  Objeto.h
//  
//
//  Created by Carlos Spaggiari on 4/29/14.
//
//
#include <string>
#include <cstdlib>
#include "CAnimation.h"

#ifndef _Objeto_h
#define _Objeto_h

const std::string path= "/Users/carlosspaggiari/Desktop/Game/Resource/";
class ObjAnimado
{
public:
    std::string id;
    int x,y,w,h,dir;
    bool animado,direccion;
    CAnimation anim;
    ObjAnimado(std::string id,int x,int y,int w,int h,int FrameRate, int MaxFrame, bool Oscillate,bool animado,bool direccion);
    void SetPos(int x,int y);
};

ObjAnimado::ObjAnimado(std::string id,int x,int y,int w,int h,int FrameRate,int MaxFrame,bool Oscillate,bool animado=false,bool direccion=false)
{
    this->id = path+id;
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    anim=CAnimation();
    anim.SetFrameRate(FrameRate);
    anim.MaxFrames=MaxFrame;
    anim.Oscillate=Oscillate;
    this->animado=animado;
    this->direccion=direccion;
    dir=3;
}

void ObjAnimado::SetPos(int x,int y)
{
    this->x=x;
    this->y=y;
}

ObjAnimado Chara = ObjAnimado("Chara.png",0,0,32,32,10,3,true,true,true);
ObjAnimado Brure = ObjAnimado("Brure.png",0,0,32,32,10,3,true,true,true);
ObjAnimado Fire  = ObjAnimado("Fira.png" ,0,0,32,32,100,3,true,true,true);
ObjAnimado Efis  = ObjAnimado("Efis.png" ,0,0,32,32,24,3,true,true,true);

#endif
