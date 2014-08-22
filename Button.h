//
//  Button.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 6/7/14.
//  Copyright (c) 2014 Student. All rights reserved.
//



#ifndef HelloSDL_Button_h
#define HelloSDL_Button_h
#include "Surface.h"
#include "Bar.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////    BUTTON CLASS:  Each botton have it own position x,y and dimentions w,h.                                    /////
/////                    This class provide a simple way to create a variety of                                      /////
/////                    bottom inside a Bar Class.                                                                  /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Button
{
private:
    int x,y;
    int *x1,*y1;
    int w,h;
    Bar *bar;
    SDL_Surface *surf_press, *surf_release;
public:
    Button(int X,int Y,int W, int H,int *X1, int *Y1);
    bool setSurf(std::string file_press, std::string file_release);
    void setPos(int X,int Y);
    void setSize(int W,int H);
    void setBound(int *X1, int *Y1);
};
Button::Button(int X,int Y,int W, int H,int *X1=NULL, int *Y1=NULL)
{
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
}
void Button::setPos(int X, int Y)
{
    x = X;
    y = Y;
}
void Button::setSize(int W, int H)
{
    w = W;
    h = H;
}

void Button::setBound(int *X1, int *Y1)
{
    x1 = X1;
    y1 = Y1;
}

bool Button::setSurf(std::string file_press, std::string file_release)
{
    surf_press = Csurface::OnLoad(&file_press[0]);
    surf_release = Csurface::OnLoad(&file_release[0]);
    if (surf_press == NULL || surf_release == NULL)
        return false;
    return true;
}


#endif
