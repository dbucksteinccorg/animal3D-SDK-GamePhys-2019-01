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
	
	a3_PhysicsWorld.h
	Physics world management header.
*/

#ifndef __ANIMAL3D_PHYSICSWORLD_H
#define __ANIMAL3D_PHYSICSWORLD_H


// math library
#include "animal3D-A3DM/animal3D-A3DM.h"

// other framework includes
#include "animal3D/a3utility/a3_Timer.h"
#include "animal3D/a3utility/a3_Thread.h"

// physics includes
#include "a3_RigidBody.h"
#include "a3_Ray.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_PhysicsWorldState		a3_PhysicsWorldState;
	typedef struct a3_PhysicsWorld			a3_PhysicsWorld;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// counters
	enum a3_PhysicsWorldMaxCount
	{
		physicsWorldMaxCount_rigidbody = 16,
	};


//-----------------------------------------------------------------------------

	// state of a physics world: things that can be used for graphics ONLY
	//	-> graphics will READ position and rotation
	struct a3_PhysicsWorldState
	{
		// send to graphics
		a3vec3 position_rigidbody[physicsWorldMaxCount_rigidbody];
		a3quat rotation_rigidbody[physicsWorldMaxCount_rigidbody];
		a3mat4 transform_rigidbody[physicsWorldMaxCount_rigidbody];
		a3mat4 transformInv_rigidbody[physicsWorldMaxCount_rigidbody];

		// active object counter
		a3ui32 count_rigidbody;
	};


//-----------------------------------------------------------------------------

	// persistent physics world data structure
	struct a3_PhysicsWorld
	{
		// state to store all of the things that graphics will use
		a3_PhysicsWorldState pw_state[1];

		// dedicated timer
		a3_Timer pw_timer[1];

		// dedicated thread
		a3_Thread pw_thread[1];

		// simple mutex lock
		a3boolean pw_lock;

		// initialized flag
		a3boolean pw_init;


		// rigid bodies
		union {
			a3_RigidBody rb[physicsWorldMaxCount_rigidbody];
			struct {
				a3_RigidBody
					testRB_plane[1],
					testRB_sphere[2],
					testRB_box[2],
					testRB_cylinder[2],
					testRB_torus[2],
					testRB_teapot[2];
			};
		};

		// the ray and ray hit
		a3_Ray tmpRay[1];
		a3_RayHit tmpRayHit[1];
	};


//-----------------------------------------------------------------------------

	// physics simulation step
	a3ret a3physicsWorldUpdate(a3_PhysicsWorld *world, a3f64 dt);

	// reset world states
	a3ret a3physicsWorldStateReset(a3_PhysicsWorld *world);

	// threaded physics simulation
	inline void a3physicsWorldThreadInit(a3_PhysicsWorld *world);
	inline void a3physicsWorldThreadTerm(a3_PhysicsWorld *world);

	// mutex handling
	inline a3ret a3physicsWorldLock(a3_PhysicsWorld *world);
	inline a3ret a3physicsWorldUnlock(a3_PhysicsWorld *world);

	// extra utilities
	void a3physicsWorldRayTest(a3_PhysicsWorld *world);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_PHYSICSWORLD_H