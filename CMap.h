//
//  CMap.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/1/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef __HelloSDL__CMap__
#define __HelloSDL__CMap__

#include <SDL/SDL.h>
#include <vector>
#include "CTile.h"
#include "Surface.h"

class CMap {
public:
    SDL_Surface* Surf_Tileset;
    
private:
    std::vector<CTile> TileList;
    
public:
    CMap();
    
public:
    bool OnLoad(std::string File);
    
    void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
};





CMap::CMap() {
    Surf_Tileset = NULL;
}

bool CMap::OnLoad(std::string File) {
    TileList.clear();
    File=path+File;
    FILE* FileHandle = fopen(&File[0], "r");
    
    if(FileHandle == NULL) {
        return false;
    }
    
    for(int Y = 0;Y < MAP_HEIGHT;Y++) {
        for(int X = 0;X < MAP_WIDTH;X++) {
            CTile tempTile;
            
            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
            
            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }
    
    fclose(FileHandle);
    
    return true;
}

void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
    if(Surf_Tileset == NULL) return;
    
    int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
    //int TilesetHeight = Surf_Tileset->h / TILE_SIZE;
    
    int ID = 0;
    
    for(int Y = 0;Y < MAP_HEIGHT;Y++) {
        for(int X = 0;X < MAP_WIDTH;X++) {
            if(TileList[ID].TypeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }
            
            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);
            
            int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
            
            Csurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            
            ID++;
        }
    }
}

#endif
