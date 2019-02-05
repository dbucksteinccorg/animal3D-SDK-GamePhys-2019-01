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

	// ****TO-DO: 
	// particle for motion
	struct a3_Particle
	{
		a3vec3 position;
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
	inline void a3particleReset(a3_Particle *p);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_PARTICLE_H