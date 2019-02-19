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
	
	a3_Particle.h
	Single particle for physics simulation.
*/

#ifndef __ANIMAL3D_PARTICLE_H
#define __ANIMAL3D_PARTICLE_H


//-----------------------------------------------------------------------------

#include "a3_Force.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_Particle		a3_Particle;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// particle for motion
	struct a3_Particle
	{
		// linear dynamics: 
		a3vec3 position;
		a3vec3 velocity;
		a3vec3 acceleration;
		a3vec3 momentum;
		a3vec3 force;
		a3real mass, massInv;

		// angular dynamics: 
		// ****TO-DO: 
		//	- add angular dynamics vectors
		//	- add local inertia tensor and inverse for convenience
		//	- add world inertia tensor and inverse
		//	- add local center of mass for convenience
		//	- add world center of mass

	};


//-----------------------------------------------------------------------------

	// named Euler methods

	// explicit Euler: integrate current velocity
	inline void a3particleIntegrateEulerExplicit(a3_Particle *p, const a3real dt);
	
	// semi-implicit Euler: integrate next velocity
	inline void a3particleIntegrateEulerSemiImplicit(a3_Particle *p, const a3real dt);
	
	// kinematic: integrate average of current and next velocities
	inline void a3particleIntegrateEulerKinematic(a3_Particle *p, const a3real dt);


//-----------------------------------------------------------------------------

	// particle helpers

	// reset
	inline void a3particleReset(a3_Particle *p);

	// set mass
	inline a3i32 a3particleSetMass(a3_Particle *p, const a3real mass);

	// check if particle is moving
	inline a3i32 a3particleIsMoving(const a3_Particle *p);

	// apply force at center of mass
	inline a3i32 a3particleApplyForceDirect(a3_Particle *p, const a3real3p f);

	// convert force to acceleration
	inline a3i32 a3particleConvertForce(a3_Particle *p);

	// reset force
	inline a3i32 a3particleResetForce(a3_Particle *p);

	// check if particle is rotating
	inline a3i32 a3particleIsRotating(const a3_Particle *p);

	// apply force at other location
	inline a3i32 a3particleApplyForceLocation(a3_Particle *p, const a3real3p f, const a3real3p location_world);

	// convert torque to angular acceleration
	inline a3i32 a3particleConvertTorque(a3_Particle *p);

	// reset torque
	inline a3i32 a3particleResetTorque(a3_Particle *p);


//-----------------------------------------------------------------------------

	// calculate inertia tensor for shapes
	//	(set mass first!)
	//	 note: body axes are 0, 1 and 2 for x, y and z respectively

	//	solid sphere
	inline a3i32 a3particleSetLocalInertiaTensorSphereSolid(a3_Particle *p, const a3real radius);
	//	hollow sphere
	inline a3i32 a3particleSetLocalInertiaTensorSphereHollow(a3_Particle *p, const a3real radius);
	//	solid box
	inline a3i32 a3particleSetLocalInertiaTensorBoxSolid(a3_Particle *p, const a3real width, const a3real height, const a3real depth);
	//	hollow box
	inline a3i32 a3particleSetLocalInertiaTensorBoxHollow(a3_Particle *p, const a3real width, const a3real height, const a3real depth);
	//	solid cylinder
	inline a3i32 a3particleSetLocalInertiaTensorCylinderSolid(a3_Particle *p, const a3real radius, const a3real height, const a3i32 bodyAxis);
	//	solid cone about apex
	inline a3i32 a3particleSetLocalInertiaTensorConeSolidApex(a3_Particle *p, const a3real radius, const a3real height, const a3i32 bodyAxis);
	//	rod about end
	inline a3i32 a3particleSetLocalInertiaTensorRodEnd(a3_Particle *p, const a3real length, const a3i32 bodyAxis);
	//	rod about center
	inline a3i32 a3particleSetLocalInertiaTensorRodCenter(a3_Particle *p, const a3real length, const a3i32 bodyAxis);

	// calculate total mass and center of mass from a set of influences
	inline a3i32 a3particleCalculateLocalCenterOfMass(a3_Particle *p, const a3real3 *influenceList, const a3real *massList, const a3ui32 count);

	// calculate inertia tensor and inverse from a set of influences
	//	(calculate center of mass first!)
	inline a3i32 a3particleCalculateLocalInertiaTensor(a3_Particle *p, const a3real3 *influenceList, const a3real *massList, const a3ui32 count);

	// update center of mass relative to world
	inline a3i32 a3particleUpdateCenterOfMass(a3_Particle *p, const a3real4x4p transform);

	// update inertia tensor relative to world
	inline a3i32 a3particleUpdateInertiaTensor(a3_Particle *p, const a3real4x4p transform);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_PARTICLE_H