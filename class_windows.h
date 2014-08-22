//
//  class_windows.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 6/3/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef class_windows_h
#define class_windows_h


#include "Surface.h"

#define DEFAULT_TITLE_HEIGH  20

class Bar;
class Button;
class Scroll;
class Window;

enum
{
    VERTICAL = false,
    HORIZONTAL = true
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////    BUTTON CLASS:  Each botton have it own position x,y and dimentions w,h.                                    /////
/////                    This class provide a simple way to create a variety of                                      /////
/////                    bottom inside a Bar Class.                                                                  /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Button
{
    friend class Bar;
    friend class Window;
protected:
    Bar *linkedBar;
    SDL_Surface *surf;
    int *x1,*y1;
    int x,y;
    int w,h;
    
public:
    bool press;
    Button(int X,int Y,int W, int H,int *X1, int *Y1,Bar *bar);
    bool setSurf(std::string file_press);
    void setPos(int X,int Y);
    void setSize(int W,int H);
    void setBound(int *X1, int *Y1);
    void OnRender(SDL_Surface *surfDest);
};


Button::Button(int X,int Y,int W, int H,int *X1=NULL, int *Y1=NULL, Bar *bar = NULL)
{
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
    press = false;
    linkedBar = bar;
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

bool Button::setSurf(std::string file)
{
    surf = Csurface::OnLoad(&file[0]);
    if (surf == NULL)
        return false;
    
    Csurface::Transparent(surf, 255, 100, 200);
    return true;
}
void Button::OnRender(SDL_Surface *surfDest)
{
    if (!press)
        if (x1 != NULL)
            Csurface::OnDraw(surfDest, surf, x + *x1, y + *y1,0 ,0 ,w, h);
        else
            Csurface::OnDraw(surfDest, surf, x, y,0 ,0 ,w, h);
    else
        if (x1 != NULL){
            
            Csurface::OnDraw(surfDest, surf, x + *x1, y + *y1,0 ,h ,w, h);
        }
        else
            Csurface::OnDraw(surfDest, surf, x, y,0 ,h ,w, h);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////    SCROLL CLASS:  A small class that draw a scroll bar inside a Window class                                  /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Scroll
{
    friend class Window;
protected:
    SDL_Surface *surf_bar,*surf_button;
    int  *x1,*y1;
    Window *linkedWin;
    bool direction;
    int  w,h;
    int  pos;
    int  x,y;
public:
    Scroll(int X,int Y,int W,int H,int *X1,int *Y1,Window *win);
    bool setSurface(std::string file_bar,std::string file_button);
    void setPos(int X,int Y);
    void setSize(int W,int H);
    void setBound(int *X1, int *Y1);
    void OnRender(SDL_Surface *surfDest);
};

Scroll::Scroll(int X,int Y,int W,int H,int *X1 = NULL, int *Y1 = NULL, Window *win = NULL)
{
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
    pos = 0;
    linkedWin = win;
    
}
bool Scroll::setSurface(std::string file_bar,std::string file_button)
{
    surf_bar = Csurface::OnLoad(&file_bar[0]);
    surf_button = Csurface::OnLoad(&file_button[0]);
    if (surf_bar == NULL || surf_button == NULL)
        return false;
    
    Csurface::Transparent(surf_bar, 255, 100, 200);
    Csurface::Transparent(surf_button, 255, 100, 200);
    return true;
}
void Scroll::setPos(int X,int Y)
{
    x = X;
    y = Y;
}
void Scroll::setSize(int W,int H)
{
    w = W;
    h = H;
}

void Scroll::setBound(int *X1, int *Y1)
{
    x1 = X1;
    y1 = Y1;
}

void Scroll::OnRender(SDL_Surface *surfDest)
{
    if (x1 != NULL)
        Csurface::OnDraw(surfDest, surf_bar, x + *x1, y + *y1,0 ,0 ,w, h);
    else
        Csurface::OnDraw(surfDest, surf_bar, x, y,0 ,0 ,w, h);

    if (direction == HORIZONTAL)
        if (x1 != NULL)
            Csurface::OnDraw(surfDest, surf_button, x + *x1 + pos, y + *y1,0 ,0 ,w, h);
        else
            Csurface::OnDraw(surfDest, surf_button, x + pos, y,0 ,0 ,w, h);
    else
        if (x1 != NULL)
            Csurface::OnDraw(surfDest, surf_button, x + *x1, y + *y1 + pos,0 ,0 ,w, h);
        else
            Csurface::OnDraw(surfDest, surf_button, x, y + pos,0 ,0 ,w, h);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///     BAR CLASS:   Create a square sahped figure that can be used inside a specific Window.
///                    This class possess a vector of Buttons.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Bar
{
    friend class Window;
protected:
    SDL_Surface *surf;
    int *x1,*y1;
    Window *linkedWin;
    int x,y;
    int w,h;
    std::vector<Button> buttons;
    
public:
    Bar(int X,int Y,int W,int H,int *X1, int *Y1,Window *win);
    bool setSurface(std::string file);
    void setPos(int X,int Y);
    void setSize(int W,int H);
    void addButton(Button b);
    void setBound(int *X1, int *Y1);
    void OnRender(SDL_Surface *surfDest);
};

Bar::Bar(int X,int Y,int W,int H,int *X1 = NULL, int *Y1 = NULL,Window *win = NULL)
{
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
    linkedWin = win;
    
}
bool Bar::setSurface(std::string file)
{
    surf = Csurface::OnLoad(&file[0]);
    if (surf == NULL)
        return false;
    
    Csurface::Transparent(surf, 255, 100, 200);
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
    buttons.push_back(b);
}
void Bar::setBound(int *X1, int *Y1)
{
    x1 = X1;
    y1 = Y1;
    for(int i = 0 ; i< buttons.size();i++)
        {
        buttons[i].setBound(X1, Y1);
        }
}

void Bar::OnRender(SDL_Surface *surfDest)
{
    if (x1 != NULL)
        {
        Csurface::OnDraw(surfDest, surf, x + *x1, y + *y1,0 ,0 ,w, h);

        }
    else
        {
        Csurface::OnDraw(surfDest, surf, x, y,0 ,0 ,w, h);
        }
        for (int i=0;i<buttons.size();i++)
        buttons[i].OnRender(surfDest);
    printf("(%d,%d) \n",x+*x1,y+*y1);
}




///       WINDOW CLASS:   An easy way to create a sub-window nested on the main window.
///                       Every window possess a tittle bar with its name and a boolean value that determinate
///                       if the window is locked inside the main window or not, if the window is locked the
///                       tittle bar disappears. It also have 2 vectors, "bars" and "scrolls", bars will save
///                       Bar Classes and scrolls will save Scroll Classes.



class Window
{
public:
    static std::vector<Window> windowList;
    
public:
    bool lock;
    int x,y;
    int *x1,*y1;
    int h,w;
    std::string name;
    Bar title = Bar(0, 0, 1,1);
    Button b = Button(1, 1, 1, 1);
    std::vector<Bar> bars;
    std::vector<Scroll> scrolls;
    SDL_Surface *surf;
    
public:
    Window(std::string newName,int X,int Y,int W,int H,int *X1, int *Y1);
    void lockWin(bool b, int Y, int X);
    void setPos(int X,int Y);
    void setBound(int *X1, int *Y1);
    void setSize(int W,int H);
    void setName(std::string newName);
    bool setSurface(std::string file);
    void OnRender(SDL_Surface *surfDest);
    bool setSurfTitle(std::string bar,std::string quit,std::string mini,std::string maxi);
    static int WindowPressed(int X, int Y);
    static int BarPressed(int X,int Y,int win);
    static Button* ButtonPressed(int X,int Y, int win,int bar);
};


Window::Window(std::string newName,int X,int Y,int W,int H,int *X1 = NULL, int *Y1 = NULL)
{
    
    lock = false;
    surf = NULL;
    x = X;
    y = Y;
    w = W;
    h = H;
    x1 = X1;
    y1 = Y1;
    
    bars.push_back(Bar(0,0,w,DEFAULT_TITLE_HEIGH));
    bars[0].addButton(Button(5, 3, 15, 15,&x,&y,&bars[0]));
    bars[0].addButton(Button(5+15+3, 3, 15, 15,&x,&y,&bars[0]));
    bars[0].addButton(Button(5+15+3+15+3, 3, 15, 15, &x,&y,&bars[0]));

}
std::vector<Window> Window::windowList;

void CreateNewWindow(std::string name, int X, int Y, int W, int H, int *X1 = NULL, int *Y1 = NULL)
{
    Window::windowList.push_back(Window(name, X, Y, W, H,X1,Y1));
    X1 = &Window::windowList[Window::windowList.size()-1].x;
    Y1 = &Window::windowList[Window::windowList.size()-1].y;
    Window::windowList[Window::windowList.size()-1].bars[0].setBound(X1, Y1);
}

void Window::lockWin(bool b, int X, int Y)
{
    lock = b;
    x = X;
    y = Y;
}

void Window::setPos(int X, int Y)
{
    x = X;
    y = Y;
    printf("(%d,%d) \n",*bars[0].x1,*bars[0].y1);
}

void Window::setBound(int *X1, int *Y1)
{
    x1 = X1;
    y1 = Y1;
}
void Window::setSize(int W, int H)
{
    w = W;
    h = H;
}

void Window::setName(std::string newName)
{
    name = newName;
}

bool Window::setSurface(std::string file)
{
    this->surf = Csurface::OnLoad(&file[0]);
    if (surf == NULL)
        return false;
    Csurface::Transparent(surf, 255, 100, 200);
    return true;
}

void Window::OnRender(SDL_Surface *surfDest)
{
    if (x1 != NULL)
        Csurface::OnDraw(surfDest, surf, x + *x1, y + *y1,0 ,0 ,w, h);
    else
        Csurface::OnDraw(surfDest, surf, x, y,0 ,0 ,w, h);
    for (int i = 1; i < bars.size() ;i++)
        bars[i].OnRender(surfDest);
    for (int i = 0; i < scrolls.size(); i++)
        scrolls[i].OnRender(surfDest);
    bars[0].OnRender(surfDest);
}

bool Window::setSurfTitle(std::string bar,std::string quit,std::string mini,std::string maxi)
{
    return (bars[0].setSurface(bar) &&
            bars[0].buttons[0].setSurf("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEditor/Resource/quit.png") &&
            bars[0].buttons[1].setSurf("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEditor/Resource/minimize.png") &&
            bars[0].buttons[2].setSurf("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEditor/Resource/maximize.png"));
}



int Window::WindowPressed ( int X, int Y )
{
    for (int i =0; i< Window::windowList.size() ; i++)
        {
        int x = Window::windowList[i].x;
        int y = Window::windowList[i].y;
        if (X >= x && Y >= y && X <= x+Window::windowList[i].w && Y <= y+Window::windowList[i].h)
            return i;
        }
    return -1;
}

int Window::BarPressed(int X,int Y,int win)
{
    for (int i =0; i< Window::windowList[win].bars.size() ; i++)
        {
        Bar *aux;
        aux = &Window::windowList[win].bars[i];
        if (X >= aux->x + *aux->x1 && Y >= aux->y + *aux->y1  &&
            Y <= aux->y + *aux->y1  + aux->h && X <= aux->x + *aux->x1  + aux->w)
            {
            return i;
            }
        }
    return -1;
}

/// Button*  Window::ButtonPressed(int X, int Y, int win, int bar):
///
Button* Window::ButtonPressed(int X, int Y, int win,int bar)
{
    Bar *aux = &Window::windowList[win].bars[bar];
    for (int j = 0 ;j < aux->buttons.size();j++)
        {
        Button *aux1 = &aux->buttons[j];
        if (aux1->y1 != NULL && aux1->x1 != NULL)
        if (X >= aux1->x + *aux1->x1 && Y >= aux1->y + *aux1->y1 &&
            Y <= aux1->y + aux1->h + *aux1->y1 && X <= aux1->x + aux1->w + *aux1->x1)
            {
            return aux1;
            }
        }

    return NULL;
}





#endif
