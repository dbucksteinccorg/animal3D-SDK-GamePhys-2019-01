/*
	Copyright 2011-2019 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_Particle.c
	Implementation of particle.
*/

#include "a3_Particle.h"


//-----------------------------------------------------------------------------

// internal helper to multiply vec3 with quaternion (not rotation!)
// results in a quaternion, useful for derivative calculation
inline a3real4r a3particleMultiplyVec3Quat(a3real4p q_out, const a3real3p vL, const a3real4p qR)
{
	// ****TO-DO: 
	//	- implement simplified quaternion multiplication

	a3real3 tmp;
	a3real3Cross(q_out, vL, qR);
	a3real3Add(q_out, a3real3ProductS(tmp, vL, qR[3]));
	q_out[3] = -a3real3Dot(vL, qR);

	// done
	return q_out;
}

// internal helper to perform vec3 transform
inline a3real3r a3particleTransformPoint3_internal(a3real3p v_out, const a3real3p v, const a3real4x4p t)
{
	// ****TO-DO: 
	//	- transform vector by matrix

	v_out[0] = t[0][0] * v[0] + t[1][0] * v[1] + t[2][0] * v[2] + t[3][0];
	v_out[1] = t[0][1] * v[0] + t[1][1] * v[1] + t[2][1] * v[2] + t[3][1];
	v_out[2] = t[0][2] * v[0] + t[1][2] * v[1] + t[2][2] * v[2] + t[3][2];

	// done
	return v_out;
}

// internal helper to perform rebase
inline a3real3x3r a3particleRebaseMatrix_internal(a3real3x3p m_out, const a3real3x3p m, const a3real4x4p t)
{
	// ****TO-DO: 
	//	- utility to rebase matrix given a transform: 
	//		final = t * m * t^-1
	//	- if we know t represents a rotation then its inverse is its transpose
	//	- possibly messy but that means direct and therefore efficient

	// solution to (m * t^inv)
	a3real3x3 tmp;

	// first column
	tmp[0][0] = m[0][0] * t[0][0] + m[1][0] * t[1][0] + m[2][0] * t[2][0];
	tmp[0][1] = m[0][1] * t[0][0] + m[1][1] * t[1][0] + m[2][1] * t[2][0];
	tmp[0][2] = m[0][2] * t[0][0] + m[1][2] * t[1][0] + m[2][2] * t[2][0];

	// second column
	tmp[1][0] = m[0][0] * t[0][1] + m[1][0] * t[1][1] + m[2][0] * t[2][1];
	tmp[1][1] = m[0][1] * t[0][1] + m[1][1] * t[1][1] + m[2][1] * t[2][1];
	tmp[1][2] = m[0][2] * t[0][1] + m[1][2] * t[1][1] + m[2][2] * t[2][1];

	// third column
	tmp[2][0] = m[0][0] * t[0][2] + m[1][0] * t[1][2] + m[2][0] * t[2][2];
	tmp[2][1] = m[0][1] * t[0][2] + m[1][1] * t[1][2] + m[2][1] * t[2][2];
	tmp[2][2] = m[0][2] * t[0][2] + m[1][2] * t[1][2] + m[2][2] * t[2][2];


	// now (t * tmp)
	m_out[0][0] = t[0][0] * tmp[0][0] + t[1][0] * tmp[0][1] + t[2][0] * tmp[0][2];
	m_out[0][1] = t[0][1] * tmp[0][0] + t[1][1] * tmp[0][1] + t[2][1] * tmp[0][2];
	m_out[0][2] = t[0][2] * tmp[0][0] + t[1][2] * tmp[0][1] + t[2][2] * tmp[0][2];

	m_out[1][0] = t[0][0] * tmp[1][0] + t[1][0] * tmp[1][1] + t[2][0] * tmp[1][2];
	m_out[1][1] = t[0][1] * tmp[1][0] + t[1][1] * tmp[1][1] + t[2][1] * tmp[1][2];
	m_out[1][2] = t[0][2] * tmp[1][0] + t[1][2] * tmp[1][1] + t[2][2] * tmp[1][2];

	m_out[2][0] = t[0][0] * tmp[2][0] + t[1][0] * tmp[2][1] + t[2][0] * tmp[2][2];
	m_out[2][1] = t[0][1] * tmp[2][0] + t[1][1] * tmp[2][1] + t[2][1] * tmp[2][2];
	m_out[2][2] = t[0][2] * tmp[2][0] + t[1][2] * tmp[2][1] + t[2][2] * tmp[2][2];

	// done
	return m_out;
}


//-----------------------------------------------------------------------------

// named Euler methods

// ****TO-DO: 
// explicit Euler: integrate current velocity
extern inline void a3particleIntegrateEulerExplicit(a3_Particle *p, const a3real dt)
{
//	a3vec4 d;

}

// ****TO-DO: 
// semi-implicit Euler: integrate next velocity
extern inline void a3particleIntegrateEulerSemiImplicit(a3_Particle *p, const a3real dt)
{
//	a3vec4 d;

}

// ****TO-DO: 
// kinematic: integrate average of current and next velocities
extern inline void a3particleIntegrateEulerKinematic(a3_Particle *p, const a3real dt)
{
//	a3vec4 d;

}


//-----------------------------------------------------------------------------

// particle helpers

// reset
extern inline void a3particleReset(a3_Particle *p)
{
	p->position = a3zeroVec3;
	p->velocity = a3zeroVec3;
	p->acceleration = a3zeroVec3;
	p->momentum = a3zeroVec3;
	p->force = a3zeroVec3;
	p->mass = p->massInv = a3realZero;

	// ****TO-DO: 
	//	- reset new members

}

