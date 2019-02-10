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
	
	a3_PhysicsWorld.c
	Physics world management source.
*/

#include "a3_PhysicsWorld.h"

#include <stdio.h>


//-----------------------------------------------------------------------------

// internal utility for initializing physics world and state
void a3physicsInitialize_internal(a3_PhysicsWorld *world)
{
	// generic counter
	a3ui32 i;

	// hard-set random seed for predictability (i.e. scenario replication)
	a3randomSetSeed(0);


	// reset all physics objects
	for (i = 0; i < physicsWorldMaxCount_particle; ++i)
		a3particleReset(world->particle + i);

	// initial values: set positions, related functions and values
	// entirely force-controlled particles do not need a full set 
	//	of initial values (e.g. can start with zero velocity)

	world->testParticle_springy->position.x = +8.0f;
	world->testParticle_springy->position.z = +6.0f;
	a3particleSetMass(world->testParticle_springy, 1.0f);

	world->testParticle_gravity->position.y = +8.0f;
	world->testParticle_gravity->position.z = +6.0f;
	a3particleSetMass(world->testParticle_gravity, 1.0f);

	world->testParticle_draggy->position.x = -8.0f;
	world->testParticle_draggy->position.z = +6.0f;
	a3particleSetMass(world->testParticle_draggy, 1.0f);

	world->testParticle_slippy->position.y = -8.0f;
	world->testParticle_slippy->position.z = -1.0f;
	a3particleSetMass(world->testParticle_slippy, 1.0f);


	// reset state
	a3physicsWorldStateReset(world->pw_state);
	world->pw_state->count_particle = 4;


	// done
	printf("\n physics thread initialized");
	world->pw_init = 1;
}

// internal utility for terminating physics world and state
void a3physicsTerminate_internal(a3_PhysicsWorld *world)
{
	// any termination tasks here


	// done
	printf("\n physics thread terminated");
	world->pw_init = 0;
}


//-----------------------------------------------------------------------------

// internal physics world thread function
a3ret a3physicsThread_internal(a3_PhysicsWorld *world)
{
	// desired physics update rate (updates per second)
	// -> use zero for "continuous mode"
	const a3f64 rate = 100.0;

	// pointer to timer for convenience
	a3_Timer *timerPtr = world->pw_timer;

	// second counter for physics (debugging)
	a3ui32 currSecond = 0, prevSecond = 0;

	// create world
	a3physicsInitialize_internal(world);

	// start timer
	// rate should be set before beginning thread
	a3timerSet(timerPtr, rate);
	a3timerStart(timerPtr);

	// if lock is negative, terminate
	// originator of thread should decide this
	while (world->pw_lock >= 0)
	{
		if (a3timerUpdate(timerPtr))
		{
			// update timer ticked, do the thing
			a3physicsWorldUpdate(world, timerPtr->previousTick);

			// debug display time in seconds every second
			currSecond = (a3ui32)(timerPtr->totalTime);
			if (currSecond > prevSecond)
			{
				prevSecond = currSecond;
				printf("\n physics time: %.4lf;  ticks: %llu \n     ups avg: %.4lf;  dt avg: %.4lf",
					timerPtr->totalTime,
					timerPtr->ticks,
					(a3f64)timerPtr->ticks / timerPtr->totalTime,
					timerPtr->totalTime / (a3f64)timerPtr->ticks
				);
			}
		}
	}

	// terminate world
	a3physicsTerminate_internal(world);
	return 0;
}


//-----------------------------------------------------------------------------

// physics simulation step
a3ret a3physicsWorldUpdate(a3_PhysicsWorld *world, a3f64 dt)
{
	// copy of state to edit before committing writing to world
	a3_PhysicsWorldState state_copy[1] = { *world->pw_state };

	// generic counter
	a3ui32 i;

	// time as real
	const a3real t_r = (a3real)(world->pw_timer->totalTime);
	const a3real dt_r = (a3real)(dt);

	// tmp force vectors
//	a3vec3 f_gravity;
//	a3vec3 f_normal;
//	a3vec3 f_sliding;
//	a3vec3 f_friction_s;
//	a3vec3 f_friction_k;
//	a3vec3 f_drag;
//	a3vec3 f_spring;
//	a3vec3 f_damp_l;

	// tmp particle helpers
//	a3_Particle *currentParticle;
//	const a3vec3 springyAnchor = { 0.0f, 0.0f, 10.0f };
//	const a3vec3 slippyForce = { 0.0f, 5.0f, 0.0f };


	// ****TO-DO: 
	// update physics objects 
	//	- reset and apply forces
	//	- integrate
	//	- force conversion
	//	- additional tasks (e.g. clamp position)


	// update state
	for (i = 0; i < state_copy->count_particle; ++i)
	{
		state_copy->position_particle[i] = world->particle[i].position;
	}


	// write operation is locked
	if (a3physicsWorldLock(world) > 0)
	{
		// copy state to world
		*world->pw_state = *state_copy;
		a3physicsWorldUnlock(world);
	}

	// done
	return 0;
}


//-----------------------------------------------------------------------------

// reset world state
a3ret a3physicsWorldStateReset(a3_PhysicsWorldState *worldState)
{
	// generic counter
	a3ui32 i;

	if (worldState)
	{
		// reset all state data appropriately
		for (i = 0; i < physicsWorldMaxCount_particle; ++i)
		{
			worldState->position_particle[i] = a3zeroVec3;
		}
		return i;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// threaded physics simulation
extern inline void a3physicsWorldThreadInit(a3_PhysicsWorld *world)
{
	// reset flags then launch new thread for this world; 
	//	wait for world and thread to initialize before continuing
	world->pw_init = 0;
	world->pw_lock = 0;
	a3threadLaunch(world->pw_thread, (a3_threadfunc)a3physicsThread_internal, world, "a3physicsThread_internal");
	while (!world->pw_init || !world->pw_thread->threadID);
}

extern inline void a3physicsWorldThreadTerm(a3_PhysicsWorld *world)
{
	// terminate physics world by acquiring lock then invalidating it; 
	//	wait for world and thread to terminate before continuing
	a3physicsWorldLock(world);
	world->pw_lock = -1;
	while (world->pw_init || world->pw_thread->threadID);
}


//-----------------------------------------------------------------------------

// get thread ID
#ifdef _WIN32
#include <Windows.h>
inline a3ret threadID()
{
	return GetCurrentThreadId();
}
#else
#include <sys/types.h>
inline a3ret threadID()
{
	return gettid();
}
#endif	// _WIN32


// mutex handling
extern inline a3ret a3physicsWorldLock(a3_PhysicsWorld *world)
{
	// wait for lock to be released, then set it
	while (world->pw_lock > 0);
	if (world->pw_lock == 0)
	{
		world->pw_lock = threadID();
		return world->pw_lock;
	}
	return -1;
}

extern inline a3ret a3physicsWorldUnlock(a3_PhysicsWorld *world)
{
	// release lock if caller is owner
	const a3ret ret = (a3ret)world->pw_lock;
	if (ret == threadID())
	{
		world->pw_lock = 0;
		return ret;
	}
	return -1;
}


//-----------------------------------------------------------------------------
