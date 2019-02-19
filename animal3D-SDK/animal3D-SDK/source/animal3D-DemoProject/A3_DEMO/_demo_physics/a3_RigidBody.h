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
	
	a3_RigidBody.h
	Rigid body for physics simulation.
*/

#ifndef __ANIMAL3D_RIGIDBODY_H
#define __ANIMAL3D_RIGIDBODY_H


#include "a3_Particle.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_RigidBody		a3_RigidBody;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// alternative name for particle (it does everything we need it to...)
	typedef a3_Particle a3_RigidBodyMotionController;

	// rb
	struct a3_RigidBody
	{
		// particle is "component" attached to make it move
		a3_RigidBodyMotionController motionController[1];
	};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_RIGIDBODY_H