#include "Behave.h"
using namespace std;

// movement variables 
CVector3 current;

// point counter
int pointCounter = 0;
// movement paths
CVector3 point1;
CVector3 point2;
CVector3 point3;
CVector3 point4;
CVector3 point5;

CVector3 points[5]{ point1,point2,point3,point4,point5 };
CVector3 nextPoint;

// movement paths
CVector3 side[5]
{
	CVector3(120.0f, 60.0f, 0.0f),
	CVector3(60.0f, 40.0f, 0.0f),
	CVector3(20.0f, 0.0f, 0.0f),
	CVector3(100.0f, 0.0f, 0.0f),
	CVector3(160.0f, 40.0f, 0.0f)
};

// attack from the top
CVector3 top[5]{
	CVector3(0.0f, 80.0f, 120.0f),
	CVector3(0.0f , 40.0f, 80.0f),
	CVector3(0.0f , 20.0f, 0.0f),
	CVector3(0.0f, 40.0f , -80.0f),
	CVector3(0.0f, 100.0f, 0.0f)
};
//squad movement
void attackSide(CMesh* model,CMesh*target, float frameTime) // needs generalising
{
	current = model->Matrix().Position();

	points[0] = target->Matrix().Position() + CVector3(-120.0f, 60.0f, 0.0f);
	points[1] = target->Matrix().Position() + CVector3(-60.0f, 40.0f, 0.0f);
	points[2] = target->Matrix().Position() + CVector3(-20.0f, 0.0f, 0.0f);
	points[3] = target->Matrix().Position() + CVector3(-100.0f, 0.0f, 0.0f);
	points[4] = target->Matrix().Position() + CVector3(-160.0f, 40.f, 0.0f);

	// movement paths
	nextPoint = points[pointCounter];


	if (Distance(current, nextPoint) < 2.0f)
	{
		nextPoint = points[pointCounter];
		pointCounter++;
	}
	if (pointCounter == 5)
	{
		pointCounter = 0;
	}

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		model->GetNode(i).positionMatrix.MoveLocalZ(MoveSpeed*frameTime);
	}
	model->SetFacing(nextPoint);
}

void attackTop(CMesh* model, CMesh*target, float frameTime) // needs generalising
{
	current = model->Matrix().Position();

	points[0] = target->Matrix().Position() + CVector3(0.0f, 80.0f, 120.0f);
	points[1] = target->Matrix().Position() + CVector3(0.0f, 40.0f, 80.0f);
	points[2] = target->Matrix().Position() + CVector3(0.0f, 20.0f, 0.0f);
	points[3] = target->Matrix().Position() + CVector3(0.0f, 40.0f, -80.0f);
	points[4] = target->Matrix().Position() + CVector3(0.0f, 100.f, 0.0f);

	// movement paths
	nextPoint = points[pointCounter];


	if (Distance(current, nextPoint) < 2.0f)
	{
		nextPoint = points[pointCounter];
		pointCounter++;
	}
	if (pointCounter == 5)
	{
		pointCounter = 0;
	}

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		model->GetNode(i).positionMatrix.MoveLocalZ(MoveSpeed*frameTime);
	}
	model->SetFacing(nextPoint);
}
// all these need changing later after removal of movement.h/ cpp
const float OrbitSpeeds = 1.0f; // speed or rotation
const float Orbits = 50.0f; // rotation radius 
static float Rotates = 0.0f; //needs defining
static float Rot = 0.0f;


void OrbitTargetVert(CMesh* model, CVector3 target, float radius, float frameTime, bool clock) // speeds need to be corrected 
{
	float speed = 50;
	Rotates -= OrbitSpeeds * frameTime;
	CVector3 pos;
	CVector3 news;
	CVector3 current = model->Matrix().Position();
	pos = target;

	if (clock)
	{
		news = pos + CVector3(0, cos(Rotates)* radius, sin(Rotates)* radius); // needs to be generalised to allow for more directions
	}
	else
	{
		news = pos + CVector3(0, sin(Rotates)* radius, cos(Rotates)* radius); // needs to be generalised to allow for more directions
	}

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		model->GetNode(i).positionMatrix.MoveLocalZ(speed*frameTime);
	}
	model->SetFacing(news);
}

void OrbitTargetHor(CMesh* model, CVector3 target, float radius, float frameTime, bool clock) // speeds need to be corrected 
{
	float speed = 50;
	Rotates -= OrbitSpeeds * frameTime;
	CVector3 pos;
	CVector3 news;
	CVector3 current = model->Matrix().Position();
	pos = target;
	if (clock)
	{
		news = pos + CVector3(cos(Rotates)* radius, 0, sin(Rotates)* radius);
	}
	else
	{
		news = pos + CVector3(sin(Rotates)* radius, 0, cos(Rotates)* radius);
	}

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		model->GetNode(i).positionMatrix.MoveLocalZ(speed*frameTime);
	}
	model->SetFacing(news);
}

