#pragma once
#include "Mesh.h"

// globals
const int maxSquad = 3;
// movement

// movement functions
// 1. Attacking model
// 2. Attack Target
void attackSide(CMesh* model,CMesh*Target, float frameTime);
void attackTop(CMesh* model, CMesh* Target, float frameTime);

// Orbit a given target
// 1. current mesh to be moved
// 2. Target Position (CVector3)
// 3. given radius to orbit around
// 4. FrameTime
// 5. true = clockwise/ false = Counter Clockwise
void OrbitTargetVert(CMesh* model, CVector3 target, float radius, float frameTime, bool clock);
void OrbitTargetHor(CMesh* model, CVector3 target, float radius,  float frameTime, bool clock);

// 1. model doing the chasing
// 2. model for target to chase
void ChaseTarget(CMesh* model, CMesh*target, float frameTime);


void Shoot(CMesh* Light, CVector3 Shooter, CVector3 Target, float frameTime);
CVector3 GetPoint();