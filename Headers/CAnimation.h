//
//  Animacion.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/27/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_Animacion_h
#define HelloSDL_Animacion_h

#include <string>
#include <cstdlib>
#include <SDL/SDL.h>
#include <vector>

class CAnimation
{
private:
    int  CurrentFrame;
    int  FrameInc;
    int  FrameRate;
    long OldTime;
    
public:
    int  MaxFrames;
    bool Oscillate;
    
    
    /* Functions */
    CAnimation();
    
    void OnAnimate();
    
    void SetFrameRate(int Rate);
    
    void SetCurrentFrame(int Frame);
    
    int  GetCurrentFrame();
    
};

CAnimation::CAnimation()
{
          CurrentFrame = 1;
          MaxFrames    = 0;
          FrameInc     = 1;
          FrameRate    = 200;
          OldTime      = 0;
          Oscillate    = 0;
}


void CAnimation::OnAnimate()
{
    if ( OldTime + FrameRate > SDL_GetTicks())
    {
        return;
    }
    
    OldTime = SDL_GetTicks();
    
    CurrentFrame += FrameInc;
    
    if(Oscillate)
    {
        if(FrameInc > 0)
        {
            if(CurrentFrame >= MaxFrames)
            {
                FrameInc = -FrameInc;
            }
        }
        else
        {
            if(CurrentFrame <= 0)
            {
                FrameInc = -FrameInc;
            }
        }
    }
    else
    {
        if(CurrentFrame >= MaxFrames)
        {
            CurrentFrame = 0;
        }
    }
}


void CAnimation::SetFrameRate(int Rate)
{
    FrameRate = Rate;
}

void CAnimation::SetCurrentFrame(int Frame)
{
    if (Frame < 0 || Frame >= MaxFrames) return;
    
    CurrentFrame = Frame;
}

int CAnimation::GetCurrentFrame()
{
    return CurrentFrame;
}






#endif
