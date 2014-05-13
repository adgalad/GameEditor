//
//  CTile.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/1/14.
//  Copyright (c) 2014 Student. All rights reserved.
//
#include "Define.h"
#ifndef HelloSDL_CTile_h
#define HelloSDL_CTile_h

enum {
    TILE_TYPE_NONE = 0,
    
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class CTile {
public:
    int     TileID;
    int     TypeID;
    
public:
    CTile();
};


CTile::CTile() {
    TileID = 0;
    TypeID = TILE_TYPE_NONE;
}

#endif
