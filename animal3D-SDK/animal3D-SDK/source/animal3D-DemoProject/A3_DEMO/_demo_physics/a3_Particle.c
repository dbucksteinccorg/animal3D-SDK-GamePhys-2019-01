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

// named Euler methods

// ****TO-DO: 
// explicit Euler: integrate current velocity
extern inline void a3particleIntegrateEulerExplicit(a3_Particle *p, const a3real dt)
{
//	a3vec3 d;

}

// ****TO-DO: 
// semi-implicit Euler: integrate next velocity
extern inline void a3particleIntegrateEulerSemiImplicit(a3_Particle *p, const a3real dt)
{
//	a3vec3 d;

}

// ****TO-DO: 
// kinematic: integrate average of current and next velocities
extern inline void a3particleIntegrateEulerKinematic(a3_Particle *p, const a3real dt)
{
//	a3vec3 d;

}


//-----------------------------------------------------------------------------

// particle helpers

// ****TO-DO: 
extern inline void a3particleReset(a3_Particle *p)
{
	p->position = a3zeroVec3;

}


//-----------------------------------------------------------------------------
