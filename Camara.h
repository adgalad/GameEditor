//
//  Camara.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/1/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_Camara_h
#define HelloSDL_Camara_h
#include "Define.h"
enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera {
public:
    static CCamera CameraControl;
    
private:
    int X;
    int Y;
    
    int* TargetX;
    int* TargetY;
    
public:
    int TargetMode;
    
public:
    CCamera();
    
public:
    void OnMove(int MoveX, int MoveY);
    
public:
    int GetX();
    int GetY();
    
public:
    void SetPos(int X, int Y);
    
    void SetTarget(int* X, int* Y);
};


CCamera CCamera::CameraControl;

CCamera::CCamera() {
    X = Y = 0;
    
    TargetX = TargetY = NULL;
    
    TargetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(int MoveX, int MoveY) {
    X += MoveX;
    Y += MoveY;
}

int CCamera::GetX() {
    if(TargetX != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetX - (VideoInfo->current_w / 2);
        }
        
        return *TargetX;
    }
    
    return X;
}

int CCamera::GetY() {
    if(TargetY != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetY - (VideoInfo->current_h / 2);
        }
        
        return *TargetY;
    }
    
    return Y;
}

void CCamera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(int* X, int* Y) {
    TargetX = X;
    TargetY = Y;
}


#endif
