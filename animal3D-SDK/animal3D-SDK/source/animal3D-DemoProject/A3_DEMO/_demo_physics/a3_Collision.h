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
	
	a3_Collision.h
	Collision detection and response algorithms.
*/

#ifndef __ANIMAL3D_COLLISION_H
#define __ANIMAL3D_COLLISION_H


// math library
#include "animal3D-A3DM/animal3D-A3DM.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_ConvexHull			a3_ConvexHull;
	typedef struct a3_ConvexHullCollision	a3_ConvexHullCollision;
	typedef enum a3_Axis					a3_Axis;
	typedef enum a3_ConvexHullType			a3_ConvexHullType;
	typedef enum a3_ConvexHullFlag			a3_ConvexHullFlag;
	typedef enum a3_ConvexHullProperty		a3_ConvexHullProperty;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// axis
	enum a3_Axis
	{
		a3axis_x,	// index 0 in a matrix
		a3axis_y,	// index 1 in a matrix
		a3axis_z,	// index 2 in a matrix
	};

	// constants
	enum a3_ConvexHullLimits
	{
		a3hullProperty_maxCount_preset = 16,
		a3hullProperty_maxCount_user = 0,

	//	a3hullContact_maxCount = 8,
	};

	// generic convex hull types
	enum a3_ConvexHullType
	{
		a3hullType_none,
		a3hullType_point,
		a3hullType_plane,
		a3hullType_disc,
		a3hullType_box,
		a3hullType_sphere,
		a3hullType_cylinder,
		a3hullType_mesh,
	};

	// generic convex hull flags
	enum a3_ConvexHullFlag
	{
		a3hullFlag_none,			// 0x00
		a3hullFlag_is3D,			// 0x01
		a3hullFlag_isAxisAligned,	// 0x02
	};

	// generic convex hull properties
	enum a3_ConvexHullProperty
	{
		// boxy shape properties
		a3hullProperty_width = 0,
		a3hullProperty_height,
		a3hullProperty_depth,
		a3hullProperty_halfwidth,
		a3hullProperty_halfheight,
		a3hullProperty_halfdepth,
		a3hullProperty_halfwidthSq,
		a3hullProperty_halfheightSq,
		a3hullProperty_halfdepthSq,

		// round shape properties
		a3hullProperty_radius = 0,
		a3hullProperty_length,
		a3hullProperty_radiusSq,
		a3hullProperty_halfLength,

		// user-defined properties
		a3hullProperty_user = a3hullProperty_maxCount_preset,
	};

	// generic convex hull descriptor
	struct a3_ConvexHull
	{
		// transformation and inverse pointers
		const a3mat4 *transform, *transformInv;

		// hull shape
		a3_ConvexHullType type;

		// hull shape flags
		a3_ConvexHullFlag flag;

		// fixed normal axis
		a3_Axis normalAxis;

		// hull shape properties
		union {
			a3real prop[a3hullProperty_maxCount_preset];
			struct {
				a3real width, height, depth;
				a3real halfWidth, halfHeight, halfDepth;
				a3real halfWidthSq, halfHeightSq, halfDepthSq;
			};
			struct {
				a3real radius, length;
				a3real radiusSq, halfLength;
			};
		};
	//	union {
	//		a3real prop_user[a3hullProperty_maxCount_user];
	//		struct {
	//			
	//		};
	//	};
	};

	// collision descriptor
	struct a3_ConvexHullCollision
	{
		// hulls involved
		const a3_ConvexHull *hull_a, *hull_b;
	
		// contact list for each hull
	//	a3vec3 contact_a[a3hullContact_maxCount], contact_b[a3hullContact_maxCount];

		// contact normal list for each hull
	//	a3vec3 contactNormal_a[a3hullContact_maxCount], contactNormal_b[a3hullContact_maxCount];

		// contact count for each hull
	//	a3ui32 contactCount_a, contactCount_b;
	};


//-----------------------------------------------------------------------------

	// create point hull
	inline a3i32 a3collisionHullCreatePoint(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv);

	// create plane hull
	inline a3i32 a3collisionHullCreatePlane(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real width, const a3real height, const a3boolean isAxisAligned, const a3_Axis normalAxis);

	// create disc hull
	inline a3i32 a3collisionHullCreateDisc(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius, const a3boolean isAxisAligned, const a3_Axis normalAxis);

	// create box hull
	inline a3i32 a3collisionHullCreateBox(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real width, const a3real height, const a3real depth, const a3boolean isAxisAligned);

	// create sphere hull
	inline a3i32 a3collisionHullCreateSphere(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius);

	// create cylinder hull
	inline a3i32 a3collisionHullCreateCylinder(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const a3real radius, const a3real length, const a3_Axis normalAxis);

	// create mesh hull
	inline a3i32 a3collisionHullCreateMesh(a3_ConvexHull *hull_out, const a3mat4 *transform, const a3mat4 *transformInv, const void *points, const a3ui32 pointCount, const a3boolean is3D);


//-----------------------------------------------------------------------------

	// high-level collision test
	inline a3i32 a3collisionTestConvexHulls(a3_ConvexHullCollision *collision_out, const a3_ConvexHull *hull_a, const a3_ConvexHull *hull_b);
	

//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_COLLISION_H