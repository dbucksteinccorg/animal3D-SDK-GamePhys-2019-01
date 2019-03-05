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
	
	a3_Collision.c
	Collision detection and response algorithm implementations.
*/


#include "a3_Collision.h"


//-----------------------------------------------------------------------------

// internal utility to reset property list for hull
inline void a3collisionResetHull_internal(a3_ConvexHull *hull_out)
{
	// reset pointers
	hull_out->transform = hull_out->transformInv = 0;

	// reset flags etc.
	hull_out->type = a3hullType_none;
	hull_out->flag = a3hullFlag_none;
	hull_out->normalAxis = a3axis_x;

	// reset properties
	hull_out->width = hull_out->height = hull_out->depth = a3realZero;
	hull_out->halfWidth = hull_out->halfHeight = hull_out->halfDepth = a3realZero;
	hull_out->halfWidthSq = hull_out->halfHeightSq = hull_out->halfDepthSq = a3realZero;
}


//-----------------------------------------------------------------------------
// internal collision tests
//	- there are many more, but these will do for now

inline a3i32 a3collisionTestPointSphere_internal(
	const a3real3p pointPosition, const a3real3p sphereCenter, const a3real sphereRadiusSq, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestPointAABB_internal(
	const a3real3p pointPosition_localToAABB, const a3real3p aabbMinExtents, const a3real3p aabbMaxExtents)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestPlaneSphere_internal(
	const a3real3p planeCenter, const a3real3p planeTangent, const a3real3p planeBitangent, const a3real3p planeNormal, const a3real planeHalfWidth, const a3real planeHalfHeight, const a3real3p sphereCenter, const a3real sphereRadius, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestPlaneAABB_internal(
	const a3real3p planeCenter_localToAABB, const a3real3p planeTangent_localToAABB, const a3real3p planeBitangent_localToAABB, const a3real3p planeNormal_localToAABB, const a3real planeHalfWidth, const a3real planeHalfHeight, const a3real3p aabbMinExtents, const a3real3p aabbMaxExtents, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestSpheres_internal(
	const a3real3p sphereCenter_a, const a3real sphereRadius_a, const a3real3p sphereCenter_b, const a3real sphereRadius_b, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestSphereAABB_internal(
	const a3real3p sphereCenter_localToAABB, const a3real sphereRadius, const a3real3p aabbMinExtents, const a3real3p aabbMaxExtents, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}

inline a3i32 a3collisionTestAABBs_internal(
	const a3real3p aabbMinExtents_a, const a3real3p aabbMaxExtents_a, const a3real3p aabbMinExtents_b, const a3real3p aabbMaxExtents_b, a3real3p diff_tmp)
{
	// ****TO-DO: 
	//	- implement test

	return 0;
}


//-----------------------------------------------------------------------------

// create point hull
extern inline a3i32 a3collisionHullCreatePoint(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_point;

		// done
		return hull_out->type;
	}
	return -1;
}

// create plane hull
extern inline a3i32 a3collisionHullCreatePlane(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real width, const a3real height, const a3boolean isAxisAligned, const a3_Axis normalAxis)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_plane;
		hull_out->flag = (isAxisAligned ? a3hullFlag_isAxisAligned : 0);
		hull_out->normalAxis = normalAxis;
		hull_out->width = width;
		hull_out->height = height;
		hull_out->halfWidth = width * a3realHalf;
		hull_out->halfHeight = height * a3realHalf;
		hull_out->halfWidthSq = width * width * a3realQuarter;
		hull_out->halfHeightSq = height * height * a3realQuarter;

		// done
		return hull_out->type;
	}
	return -1;
}

// create disc hull
extern inline a3i32 a3collisionHullCreateDisc(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius, const a3boolean isAxisAligned, const a3_Axis normalAxis)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_disc;
		hull_out->flag = (isAxisAligned ? a3hullFlag_isAxisAligned : 0);
		hull_out->normalAxis = normalAxis;
		hull_out->radius = radius;
		hull_out->radiusSq = radius * radius;

		// done
		return hull_out->type;
	}
	return -1;
}

// create box hull
extern inline a3i32 a3collisionHullCreateBox(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real width, const a3real height, const a3real depth, const a3boolean isAxisAligned)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_box;
		hull_out->flag = a3hullFlag_is3D | (isAxisAligned ? a3hullFlag_isAxisAligned : 0);
		hull_out->width = width;
		hull_out->height = height;
		hull_out->depth = depth;
		hull_out->halfWidth = width * a3realHalf;
		hull_out->halfHeight = height * a3realHalf;
		hull_out->halfDepth = depth * a3realHalf;
		hull_out->halfWidthSq = width * width * a3realQuarter;
		hull_out->halfHeightSq = height * height * a3realQuarter;
		hull_out->halfDepthSq = depth * depth * a3realQuarter;

		// done
		return hull_out->type;
	}
	return -1;
}

// create sphere hull
extern inline a3i32 a3collisionHullCreateSphere(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_sphere;
		hull_out->flag = a3hullFlag_is3D;
		hull_out->radius = radius;
		hull_out->radiusSq = radius * radius;

		// done
		return hull_out->type;
	}
	return -1;
}

// create cylinder hull
extern inline a3i32 a3collisionHullCreateCylinder(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius, const a3real length, const a3_Axis normalAxis)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_cylinder;
		hull_out->flag = a3hullFlag_is3D;
		hull_out->normalAxis = normalAxis;
		hull_out->radius = radius;
		hull_out->radiusSq = radius * radius;
		hull_out->length = length;
		hull_out->halfLength = length * a3realHalf;

		// done
		return hull_out->type;
	}
	return -1;
}

// create mesh hull
extern inline a3i32 a3collisionHullCreateMesh(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const void *points, const a3ui32 pointCount, const a3boolean is3D)
{
	if (hull_out && transform && transformInv)
	{
		a3collisionResetHull_internal(hull_out);

		// ****TO-DO: 
		// set properties
		hull_out->transform = transform;
		hull_out->transformInv = transformInv;
		hull_out->type = a3hullType_mesh;


		// done
		return hull_out->type;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// high-level collision test
extern inline a3i32 a3collisionTestConvexHulls(a3_ConvexHullCollision *collision_out, const a3_ConvexHull *hull_a, const a3_ConvexHull *hull_b)
{
	if (collision_out && hull_a && hull_b)
	{
		// ****TO-DO: 
		//	- select appropriate internal test
		//	- do necessary preparations for selected test (e.g. transformations)
		//	- do multiple tests if necessary (e.g. two arbitrary boxes)
		a3i32 status = 0;

		// call test and get final status

		if (status)
		{
			// store resolution data
		}
		return status;
	}
	return -1;
}


//-----------------------------------------------------------------------------
