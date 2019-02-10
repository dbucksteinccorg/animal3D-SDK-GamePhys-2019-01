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
		a3vec3 position;
		a3vec3 velocity;
		a3vec3 acceleration;
	
		// ****TO-DO: 
		//	- add new members

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


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_PARTICLE_H