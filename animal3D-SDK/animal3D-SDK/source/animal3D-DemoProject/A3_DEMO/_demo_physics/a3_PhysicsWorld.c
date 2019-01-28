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
//	a3ui32 i;

	// hard-set random seed for predictability (i.e. scenario replication)
	a3randomSetSeed(0);


	// reset all physics objects


	// reset state
	a3physicsWorldStateReset(world->pw_state);

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

// ****TO-DO: 
// internal physics world thread function
a3ret a3physicsThread_internal(a3_PhysicsWorld *world)
{
	// desired physics update rate (updates per second)
	const a3f64 rate = 100.0;

	// pointer to timer for convenience
	a3_Timer *timerPtr = world->pw_timer;

	// second counter for physics (debugging)
	a3ui32 currSecond = 0, prevSecond = 0;


	return 0;
}


//-----------------------------------------------------------------------------

// physics simulation step
a3ret a3physicsWorldUpdate(a3_PhysicsWorld *world, a3f64 dt)
{
	// copy of state to edit before committing writing to world
	a3_PhysicsWorldState state_copy[1] = { *world->pw_state };

	// time as real
	const a3real t_r = (a3real)(world->pw_timer->totalTime);
	const a3real dt_r = (a3real)(dt);

	// generic counter
//	a3ui32 i;


	// update physics objects


	// ****TO-DO: 
	// update state
//	const a3real t_clamp = ???


	// ****TO-DO: 
	// write operation is locked


	// done
	return 0;
}


//-----------------------------------------------------------------------------

// reset world state
a3ret a3physicsWorldStateReset(a3_PhysicsWorldState *worldState)
{
	// generic counter
//	a3ui32 i;

	if (worldState)
	{
		// ****TO-DO: 
		// reset all state data appropriately

	}
	return -1;
}


//-----------------------------------------------------------------------------

// threaded physics simulation
extern inline void a3physicsWorldThreadInit(a3_PhysicsWorld *world)
{
	// ****TO-DO: 
	// reset flags then launch new thread for this world; 
	//	wait for world and thread to initialize before continuing

}

extern inline void a3physicsWorldThreadTerm(a3_PhysicsWorld *world)
{
	// ****TO-DO: 
	// terminate physics world by acquiring lock then invalidating it; 
	//	wait for world and thread to terminate before continuing

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
	// ****TO-DO: 
	// wait for lock to be released, then set it

	return -1;
}

extern inline a3ret a3physicsWorldUnlock(a3_PhysicsWorld *world)
{
	// ****TO-DO: 
	// release lock if caller is owner

	return -1;
}


//-----------------------------------------------------------------------------
