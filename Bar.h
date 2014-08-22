//
//  Bar.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 6/7/14.
//  Copyright (c) 2014 Student. All rights reserved.
//


#ifndef HelloSDL_Bar_h
#define HelloSDL_Bar_h
#include "Surface.h"
#include "Button.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////      BAR CLASS:   Create a square sahped figure that can be used inside a specific Window.                    /////
/////                    This class possess a vector of Buttons.                                                     /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Bar
{
protected:
    SDL_Surface *surf;
    int x,y;
    int *x1,*y1;
    int w,h;
    std::vector<Button*> buttons;
public:
    Bar(int X,int Y,int W,int H,int *X1, int *Y1);
    bool setSurface(std::string file);
    void setPos(int X,int Y);
    void setSize(int W,int H);
    void addButton(Button b);
    void setBound(int *X1, int *Y1);
};

Bar::Bar(int X,int Y,int W,int H,int *X1 = NULL, int *Y1 = NULL)
{
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
}
bool Bar::setSurface(std::string file)
{
    surf = Csurface::OnLoad(&file[0]);
    if (surf == NULL)
        return false;
    return true;
}
void Bar::setPos(int X,int Y)
{
    x = X;
    y = Y;
}
void Bar::setSize(int W,int H)
{
    w = W;
    h = H;
}
void Bar::addButton(Button b)
{
    buttons.push_back(&b);
}
void Bar::setBound(int *X1, int *Y1)
{
    x1 = X1;
    y1 = Y1;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////   TITLEBAR CLASS:   An inherated class of Bar. A tittle bar will be present on every unlocked Window.         /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class titleBar: public Bar
{
public:
    std::string name;
    Button maximize = Button(1,1,1,1);
    Button minimize = Button(1,1,1,1);
    Button quit = Button(1,1,1,1);
    titleBar(int X,int Y,int W,int H,int *X1, int *Y1);
    
};

titleBar::titleBar(int X,int Y,int W,int H,int *X1 = NULL, int *Y1 = NULL) : Bar(X,Y,W,H,X1,Y1)
{
    x = 1;
    maximize = Button(0,0,10,10,&w-13,&h+3);
    minimize = Button(0,0,10,10,&w-26,&h+3);
    quit = Button(0,0,10,10,&w-39,&h+3);
    
}

#endif
