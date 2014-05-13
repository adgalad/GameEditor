//
//  CArea.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/1/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_CArea_h
#define HelloSDL_CArea_h

#include "CMap.h"

class CArea {
public:
    static CArea            AreaControl;
    
public:
    std::vector<CMap>       MapList;
    

    int                     AreaSize;
    
    SDL_Surface*        Surf_Tileset;
    
public:
    CArea();
    
    bool    OnLoad(std::string File);
    
    void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
    
    void    OnCleanup();
};




CArea CArea::AreaControl;

CArea::CArea() {
    AreaSize = 0;
}

bool CArea::OnLoad(std::string File) {
    MapList.clear();
    File=path+File;
    std::cout << " file: "+File+" \n";
    std::string MapFileStr;
    FILE* FileHandle = fopen(&File[0], "r");
    
    if(FileHandle == NULL) {

        return false;
    }
    
    char TilesetFile[255];
    
    fscanf(FileHandle, "%s\n", TilesetFile);
    MapFileStr = path+TilesetFile;
     std::cout << " file: "+MapFileStr+" \n";
    if((Surf_Tileset = Csurface::OnLoad(&MapFileStr[0])) == false) {
        fclose(FileHandle);

        return false;
    }

    fscanf(FileHandle, "%d\n", &AreaSize);
    
    for(int X = 0;X < AreaSize;X++) {
        for(int Y = 0;Y < AreaSize;Y++) {
            char MapFile[50];
            
            fscanf(FileHandle, "%s ", MapFile);
            MapFileStr = MapFile;

            CMap tempMap;
            if(tempMap.OnLoad(&MapFileStr[0]) == false) {
                fclose(FileHandle);
                
                return false;
            }
            
            tempMap.Surf_Tileset = Surf_Tileset;
            
            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }
    
    fclose(FileHandle);
    
    return true;
}

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;
    
    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);
    
    for(int i = 0;i < 4;i++) {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
        
        if(ID < 0 || ID >= MapList.size()) continue;
        
        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;
        
        MapList[ID].OnRender(Surf_Display, X, Y);
    }
}

void CArea::OnCleanup() {
    if(Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    }
    
    MapList.clear();
}

#endif
