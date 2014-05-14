//
//  Window.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/3/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "Surface.h"
#include <fstream>
#include <vector>
#ifndef HelloSDL_Window_h
#define HelloSDL_Window_h


std::string path = "/Users/carlosspaggiari/Desktop/Game/Resource/";

std::string path2 = "/Users/carlosspaggiari/Desktop/GameEditor/Resource/";
#define NullTile = 0

const int mapx=200,mapy=200;


class Window
{
public:
    SDL_Surface *MainWindow,*MousePointer,*Barra,*botones,*fondo,*scroll;
    int w,h;
    bool FullScreen;
    bool running;
    int currentTile,maxTile;
    int tool;
    std::vector<int> black[mapx+2][mapy+2];
    int x,y,fondoX,fondoY,fondoPos;
    int pallet;
    int pallettam;
    int win;
    
    int objectsBegin;

    Window();
    bool OnInit();
    bool OnExecute();
    void OnCleanup();
    bool OnEvent(SDL_Event *Event);
    bool OnLoop(SDL_Event *Event);
    bool OnRender(SDL_Event *Event);
    bool Fwrite();
    void Fread();
};




Window::Window()
{
    FullScreen = false;
    MousePointer = NULL;
    MainWindow = NULL;
    fondo = NULL;
    scroll = NULL;
    botones = NULL;
    Barra = NULL;
    running = true;
    currentTile = 1;
    x=-8;
    y=-1;
    fondoX = 16;
    fondoY = 96;
    fondoPos = 0;
    pallet=1;
    pallettam = 1;
    tool =1;
    win = 0;
    objectsBegin = 9;
}


void Window::Fread()
{
    std::string file = path+"save.map";
    FILE *save = fopen(&file[0], "r");
    
    if (save!=NULL)
    {
        int aux;

        for(int i=0;i<mapy;i++){
            for (int j=0; j <mapx; j++) {
                
                bool hasNext = true;
                std::vector<int> tempVec;
                int tileId = 0;
                char ch = '\0';
                
                while (hasNext)
                    {
                    fscanf(save,"%d",&tileId);
                    fscanf(save,"%c",&ch);
                    tempVec.push_back(tileId);
                    if ( ch == ':')
                        hasNext = false;
                    }
                fscanf(save,"%d ",&aux);
                black[i][j]=tempVec;
            
            }
            
            fscanf(save, "\n");
        }
    }
    else
        {
        std::vector<int> t;
        t.push_back(0);
        for(int i=0;i<mapy;i++)
            for (int j=0; j <mapx; j++)
                black[i][j] = t;

        }
}

bool Window::Fwrite()
{
    
    std::string File;
    File = path + "save.map";
    std::ofstream save;
    save.open (File);
    
    for(int i=0 ; i< mapx ; i++)
        {
        for (int j=0; j < mapy ; j++)
            {
            std::string str = "";
            bool block = false;
            for (int k = 0; k< black[i][j].size() ; k++)
                {
                int Id = black[i][j][k];
                if (Id == 0){
                    str = "0";
                    block = true;
                    break;
                }
                str = str+ std::to_string(Id);
                if (k+1 != black[i][j].size())
                    str = str +"-";
                if (Id >= objectsBegin) {
                    block = true;
                }
                }
            if (block)
                save << str+":2 ";
            else
                save << str+":1 ";
            }
        save << "\n";
        }
    return true;
}

bool Window::OnInit()
{
    /* Init SDL */
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    
    
    /* Obtain screen's dimensions */

    const SDL_VideoInfo *VideoInfo;
    VideoInfo = SDL_GetVideoInfo();
    w=VideoInfo->current_w;
    h=VideoInfo->current_h;
    

    
    /* Set Video Mode */
    if ((MainWindow=SDL_SetVideoMode(w,h-128, 32, SDL_HWSURFACE|SDL_DOUBLEBUF))==NULL)
        return false;
    std::string img = path2+"editor.png";
    Barra = Csurface::OnLoad(&img[0]);
    img = path2+"botones.png";
    botones = Csurface::OnLoad(&img[0]);
    img = path+"tiles1.png";
    MousePointer = Csurface::OnLoad(&img[0]);
    img = path2+"fondo.png";
    fondo = Csurface::OnLoad(&img[0]);
    
    Csurface::Transparent(MousePointer, 255, 100, 200);
    Csurface::Transparent(MousePointer, 255, 100, 200);
    Csurface::Transparent(Barra, 255, 100, 200);
    //SDL_SetColorKey(fondo, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fondo->format, 255, 100, 200));
    
    maxTile = (MousePointer->h/32 +1) * (MousePointer->w-32)/32 ;
    printf(" %d" ,maxTile);
    /* Enable Key Repeat */
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    /* Set Unicode Translate */
    SDL_EnableUNICODE(1);
    
    Fread();
    return true;
    
}

