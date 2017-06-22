
#include "Movement.h"

using namespace std; 



// Takes a CMesh name, frame time and EKeyCode (Key_Q) 
void Control(CMesh* Model, float frameTime, EKeyCode turnLeft, EKeyCode turnRight,
	EKeyCode moveForward, EKeyCode moveBackward)
{
	int numNode = 0; 
	if (KeyHeld(turnRight))
	{
		numNode = Model->GetNumNodes();
		for (int i = 0; i < numNode; i++)
		{
			//Model->GetNode(i).positionMatrix += RotSpeed * frameTime;
			Model->GetNode(i).positionMatrix.RotateLocalY(RotSpeed * frameTime);
		}

	}
	if (KeyHeld(turnLeft))
	{
		numNode = Model->GetNumNodes();
		for (int i = 0; i < numNode; i++)
		{
			//Model->GetNode(i).positionMatrix += RotSpeed * frameTime;
			Model->GetNode(i).positionMatrix.RotateLocalY(-RotSpeed * frameTime);
		}
	}
	// Local Z movement - move in the direction of the Z axis, get axis from view matrix
	if (KeyHeld(moveForward))
	{
		numNode = Model->GetNumNodes();
		for (int i = 0; i < numNode; i++)
		{
			Model->GetNode(i).positionMatrix.MoveLocalX(-MoveSpeed * frameTime);
		}
	}
	if (KeyHeld(moveBackward))
	{
		numNode = Model->GetNumNodes();
		for (int i = 0; i < numNode; i++)
		{
			Model->GetNode(i).positionMatrix.MoveLocalZ(MoveSpeed * frameTime);
		}
	}
}



void Shoots(CMesh* Light, SPointLight Lights, CVector3 Shooter, CVector3 Target, float frameTime)
{
	CVector3 Current = Light->Matrix().Position();
	//CVector3 Rand = CVector3(0.0f, 0.0f, Random(80.0f, -80.0f)); // fix later
	CVector3 NextPoint;

	if (Distance(Current, Target) < 2.0f)
	{
		Light->SetPos(Shooter);
	}
	if (Distance(Current, Shooter) >= 0.0f)
	{
		NextPoint = Target;
	}

	// --- doesnt select a random target ----
	//Target = Target + CVector3(0.0f, 0.0f, Random(-20, 20));

	int numNode = Light->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		Light->GetNode(i).positionMatrix.MoveLocalZ(50.0f * frameTime);
	}
	Light->SetFacing(NextPoint);
}

//void Fire(CMesh*Light, float frameTime)
//{
//	int numNode = Light->GetNumNodes();
//	for (int j = 0; j < numNode; i++)
//	{
//		Light->GetNode(j).positionMatrix.MoveLocalZ(50.0f*frameTime);
//	}
//}

void Fire(CMesh* Light, float frameTime)
{
	int numNode = Light->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		Light->GetNode(i).positionMatrix.MoveLocalZ(100.0f * frameTime);
	}
}
