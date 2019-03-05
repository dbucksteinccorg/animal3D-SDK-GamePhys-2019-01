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

	// tmp rb pointer and values
	a3_RigidBody *currentRB;

	const a3real amplitude = (a3real)10;
	a3real param;

	// hard-set random seed for predictability (i.e. scenario replication)
	a3randomSetSeed(0);


	// reset all physics objects
	for (i = 0; i < physicsWorldMaxCount_rigidbody; ++i)
	{
		world->rb[i].index = i;
		a3particleReset(world->rb[i].motionController);
	}


	// ****TO-DO: 
	// initial values: set positions, related functions and values
	// entirely force-controlled particles do not need a full set 
	//	of initial values (e.g. can start with zero velocity)
	//	-> static masses
	//	-> local centers of mass
	//	-> local inertia tensors
	world->testRB_plane[0].motionController->position.z = -a3realTwo;
	for (i = 0, currentRB = world->testRB_sphere; i < 10; ++i, ++currentRB)
	{
		// starting positions
		param = (a3real)(i * 36);
		currentRB->motionController->position.x = amplitude * a3cosd(param);
		currentRB->motionController->position.y = amplitude * a3sind(param);

		// random rotations for every other object
		if (i % 2)
			a3quatSetEulerZYX(currentRB->motionController->rotation.q,
				a3randomSymmetric() * a3realThreeSixty,
				a3randomSymmetric() * a3realThreeSixty,
				a3randomSymmetric() * a3realThreeSixty);
	}


	// set up collision hulls and match tensors to models
	currentRB = world->testRB_plane;
	a3collisionHullCreatePlane(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		(a3real)24, (a3real)24, a3true, a3axis_z);

	currentRB = world->testRB_sphere + 0;
	a3collisionHullCreateSphere(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realOneHalf);
	a3particleSetMass(currentRB->motionController, a3realTwo);
	a3particleSetLocalInertiaTensorSphereSolid(currentRB->motionController,
		currentRB->convexHull->radius);
	
	currentRB = world->testRB_sphere + 1;
	a3collisionHullCreateSphere(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realTwo);
	a3particleSetMass(currentRB->motionController, a3realFour);
	a3particleSetLocalInertiaTensorSphereSolid(currentRB->motionController,
		currentRB->convexHull->radius);

	currentRB = world->testRB_box + 0;
	a3collisionHullCreateBox(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realOne, a3realOneHalf, a3realTwo, a3true);
	a3particleSetMass(currentRB->motionController, a3realTwo);
	a3particleSetLocalInertiaTensorBoxSolid(currentRB->motionController,
		currentRB->convexHull->width, currentRB->convexHull->height, currentRB->convexHull->depth);
	
	currentRB = world->testRB_box + 1;
	a3collisionHullCreateBox(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realOne, a3realHalf, a3realHalf, a3false);
	a3particleSetMass(currentRB->motionController, a3realFour);
	a3particleSetLocalInertiaTensorBoxSolid(currentRB->motionController,
		currentRB->convexHull->width, currentRB->convexHull->height, currentRB->convexHull->depth);
	
	currentRB = world->testRB_cylinder + 0;
	a3collisionHullCreateCylinder(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realOne, a3realFour, a3axis_x);
	a3particleSetMass(currentRB->motionController, a3realTwo);
	a3particleSetLocalInertiaTensorCylinderSolid(currentRB->motionController,
		currentRB->convexHull->radius, currentRB->convexHull->height, currentRB->convexHull->normalAxis);
	
	currentRB = world->testRB_cylinder + 1;
	a3collisionHullCreateCylinder(currentRB->convexHull,
		world->pw_state->transform_rigidbody + currentRB->index,
		world->pw_state->transformInv_rigidbody + currentRB->index,
		a3realHalf, a3realOneHalf, a3axis_x);
	a3particleSetMass(currentRB->motionController, a3realFour);
	a3particleSetLocalInertiaTensorCylinderSolid(currentRB->motionController,
		currentRB->convexHull->radius, currentRB->convexHull->height, currentRB->convexHull->normalAxis);

	currentRB = world->testRB_torus + 0;
	a3particleSetMass(currentRB->motionController, a3realZero);
	currentRB = world->testRB_torus + 1;
	a3particleSetMass(currentRB->motionController, a3realZero);
	currentRB = world->testRB_teapot + 0;
	a3particleSetMass(currentRB->motionController, a3realZero);
	currentRB = world->testRB_teapot + 1;
	a3particleSetMass(currentRB->motionController, a3realZero);


	// reset states
	a3physicsWorldStateReset(world);
	world->pw_state->count_rigidbody = 11;


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

	const a3real frequency = (a3real)15;
	const a3real amplitude = (a3real)10;
	a3real param;

	// tmp force vectors