void Window::OnCleanup()
{
    SDL_FreeSurface(MainWindow);

}

bool Window::OnEvent(SDL_Event *Event)
{
    if ( Event->motion.y > 68 && Event->motion.y < h-160-16 && Event->motion.x > 288 && Event->motion.x < w-16 )
        win = 0;
    switch (Event->type) {

        case SDL_KEYDOWN:
            switch (Event->key.keysym.sym) {
                    
                case SDLK_RIGHT:
                    if (x < mapx-40 && !win) {
                        x++;
                    }
                    break;
                case SDLK_LEFT:
                    if (x > -8 && !win) {
                        x--;
                    }
                    break;
                case SDLK_DOWN :
                    if (y < mapy-41 && !win) {
                        y++;
                    }
                    else if(fondoPos/35 > -maxTile/6+18 && win)
                        {
                        fondoPos-=4;

                        }
                    break;
                case SDLK_UP:
                    if (y > -1 && !win) {
                        y--;

                    }
                    else if(fondoPos !=0 && win)
                        {
                        fondoPos+=4;
                        }
                    break;
                default:
                    if (Event->key.keysym.unicode == 'm')
                    {
                        SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL / 3);
                    
                        if (currentTile == maxTile)
                            currentTile = 0;
                        else
                            currentTile++;
                    
                        SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
                    
                    }
                    else if(Event->key.keysym.unicode == 'n')
                    {

                        SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL / 3);
                            
                        if (currentTile == 0)
                            currentTile = maxTile;
                        else
                            currentTile--;

                        SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
                            
                    }
                    else if (Event->key.keysym.unicode == 's')
                    {
                        Fwrite();
                    }
                    else if(Event->key.keysym.unicode == '1'){
                            pallet=1;
                        pallettam=1;
                    }
                    else if(Event->key.keysym.unicode == '2'){
                        pallet=2;
                        pallettam=2;
                    }
                    else if(Event->key.keysym.unicode == '3'){
                        pallet=3;
                        pallettam=4;
                    }
                    else if(Event->key.keysym.unicode == '4'){
                        pallet=4;
                        pallettam=8;
                    }
                    break;
            }
            break;
        case SDL_KEYUP:
            break;
        case SDL_MOUSEBUTTONDOWN:
            


            if (Event->button.button == SDL_BUTTON_RIGHT) {
                
                    if (black[y+Event->motion.y/32][x+Event->motion.x/32].size() > 1)
                        black[y+Event->motion.y/32][x+Event->motion.x/32].pop_back();
                    else if (black[y+Event->motion.y/32][x+Event->motion.x/32].size() == 1)
                        black[y+Event->motion.y/32][x+Event->motion.x/32][0] = 0;
 
            }
            else if (Event->button.button == SDL_BUTTON_LEFT)
                {
                if (Event->motion.y > 64 && Event->motion.x > 288 )
                    {
                    if (tool == 1)
                        {
                        if (currentTile < objectsBegin)
                            {
                            for(int i=0;i<pallettam;i++)
                                for(int j=0;j<pallettam;j++)
                                    if ( Event->motion.y + j*32 < h - 160 && Event->motion.y + j*32 > 64 &&
                                         Event->motion.x + j*32 < w && Event->motion.x + j*32 > 288)
                                        {
                                        black[y+Event->motion.y/32+j][x+Event->motion.x/32+i][0]=currentTile;
                                        }
                            }
                        else
                            {
                            for(int i=0;i<pallettam;i++)
                                for(int j=0;j<pallettam;j++)
                                    black[y+Event->motion.y/32+j][x+Event->motion.x/32+i].push_back(currentTile);
                            
                            }
                    
                        }
                    else
                        {

                        currentTile= black[y+Event->motion.y/32][x+Event->motion.x/32].back();
                        pallet = 1;
                        pallettam = 1;
                        if (black[y+Event->motion.y/32][x+Event->motion.x/32].size() > 1)
                            black[y+Event->motion.y/32][x+Event->motion.x/32].pop_back();
                        else if (black[y+Event->motion.y/32][x+Event->motion.x/32].size() == 1)
                                 black[y+Event->motion.y/32][x+Event->motion.x/32][0] = 0;
                        tool =1;
   
                        
                        }
                    }
                else if ( Event->motion.y > 3 && Event->motion.y < 64)
                    {
                    if (Event->motion.x >60  && Event->motion.x < 120)
                        {
                        pallet = 1;
                        pallettam = 1;
                        }
                    else if (Event->motion.x > 120 && Event->motion.x < 175)
                        {
                        pallet = 2;
                        pallettam = 2;
                        }
                    else if (Event->motion.x >180  && Event->motion.x < 235)
                        {
                        pallet = 3;
                        pallettam = 4;
                        }
                    else if (Event->motion.x >240  && Event->motion.x < 295)
                        {
                        pallet = 4;
                        pallettam = 8;
                        }
                    else if (Event->motion.x >360  && Event->motion.x < 415)
                        {
                        tool = 1;
                        }
                    else if (Event->motion.x >420  && Event->motion.x < 475)
                        {
                        tool = 2;
                        }
                    }
                else if ( Event->motion.y > 99  && Event->motion.x > 32)
                {
                    win = 1;
                    currentTile = 6*((Event->motion.y - 99)/35) + (Event->motion.x - 32)/35;
                
                }
            }
            break;
        case SDL_QUIT:
            running =false;
            break;
        default:
            break;
    }
    return true;
}

