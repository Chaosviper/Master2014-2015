#pragma once
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"
#include "Quaternion.h"
//For debug only
#include <iostream>

namespace CollisionAlgorithm
{
	template<class T, class U> class CollisionDetectionAlgorithm;

	template<>
	class CollisionDetectionAlgorithm<BoxCollider, BoxCollider>
	{
	public:
		
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<BoxCollider*>(&first), static_cast<BoxCollider*>(&second));
		}
	private:
		
		static Collision* CollisionComputation(BoxCollider* first, BoxCollider* second)
		{
			//Compute Collision on first axis system so first can be seen as an AABB
			Vector3 CentersDistance(second->GetWorldPosition());
			Vector3 SecondBoxCenterInFirstBoxSystem(CentersDistance);
			CentersDistance -= first->GetWorldPosition();
			CentersDistance *= -1.0f;
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), SecondBoxCenterInFirstBoxSystem, SecondBoxCenterInFirstBoxSystem);
			Vector3 radiiSum(first->GetHalfSize());
			radiiSum += second->GetHalfSize();
			
			//SphereTest for early fast reject
			bool SphereConsideration = (CentersDistance.getX()*CentersDistance.getX()) < (radiiSum.getX()*radiiSum.getX()) &&
				(CentersDistance.getY()*CentersDistance.getY()) < (radiiSum.getY()*radiiSum.getY()) &&
				(CentersDistance.getZ()*CentersDistance.getZ()) < (radiiSum.getZ()*radiiSum.getZ()) && (CentersDistance.SqrMagnitude()) < (radiiSum.SqrMagnitude());
			
			if (SphereConsideration)
			{
				return nullptr;
			}
			
			//Compute Min and Max for first box
			Vector3 Min(first->GetWorldPosition() - first->GetHalfSize());
			Vector3 Max(first->GetWorldPosition() + first->GetHalfSize());
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), Min, Min);
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), Max, Max);
			Vector3 SecondHalfSizeInFistSystem(second->GetHalfSize());
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(second->GetRotation().ToMatrix(), SecondHalfSizeInFistSystem, SecondHalfSizeInFistSystem);
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), SecondHalfSizeInFistSystem, SecondHalfSizeInFistSystem);
			//Second vs first
			//Optimization TO DO
			//0 1 3 7 6 4 5 2
			Vector3 Vertex[8];
			Vertex[0]=(SecondBoxCenterInFirstBoxSystem);
			Vertex[0][0] += SecondHalfSizeInFistSystem[0];
			Vertex[0][1] += SecondHalfSizeInFistSystem[1];
			Vertex[0][2] += SecondHalfSizeInFistSystem[2];

			Vertex[1] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[1][0] += SecondHalfSizeInFistSystem[0];
			Vertex[1][1] += SecondHalfSizeInFistSystem[1];
			Vertex[1][2] -= SecondHalfSizeInFistSystem[2];

			Vertex[2] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[2][0] += SecondHalfSizeInFistSystem[0];
			Vertex[2][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[2][2] += SecondHalfSizeInFistSystem[2];
			
			Vertex[3] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[3][0] += SecondHalfSizeInFistSystem[0];
			Vertex[3][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[3][2] -= SecondHalfSizeInFistSystem[2];

			Vertex[4] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[4][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[4][1] += SecondHalfSizeInFistSystem[1];
			Vertex[4][2] += SecondHalfSizeInFistSystem[2];

			Vertex[5] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[5][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[5][1] += SecondHalfSizeInFistSystem[1];
			Vertex[5][2] -= SecondHalfSizeInFistSystem[2];
		
			Vertex[6] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[6][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[6][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[6][2] += SecondHalfSizeInFistSystem[2];

			Vertex[7] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[7][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[7][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[7][2] -= SecondHalfSizeInFistSystem[2];
			
			//Compute points inside
			int indexes[8];
			float compenetration[8];
			unsigned int pointsInside = 0;
			bool isInside=false;
			for (unsigned int i = 0; i < 8; ++i)
			{
				isInside=Vertex[i][0] > Min[0] && Vertex[i][1] > Min[1] &&Vertex[i][2] > Min[2]&&
					Vertex[i][0] < Max[0] && Vertex[i][1] < Max[1] && Vertex[i][2] < Max[2];
				if (isInside)
				{
					indexes[pointsInside] = i;
					compenetration[pointsInside] = (Vertex[i] - first->GetWorldPosition()).SqrMagnitude();
					++pointsInside;
				}
			}

			//Compute Collision Data iff there is a collision
			if (pointsInside)
			{
				float CompenetrationSum = compenetration[0];
				Vertex[indexes[0]][0] *= compenetration[0];
				Vertex[indexes[0]][1] *= compenetration[0];
				Vertex[indexes[0]][2] *= compenetration[0];
				//centroid of points which is the point of collision impact
				for (unsigned int i = 1; i < pointsInside; ++i)
				{
					Vertex[indexes[0]][0] += Vertex[indexes[i]][0];
					Vertex[indexes[0]][1] += Vertex[indexes[i]][1];
					Vertex[indexes[0]][2] += Vertex[indexes[i]][2];
					CompenetrationSum += compenetration[i];
					compenetration[0] = std::fmaxf(compenetration[0], compenetration[i]);
				}
				Vertex[indexes[0]][0] /= CompenetrationSum;
				Vertex[indexes[0]][1] /= CompenetrationSum;
				Vertex[indexes[0]][2] /= CompenetrationSum;

				//Compute normal by clamping on max value
				CentersDistance.Normalize();
				float x, y, z;
				x = CentersDistance.getX();
				y = CentersDistance.getY();
				z = CentersDistance.getZ();
				if (x > y)
				{
					if (x > z)
					{
						CentersDistance.Set(x, 0, 0);
					}
					else
					{
						CentersDistance.Set(0, 0, z);
					}
				}
				else
				{
					if (y > z)
					{
						CentersDistance.Set(0, y, 0);
					}
					else
					{
						CentersDistance.Set(0, 0, z);
					}
				}
				CentersDistance.Normalize();
				//Compute Compenetration
				return new Collision(compenetration[0], Vertex[indexes[0]], CentersDistance);
			}

			//first vs Second
			Vector3 Vertex[8];
			Vertex[0] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[0][0] += SecondHalfSizeInFistSystem[0];
			Vertex[0][1] += SecondHalfSizeInFistSystem[1];
			Vertex[0][2] += SecondHalfSizeInFistSystem[2];

			Vertex[1] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[1][0] += SecondHalfSizeInFistSystem[0];
			Vertex[1][1] += SecondHalfSizeInFistSystem[1];
			Vertex[1][2] -= SecondHalfSizeInFistSystem[2];

			Vertex[2] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[2][0] += SecondHalfSizeInFistSystem[0];
			Vertex[2][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[2][2] += SecondHalfSizeInFistSystem[2];

			Vertex[3] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[3][0] += SecondHalfSizeInFistSystem[0];
			Vertex[3][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[3][2] -= SecondHalfSizeInFistSystem[2];

			Vertex[4] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[4][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[4][1] += SecondHalfSizeInFistSystem[1];
			Vertex[4][2] += SecondHalfSizeInFistSystem[2];

			Vertex[5] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[5][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[5][1] += SecondHalfSizeInFistSystem[1];
			Vertex[5][2] -= SecondHalfSizeInFistSystem[2];

			Vertex[6] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[6][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[6][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[6][2] += SecondHalfSizeInFistSystem[2];

			Vertex[7] = (SecondBoxCenterInFirstBoxSystem);
			Vertex[7][0] -= SecondHalfSizeInFistSystem[0];
			Vertex[7][1] -= SecondHalfSizeInFistSystem[1];
			Vertex[7][2] -= SecondHalfSizeInFistSystem[2];

			
			int indexes[8];
			float compenetration[8];
			unsigned int pointsInside = 0;
			bool isInside = false;
			for (unsigned int i = 0; i < 8; ++i)
			{
				isInside = Vertex[i][0] > Min[0] && Vertex[i][1] > Min[1] && Vertex[i][2] > Min[2] &&
					Vertex[i][0] < Max[0] && Vertex[i][1] < Max[1] && Vertex[i][2] < Max[2];
				if (isInside)
				{
					indexes[pointsInside] = i;
					compenetration[pointsInside] = (Vertex[i] - second->GetWorldPosition()).SqrMagnitude();
					++pointsInside;
				}
			}

			//Compute Collision Data iff there is a collision
			if (pointsInside)
			{
				float CompenetrationSum = compenetration[0];
				Vertex[indexes[0]][0] *= compenetration[0];
				Vertex[indexes[0]][1] *= compenetration[0];
				Vertex[indexes[0]][2] *= compenetration[0];
				//centroid of points which is the point of collision impact
				for (unsigned int i = 1; i < pointsInside; ++i)
				{
					Vertex[indexes[0]][0] += Vertex[indexes[i]][0];
					Vertex[indexes[0]][1] += Vertex[indexes[i]][1];
					Vertex[indexes[0]][2] += Vertex[indexes[i]][2];
					CompenetrationSum += compenetration[i];
					compenetration[0] = std::fmaxf(compenetration[0], compenetration[i]);
				}
				Vertex[indexes[0]][0] /= CompenetrationSum;
				Vertex[indexes[0]][1] /= CompenetrationSum;
				Vertex[indexes[0]][2] /= CompenetrationSum;

				//Compute normal by clamping on max value
				CentersDistance.Normalize();
				float x, y, z;
				x = CentersDistance.getX();
				y = CentersDistance.getY();
				z = CentersDistance.getZ();
				if (x > y)
				{
					if (x > z)
					{
						CentersDistance.Set(x, 0, 0);
					}
					else
					{
						CentersDistance.Set(0, 0, z);
					}
				}
				else
				{
					if (y > z)
					{
						CentersDistance.Set(0, y, 0);
					}
					else
					{
						CentersDistance.Set(0, 0, z);
					}
				}
				CentersDistance.Normalize();
				//Compute Compenetration
				return new Collision(compenetration[0], Vertex[indexes[0]], CentersDistance);
			}
			//If i'm here FUCK THAT
			return nullptr;
		};
	};

	template<>
	class CollisionDetectionAlgorithm<SphereCollider, SphereCollider>
	{
	public:
		
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<SphereCollider*>(&first), static_cast<SphereCollider*>(&second));
		}

	private:
		
		static Collision* CollisionComputation(SphereCollider* first, SphereCollider* second)
		{
			Vector3 CentersDistance = first->GetWorldPosition() -  second->GetWorldPosition();
			float distance = VectorOp::DotProduct(CentersDistance, CentersDistance);
			float radiiSum = first->GetRadius() + second->GetRadius();
			if (distance < radiiSum*radiiSum)
			{
				float compenetrarion = radiiSum - sqrtf(distance);
				CentersDistance.Normalize();
				return new Collision(compenetrarion, CentersDistance*first->GetRadius(),CentersDistance);
			}
			return nullptr;
		};
	};

	template<>
	class CollisionDetectionAlgorithm<BoxCollider, SphereCollider>
	{
	public:
		template<typename T, typename U>
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<T*>(&first), static_cast<U*>(&second));
		};
		//for symmetry sake
		template<>
		static Collision* Fire<SphereCollider, BoxCollider>(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<BoxCollider*>(&second), static_cast<SphereCollider*>(&first));
		}
	private:
		static Collision* CollisionComputation(BoxCollider* first, SphereCollider* second)
		{
	
			Vector3 SphereCenterInBoxSystem(second->GetWorldPosition());
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), SphereCenterInBoxSystem, SphereCenterInBoxSystem);
			Vector3 Min(first->GetWorldPosition() - first->GetHalfSize());
			Vector3 Max(first->GetWorldPosition() + first->GetHalfSize());
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), Min, Min);
			MatrixOp::Rotate<MatrixOp::ToObjSpace>(first->GetRotation().ToMatrix(), Max, Max);

			float distance = 0;
			if (SphereCenterInBoxSystem.getX() < Min.getX())
			{
				distance += (SphereCenterInBoxSystem.getX() - Min.getX()) *(SphereCenterInBoxSystem.getX() - Min.getX());
			}
			else
			{
				if (SphereCenterInBoxSystem.getX() > Max.getX())
				{
					distance += (SphereCenterInBoxSystem.getX() - Max.getX()) *(SphereCenterInBoxSystem.getX() - Max.getX());
				}
			}
			if (SphereCenterInBoxSystem.getY() < Min.getY())
			{
				distance += (SphereCenterInBoxSystem.getY() - Min.getY()) *(SphereCenterInBoxSystem.getY() - Min.getY());
			}
			else
			{
				if (SphereCenterInBoxSystem.getY() > Max.getY())
				{
					distance += (SphereCenterInBoxSystem.getY() - Max.getY()) *(SphereCenterInBoxSystem.getY() - Max.getY());
				}
			}
			if (SphereCenterInBoxSystem.getZ() < Min.getZ())
			{
				distance += (SphereCenterInBoxSystem.getZ() - Min.getZ()) *(SphereCenterInBoxSystem.getZ() - Min.getZ());
			}
			else
			{
				if (SphereCenterInBoxSystem.getZ() > Max.getZ())
				{
					distance += (SphereCenterInBoxSystem.getZ() - Max.getZ()) *(SphereCenterInBoxSystem.getZ() - Max.getZ());
				}
			}
			if (distance< second->GetRadius()*second->GetRadius()){
				distance = second->GetRadius() - sqrtf(distance);
				Vector3 CentersDistance = first->GetWorldPosition() - second->GetWorldPosition();
				CentersDistance.Normalize();
				return new Collision(distance, CentersDistance*second->GetRadius(), CentersDistance);
			}

			return nullptr;
		};
	};
}

/*
Box Box SAT
Vector3 const& CenterOfFirstBox = first->GetWorldPosition();
Vector3 const* AxisesOfFirstBox[3];
AxisesOfFirstBox[0] = &first->GetAxis(0);
Vector3 const& FirstBoxHalfSize = first->GetHalfSize();
Vector3 const& CenterOfSecondBox = second->GetWorldPosition();
Vector3 const* AxisesOfSecondBox[3];
AxisesOfSecondBox[0] = &second->GetAxis(0);
AxisesOfSecondBox[1] = &second->GetAxis(1);
AxisesOfSecondBox[2] = &second->GetAxis(2);
Vector3 const& SecondBoxHalfSize = second->GetHalfSize();

//Optimization TO DO
//for numerical stability 1-epsilon checking for parallelism
//const float cutoff = 1.0f - 0.00001f;
//bool existsParallelPair = false;

Vector3 CentersDistance(CenterOfSecondBox - CenterOfFirstBox);

float MatrixOfDotProduct[9];
float AbsOfDotProduct[9];
float DotProductCentersAndAxisesOfFirstBox[3];
float r0, r1, r;
float r01;

for (int i = 0; i < 3; ++i)
{
MatrixOfDotProduct[i] = VectorOp::DotProduct(*(AxisesOfFirstBox[0]), *(AxisesOfSecondBox[i]));
AbsOfDotProduct[i] = std::abs(MatrixOfDotProduct[i]);
//	existsParallelPair = AbsOfDotProduct[i] > cutoff;
}
DotProductCentersAndAxisesOfFirstBox[0] = VectorOp::DotProduct(CentersDistance, *(AxisesOfFirstBox[0]));
r = std::abs(DotProductCentersAndAxisesOfFirstBox[0]);
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[0] + SecondBoxHalfSize.getY() * AbsOfDotProduct[1] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[2];
r01 = FirstBoxHalfSize.getX() + r1;
if (r > r01)
{
return nullptr;
}
AxisesOfFirstBox[1]= &first->GetAxis(1);
for (int i = 0; i < 3; ++i)
{
MatrixOfDotProduct[3 + i] = VectorOp::DotProduct(*(AxisesOfFirstBox[1]), *(AxisesOfSecondBox[i]));
AbsOfDotProduct[3 + i] = std::abs(MatrixOfDotProduct[3 + i]);
//	existsParallelPair = AbsOfDotProduct[3 + i] > cutoff;
}
DotProductCentersAndAxisesOfFirstBox[1] = VectorOp::DotProduct(CentersDistance, *(AxisesOfFirstBox[1]));
r = std::abs(DotProductCentersAndAxisesOfFirstBox[1]);
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[3] + SecondBoxHalfSize.getY() * AbsOfDotProduct[4] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[5];
r01 = FirstBoxHalfSize.getY() + r1;
if (r > r01)
{
return nullptr;
}
AxisesOfFirstBox[2]= & first->GetAxis(2);

for (int i = 0; i < 3; ++i)
{
MatrixOfDotProduct[6 + i] = VectorOp::DotProduct(*(AxisesOfFirstBox[2]), *(AxisesOfSecondBox[i]));
AbsOfDotProduct[6 + i] = std::abs(MatrixOfDotProduct[6 + i]);
//	existsParallelPair = AbsOfDotProduct[6 + i] > cutoff;
}
DotProductCentersAndAxisesOfFirstBox[2] = VectorOp::DotProduct(CentersDistance, *(AxisesOfFirstBox[2]));
r = std::abs(DotProductCentersAndAxisesOfFirstBox[2]);
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[6] + SecondBoxHalfSize.getY() * AbsOfDotProduct[7] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[8];
r01 = FirstBoxHalfSize.getZ() + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(VectorOp::DotProduct(CentersDistance, *(AxisesOfSecondBox[0])));
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[0] + FirstBoxHalfSize.getY() * AbsOfDotProduct[3] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[6];
r01 = r0 + SecondBoxHalfSize.getX();
if (r > r01)
{
return nullptr;
}

r = std::abs(VectorOp::DotProduct(CentersDistance, *(AxisesOfSecondBox[1])));
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[1] + FirstBoxHalfSize.getY() * AbsOfDotProduct[4] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[7];
r01 = r0 + SecondBoxHalfSize.getY();
if (r > r01)
{
return nullptr;
}

r = std::abs(VectorOp::DotProduct(CentersDistance, *(AxisesOfSecondBox[2])));
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[2] + FirstBoxHalfSize.getY() * AbsOfDotProduct[5] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[8];
r01 = r0 + SecondBoxHalfSize.getZ();
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[3] - DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[6]);
r0 = FirstBoxHalfSize.getY() * AbsOfDotProduct[6] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[3];
r1 = SecondBoxHalfSize.getY() * AbsOfDotProduct[2] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[1];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[4] - DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[7]);
r0 = FirstBoxHalfSize.getY() * AbsOfDotProduct[7] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[4];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[2] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[0];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[5] - DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[8]);
r0 = FirstBoxHalfSize.getY() * AbsOfDotProduct[8] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[5];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[1] + SecondBoxHalfSize.getY() * AbsOfDotProduct[0];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[6] - DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[0]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[6] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[0];
r1 = SecondBoxHalfSize.getY() * AbsOfDotProduct[5] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[4];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[7] - DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[1]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[7] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[1];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[5] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[3];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[8] - DotProductCentersAndAxisesOfFirstBox[2] * MatrixOfDotProduct[2]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[8] + FirstBoxHalfSize.getZ() * AbsOfDotProduct[2];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[4] + SecondBoxHalfSize.getY() * AbsOfDotProduct[3];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[0] - DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[3]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[3] + FirstBoxHalfSize.getY() * AbsOfDotProduct[0];
r1 = SecondBoxHalfSize.getY() * AbsOfDotProduct[8] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[7];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[1] - DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[4]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[4] + FirstBoxHalfSize.getY() * AbsOfDotProduct[1];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[8] + SecondBoxHalfSize.getZ() * AbsOfDotProduct[6];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

r = std::abs(DotProductCentersAndAxisesOfFirstBox[1] * MatrixOfDotProduct[2] - DotProductCentersAndAxisesOfFirstBox[0] * MatrixOfDotProduct[5]);
r0 = FirstBoxHalfSize.getX() * AbsOfDotProduct[5] + FirstBoxHalfSize.getY() * AbsOfDotProduct[2];
r1 = SecondBoxHalfSize.getX() * AbsOfDotProduct[7] + SecondBoxHalfSize.getY() * AbsOfDotProduct[6];
r01 = r0 + r1;
if (r > r01)
{
return nullptr;
}

return new Collision(???,???,???);
*/