// ****TO-DO: 
// set mass
extern inline a3i32 a3particleSetMass(a3_Particle *p, const a3real mass)
{
	if (p)
	{

	}
	return -1;
}

// ****TO-DO: 
// check if particle is moving
extern inline a3i32 a3particleIsMoving(const a3_Particle *p)
{
	if (p)
	{

	}
	return -1;
}

// ****TO-DO: 
// apply force at center of mass
extern inline a3i32 a3particleApplyForceDirect(a3_Particle *p, const a3real3p f)
{
	if (p && f)
	{

	}
	return 0;
}

// ****TO-DO: 
// convert force to acceleration
extern inline a3i32 a3particleConvertForce(a3_Particle *p)
{
	if (p)
	{
		// a(t) = F(t) / m

	}
	return 0;
}

// ****TO-DO: 
// reset force
extern inline a3i32 a3particleResetForce(a3_Particle *p)
{
	if (p)
	{

	}
	return -1;
}

// ****TO-DO: 
// check if particle is rotating
extern inline a3i32 a3particleIsRotating(const a3_Particle *p)
{
	if (p)
	{
		// determine if particle is rotating (angular speed is not zero)

	}
	return -1;
}

// ****TO-DO: 
// apply force at other location
extern inline a3i32 a3particleApplyForceLocation(a3_Particle *p, const a3real3p f, const a3real3p location_world)
{
	if (p && f && location_world)
	{
		//	arm = loc - c_mass
		//	torque += arm x F_applied

	}
	return 0;
}

// ****TO-DO: 
// convert torque to angular acceleration
extern inline a3i32 a3particleConvertTorque(a3_Particle *p)
{
	if (p)
	{
		// alpha(t) = I_inv(t) * torque(t)

	}
	return 0;
}

// ****TO-DO: 
// reset torque
extern inline a3i32 a3particleResetTorque(a3_Particle *p)
{
	if (p)
	{

	}
	return -1;
}


//-----------------------------------------------------------------------------

// ****TO-DO: 
// calculate inertia tensor for shapes
//	(set mass first!)
//	 note: body axes are 0, 1 and 2 for x, y and z respectively

//	solid sphere
extern inline a3i32 a3particleSetLocalInertiaTensorSphereSolid(a3_Particle *p, const a3real radius)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	hollow sphere
extern inline a3i32 a3particleSetLocalInertiaTensorSphereHollow(a3_Particle *p, const a3real radius)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	solid box
extern inline a3i32 a3particleSetLocalInertiaTensorBoxSolid(a3_Particle *p, const a3real width, const a3real height, const a3real depth)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	hollow box
extern inline a3i32 a3particleSetLocalInertiaTensorBoxHollow(a3_Particle *p, const a3real width, const a3real height, const a3real depth)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	solid cylinder
extern inline a3i32 a3particleSetLocalInertiaTensorCylinderSolid(a3_Particle *p, const a3real radius, const a3real height, const a3i32 bodyAxis)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	solid cone about apex
extern inline a3i32 a3particleSetLocalInertiaTensorConeSolidApex(a3_Particle *p, const a3real radius, const a3real height, const a3i32 bodyAxis)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	rod about end
extern inline a3i32 a3particleSetLocalInertiaTensorRodEnd(a3_Particle *p, const a3real length, const a3i32 bodyAxis)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}
//	rod about center
extern inline a3i32 a3particleSetLocalInertiaTensorRodCenter(a3_Particle *p, const a3real length, const a3i32 bodyAxis)
{
	if (p)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 


		return 1;
	}
	return 0;
}

// ****TO-DO: 
// calculate total mass and center of mass from a set of influences
extern inline a3i32 a3particleCalculateLocalCenterOfMass(a3_Particle *p, const a3real3 *influenceList, const a3real *massList, const a3ui32 count)
{
	if (p && influenceList && massList)
	{
	//	a3ui32 i;
	//	a3vec3 c, dc;
	//	a3real m, dm;

		//	- accumulate mass and weighted total of influences
		//	- store mass and multiply weighted total by inv mass


		return 1;
	}
	return 0;
}

// ****TO-DO: 
// calculate inertia tensor and inverse from a set of influences
//	(calculate center of mass first!)
extern inline a3i32 a3particleCalculateLocalInertiaTensor(a3_Particle *p, const a3real3 *influenceList, const a3real *massList, const a3ui32 count)
{
	if (p && influenceList && massList)
	{
	//	a3ui32 i;
	//	a3mat3 I = a3identityMat3;
	//	a3vec3 dr;
	//	a3real dm, x2, y2, z2;

		//	- accumulate unique components of tensor
		//	- copy symmetric elements, store and invert


		return 1;
	}
	return 0;
}

// ****TO-DO: 
// update center of mass relative to world
extern inline a3i32 a3particleUpdateCenterOfMass(a3_Particle *p, const a3real4x4p transform)
{
	if (p && transform)
	{
		// multiply matrix by local center of mass

	}
	return 0;
}

// ****TO-DO: 
// update inertia tensor
extern inline a3i32 a3particleUpdateInertiaTensor(a3_Particle *p, const a3real4x4p transform)
{
	if (p && transform)
	{
		// change of basis: 
		//	- current tensor is R*I*R^-1
		//	- current tensor inverse is R*I^-1*R^-1

	}
	return 0;
}


//-----------------------------------------------------------------------------