void OrbitTargets(CMesh* model, CVector3 pos, float radius, float frameTime) // speeds need to be corrected 
{
	float speed = 50;
	Rotates -= OrbitSpeeds * frameTime;
	CVector3 news;
	CVector3 current = model->Matrix().Position();
	
	if (current.x < 400.0f && current.x > 0.0f)
	{
		if (current.y < 400.0f && current.y > -400.0f)
		{
			if (current.z < 400.0f && current.z > -400.0f)
			{
				pos = CVector3(Random(0.0f, 100.0f), Random(-400.0f, 400.0f), Random(-400.0f, 400.0f));
			}
		}
	}
	else
	{
		news = CVector3(0.5f, 0.0f, 0.0f);
	}

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		model->GetNode(i).positionMatrix.MoveLocalZ(speed*frameTime);
	}
	model->SetFacing(news);
	
}

void ChaseTarget(CMesh* model, CMesh*target, float frameTime)
{
	CVector3 targetP = target->Matrix().Position();
	CVector3 current = model->Matrix().Position();

	
	if (Distance(current, targetP) > 20.0f)
	{
		int numNode = model->GetNumNodes();
		for (int i = 0; i < numNode; i++)
		{
			model->GetNode(i).positionMatrix.MoveLocalZ(50 * frameTime);
		}
		model->SetFacing(targetP);
	}
}

// shoot needs to be implimented

// manover maybe
void LookingAt(CMesh* model, CVector3 pos, float frameTime)
{
	CVector3 current = model->Matrix().Position();
	CVector3 target = pos;

	CVector3 currentx = model->Matrix().XAxis();
	CVector3 currentz = model->Matrix().ZAxis();

	float mex = 0;

	float ang = 0;

	mex = Dot(currentx, target);
	ang = Dot(currentz, target);

	int numNode = model->GetNumNodes();
	for (int i = 0; i < numNode; i++)
	{
		if (mex > 0.0f)
		{
			model->GetNode(i).positionMatrix.RotateLocalY(10 * frameTime);
		}
		if (mex < 0.0f)
		{
			model->GetNode(i).positionMatrix.RotateLocalY(-10 * frameTime);
		}
		if (mex == ang)
		{
			model->GetNode(i).positionMatrix.RotateLocalY(0 * frameTime);
		}

		/*if (mey > 0.0f)
		{
			model->GetNode(i).positionMatrix.RotateLocalX(10 * frameTime);
		}
		if (mey < 0.0f)
		{
			model->GetNode(i).positionMatrix.RotateLocalX(-10 * frameTime);
		}
		if (mey == ing)
		{
			model->GetNode(i).positionMatrix.RotateLocalX(0 * frameTime);
		}*/
		
	}
	
}

//void ShootLazor(CMesh* model, )
//{
//	
//		PointLights[NumPointLights].position = CVector3(Random(-600.0f, 600.0f), Random(0.0f, 100.0f), Random(-600.0f, 600.0f)); // was 5.0, 40
//		PointLights[NumPointLights].radius = Random(20.0f, 40.0f);
//		PointLights[NumPointLights].colour = CVector4(Random(0.4f, 1.0f), Random(0.4f, 1.0f), Random(0.4f, 1.0f), 0);
//		NumPointLights++;
//		
//		emit += 1.0f / LightSpawnFreq;
//	}
//
//	// Rotate all lights (except the first) around the origin in an interesting way
//	for (int i = 1; i < NumPointLights; i++)
//	{
//		float dist = PointLights[i].position.Length();
//		float rotateSpeed = (fmodf(dist, 1.0f) + -0.5f) * 200.0f / (dist + 0.1f);
//		PointLights[i].position = MatrixRotationY(rotateSpeed*frameTime).TransformVector(PointLights[i].position);
//	}
//}

//CVector3 up = ScifiShipA->Matrix().YAxis();
//CVector3 current = ScifiShipA->Matrix().Position();
//CVector3 target = HawkStarfighterA1->Matrix().Position();
//CVector3 dir = Normalise(current - target);
//
//CVector3 currentx = ScifiShipA->Matrix().XAxis();
//CVector3 currenty = ScifiShipA->Matrix().YAxis();
//CVector3 currentz = ScifiShipA->Matrix().ZAxis();
//
//float mex = 0;
//float mey = 0;
//float me = 0;
//
//float ang = 0;
//float ing = 0;
//me = Dot(currentz, currenty);
//
//mex = Dot(currentx, target);
//mey = Dot(currentz, target);
//
//ang = Dot(currentz, target);
//ing = Dot(currentz, target);
//
//int numNode = ScifiShipA->GetNumNodes();
//for (int i = 0; i < numNode; i++)
//{
//	if (mex > 0.0f)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalY(10 * frameTime);
//	}
//	if (mex < 0.0f)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalY(-10 * frameTime);
//	}
//	if (mex == ang)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalZ(0 * frameTime);
//	}
//
//	if (mey > 0.0f)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalZ(10 * frameTime);
//	}
//	if (mey < 0.0f)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalX(-10 * frameTime);
//	}
//	if (mey == ing)
//	{
//		ScifiShipA->GetNode(i).positionMatrix.RotateLocalZ(0 * frameTime);
//	}
//}


// Shoot Implimentation
// 1. Needs a start point, end point ^^ 
// 2. if Distance between light/ lazor and target  ^^ 
// 3. max number of lazors
// 4. lazor delete after a certain range/ time
// 5. be somwhat versitile

void Shoot(CMesh* Light, CVector3 Shooter, CVector3 Target, float frameTime)
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
		Light->GetNode(i).positionMatrix.MoveLocalZ(100.0f * frameTime);
	}
	Light->SetFacing(NextPoint);

}
