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
	
	a3_Ray.h
	Ray casting and picking algorithms.
*/

#ifndef __ANIMAL3D_RAY_H
#define __ANIMAL3D_RAY_H


// collision
#include "a3_Collision.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_Ray				a3_Ray;
	typedef struct a3_RayHit			a3_RayHit;
#endif	// __cplusplus

	
//-----------------------------------------------------------------------------

	// ray descriptor
	struct a3_Ray
	{
		a3vec4 origin;			// point of origin (w = 1)
		a3vec4 direction;		// direction vector (w = 0)
	};

	// ray hit descriptor
	struct a3_RayHit
	{
		a3vec4 hit0, hit1;		// near and far point of intersection
		a3real param0, param1;	// relative scales along ray
		a3boolean hitFlag;
	};


//-----------------------------------------------------------------------------

	// create ray given start and end points
	inline a3i32 a3rayCreateLine(a3_Ray *ray_out, const a3vec3 origin, const a3vec3 end);

	// create ray given origin and direction (will be normalized)
	inline a3i32 a3rayCreate(a3_Ray *ray_out, const a3vec3 origin, const a3vec3 direction);

	// transform a ray
	inline a3i32 a3rayTransform(a3_Ray *ray_out, const a3_Ray *ray, const a3real4x4p transform);

	// create ray given NDC coordinate and an inverse projection matrix
	inline a3i32 a3rayCreateUnprojected(a3_Ray *ray_out, const a3vec3 v_ndc, const a3real4x4p invProj);

	// reset ray hit to ray origin
	inline a3i32 a3rayHitReset(a3_RayHit *hit_out, const a3_Ray *ray);

	// validate hit: lower flag if near distance is negative
	inline a3i32 a3rayHitValidate(a3_RayHit *hit);


//-----------------------------------------------------------------------------

	// pick against convex hull
	inline a3i32 a3rayTestConvexHull(a3_RayHit *hit_out, const a3_Ray *ray, const a3_ConvexHull *hull);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_RAY_H