//	a3vec3 f_gravity;
//	a3vec3 f_normal;
//	a3vec3 f_sliding;
//	a3vec3 f_friction_s;
//	a3vec3 f_friction_k;
//	a3vec3 f_drag;
//	a3vec3 f_spring;
//	a3vec3 f_damp_l;

	// tmp particle and rigidbody helpers
	a3_RigidBody *currentRB;
//	const a3vec3 springyAnchor = { 0.0f, 0.0f, 10.0f };
//	const a3vec3 slippyForce = { 0.0f, 5.0f, 0.0f };

//	a3vec3 forceAmount, forceLocation;
//	a3mat4 tmpMat;


	// ****TO-DO: 
	// update physics objects 
	//	- reset and apply forces and torques
	//	- integrate (raw position and rotation)
	//	- convert to linear (matrices)
	//	- force and torque conversions
	//	- additional tasks (e.g. clamp position)

//	// test cylinder
//	i = 1;
//	currentRB = world->testRB_ship + i;
//	a3particleResetForce(currentRB->motionController);
//	a3particleResetTorque(currentRB->motionController);
//
//	// calculate test force: touch a point on the cylinder
//	tmpMat = state_copy->transform_rigidbody[i];
//	forceAmount = tmpMat.v1.xyz;
//	forceLocation = tmpMat.v3.xyz;
//	a3real3Add(forceLocation.v, tmpMat.v0.v);
//	a3real3Sub(forceLocation.v, tmpMat.v1.v);
//	a3particleApplyForceLocation(currentRB->motionController, forceAmount.v, forceLocation.v);

	for (i = 0, currentRB = world->rb;
		i < state_copy->count_rigidbody;
		++i, ++currentRB)
	{
		a3particleIntegrateEulerKinematic(currentRB->motionController, dt_r);
		a3particleConvertForce(currentRB->motionController);
		a3particleConvertTorque(currentRB->motionController);
		a3particleUpdateCenterOfMass(currentRB->motionController, state_copy->transform_rigidbody[i].m);
		a3particleUpdateInertiaTensor(currentRB->motionController, state_copy->transform_rigidbody[i].m);
	}

	// tmp position settings
	// make alternating models orbit center of world in opposite direction
	for (i = 0, currentRB = world->testRB_sphere; i < 10; ++i, ++currentRB)
	{
		param = a3trigValid_sind((a3real)(i * 36) + t_r * frequency);
		if (i % 2) param = -param;
		currentRB->motionController->position.x = amplitude * a3cosd(param);
		currentRB->motionController->position.y = amplitude * a3sind(param);
	}


	// update state
	for (i = 0; i < state_copy->count_rigidbody; ++i)
	{
		// copy raw position and rotation
		state_copy->position_rigidbody[i] = world->rb[i].motionController->position;
		state_copy->rotation_rigidbody[i] = world->rb[i].motionController->rotation;

		// convert to matrix for collisions
		a3quatConvertToMat4Translate(
			state_copy->transform_rigidbody[i].m,
			state_copy->rotation_rigidbody[i].q, state_copy->position_rigidbody[i].v);
		a3real4x4TransformInverseIgnoreScale(
			state_copy->transformInv_rigidbody[i].m,
			state_copy->transform_rigidbody[i].m);
	}


	// write operation is locked
	if (a3physicsWorldLock(world) > 0)
	{
		// copy state to world
		*world->pw_state = *state_copy;
		a3physicsWorldUnlock(world);
	}


	// ray test
	a3physicsWorldRayTest(world);


	// done
	return 0;
}


//-----------------------------------------------------------------------------

// reset world state
a3ret a3physicsWorldStateReset(a3_PhysicsWorld *world)
{
	// generic counter
	a3ui32 i;

	if (world)
	{
		// reset all state data appropriately
		world->pw_state->count_rigidbody = 0;
		for (i = 0; i < physicsWorldMaxCount_rigidbody; ++i)
		{
			world->pw_state->position_rigidbody[i] = a3zeroVec3;
			world->pw_state->rotation_rigidbody[i] = a3identityQuat;
			world->pw_state->transform_rigidbody[i] = a3identityMat4;
			world->pw_state->transformInv_rigidbody[i] = a3identityMat4;
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

// ray test
void a3physicsWorldRayTest(a3_PhysicsWorld *world)
{
	a3ui32 i;
	a3_RayHit tmpRayHit[1];
	a3rayHitReset(world->tmpRayHit, world->tmpRay);
	world->tmpRayHit->param0 = a3realOneHundred;

	// test against each object, keep closest hit
	for (i = 0; i < world->pw_state->count_rigidbody; ++i)
		if (a3rayTestConvexHull(tmpRayHit, world->tmpRay, world->rb[i].convexHull) &&
			a3rayHitValidate(tmpRayHit) &&
			tmpRayHit->param0 <= world->tmpRayHit->param0)
			*world->tmpRayHit = *tmpRayHit;
}


//-----------------------------------------------------------------------------