bool Window::OnLoop(SDL_Event *Event)
{
    for (int i = 9; i<40 ;i++)
        for(int j = 2 ; j<32; j++)
            for (int k= 0; k< black[y+j][x+i].size();k++)
                {
                int      Id = black[y+j][x+i][k];
                Csurface::OnDraw(MainWindow, MousePointer, i*32, j*32,32*(Id%10),32*(Id/10),32,32);
                
                }
    Csurface::OnDraw(MainWindow,fondo,fondoX,fondoY);
    int i,j,Id;
    i = j = Id =0;
    j=0;
    while (Id < maxTile)
        {
        Id = j*6+i;
        Csurface::OnDraw(MainWindow, MousePointer, i*35+32, fondoPos+j*35+99,32*(Id%10),32*(Id/10),32,32);
        i++;
        if ( i == 6)
            {
            i=0;
            j++;
            }
        }
    Csurface::OnDraw(MainWindow, Barra, 0, 0);
    for(int i=0;i<4;i++)
            if (i+1 != pallet)
                Csurface::OnDraw(MainWindow, botones, 60+i*60, 2,i*55,0,55,55);
            else
                Csurface::OnDraw(MainWindow, botones, 60+i*60, 2,i*55,55,55,55);
    
    for(int i=0;i<4;i++)
        if (i+1 != tool)
            Csurface::OnDraw(MainWindow, botones, 360+i*60, 2,220+i*55,0,55,55);
        else
            Csurface::OnDraw(MainWindow, botones, 360+i*60, 2,220+i*55,55,55,55);
    

    
    if ( Event->motion.y > 68 && Event->motion.y < h-160-16 && Event->motion.x > 288 && Event->motion.x < w-16 && tool == 1)
    {

        for(int i=0;i<pallettam;i++)
            for(int j=0;j<pallettam;j++){

                Csurface::OnDraw( MainWindow , MousePointer , Event->motion.x+i*32-12 ,
                                 Event->motion.y+j*32-12, 32*(currentTile%10) , 32*(currentTile/10) , 32 , 32 );
                
            }
    }

    return true;
}

bool Window::OnRender(SDL_Event *Event)
{
    SDL_Flip(MainWindow);
    return true;
}

bool Window::OnExecute()
{
    SDL_Event Event;


    while (running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        OnLoop(&Event);
        OnRender(&Event);
    }
    return true;
}

#endif
