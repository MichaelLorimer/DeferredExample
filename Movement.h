#pragma once
#include "Mesh.h"
#include "CVector4.h"

//----------------------
// --- movement data ---
//
const float OrbitSpeed = 1.0f; // speed or rotation
const float Orbit = 50.0f; // rotation radius 
static float Rotate = 0.0f; //needs defining

//----------------------
// --- movement Funk ---
//



// Takes a CMesh name, frame time and EKeyCode (Key_Q) 
void Control(CMesh* Model, float frameTime, EKeyCode turnLeft, EKeyCode turnRight,
	EKeyCode moveForward, EKeyCode moveBackward);


struct SPointLight
{
	CVector3 position;
	float    radius;
	CVector4 colour;
};

void Fire(CMesh* Light, float frameTime);

