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
	
	a3_Ray.c
	Ray casting and picking implementations.
*/

#include "a3_Ray.h"


//-----------------------------------------------------------------------------
// internal utilities

inline void a3rayHitReset_internal(a3_RayHit *hit_out, const a3_Ray *ray)
{
	hit_out->hit0 = hit_out->hit1 = ray->origin;
	hit_out->param0 = hit_out->param1 = a3realZero;
	hit_out->hitFlag = 0;
}


//-----------------------------------------------------------------------------
// internal casting algorithms for efficiency

// 3D point vs sphere check (also works for circles)
inline a3i32 a3pointTestSphere_internal(const a3real3p point, const a3real3p sphereCenter, const a3real sphereRadiusSq, a3real3p diff_tmp)
{
	// result = |point - center| <= radius
	// result = |point - center|^2 <= radius^2
	a3real3Diff(diff_tmp, point, sphereCenter);
	return (a3real3LengthSquared(diff_tmp) <= sphereRadiusSq);
}


//-----------------------------------------------------------------------------

// ****TO-DO: 
// plane
inline a3i32 a3rayTestPlane_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p planeCenter, const a3real3p planeNormal, a3real3p diff_tmp)
{
	// resource: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
	// take dot product of ray direction and normal
	// if they are perpendicular (zero), no intersection
	
	return 0;
}

// ****TO-DO: 
// finite plane
inline a3i32 a3rayTestPlaneFinite_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p planeCenter, const a3real3p planeTangent, const a3real3p planeBitangent, const a3real3p planeNormal, const a3real planeHalfWidthSq, const a3real planeHalfHeightSq, a3real3p diff_tmp)
{
	// first test infinite plane
	// if hit, perform additional calculations to determine if hit is on plane
	if (a3rayTestPlane_internal(hit_out, rayOrigin, rayDirection, planeCenter, planeNormal, diff_tmp))
	{
		// logic: 
		//	- we have a point on the plane; can project onto tangent and bitangent to get sq length of that
		//	- compare square length with projected with respective dimension squared
		//	- if both pass, we are within the plane
	
	}
	return 0;
}

// ****TO-DO: 
// disc
inline a3i32 a3rayTestDisc_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p discCenter, const a3real3p discNormal, const a3real discRadiusSq, a3real3p diff_tmp)
{
	// resource: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
	// first test against disc's plane
	if (a3rayTestPlane_internal(hit_out, rayOrigin, rayDirection, discCenter, discNormal, diff_tmp))
	{
		// if hit point collides with circle, test passes
	
	}
	return 0;
}

// ****TO-DO: 
// sphere
inline a3i32 a3rayTestSphere_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p sphereCenter, const a3real sphereRadiusSq, a3real3p diff_tmp)
{
	// ray vs sphere test: 
	// good resource: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	// good resource: http://antongerdelan.net/opengl/raycasting.html
	//	- calculate difference from ray origin to sphere center: L
	//	- project difference vector onto ray direction vector (unit)
	//		- shortcut: if dot product is negative, ray originates 
	//			within or ahead of sphere; test fails: d = L dot D
	//			(if the ray direction vector is unit length, the dot 
	//			product represents the length of the projected vector)
	//	- calculate distance from center of sphere to projected point: h
	//		- Pythagorean theorem:	d^2 + h^2 = L^2
	//								h^2 = L^2 - d^2
	//	- check if intersection occurred: 
	//		- Pythagorean again:	h^2 + b^2 = r^2
	//								b^2 = r^2 - h^2

	return 0;
}

// ****TO-DO: 
// infinite cylinder
inline a3i32 a3rayTestCylinder_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p cylinderCenter, const a3real3p cylinderAxis, const a3real cylinderRadiusSq, const a3real cylinderAxisLengthInvSq, a3real3p diff_tmp)
{
	// ray vs infinite cylinder test: 
	// resource: https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
	// resource: http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf
	// 1. Ray vs infinite cylinder: 
	//	Point on the surface of a cylinder can be represented as: 
	//		|Q - Q0 - dot(Q - Q0, R)R|^2 - r^2 = 0
	//		|dQ - dot(dQ, R)R|^2 - r^2 = 0
	//	where
	//		dQ is the vector from cylinder center to point
	//		Q is the point
	//		Q0 is the 'center' or origin of the cylinder
	//		R is the axis of the cylinder
	//		r is the radius of the cylinder
	//	Point along a ray is
	//		P = P0 + Dt
	//	where
	//		P is the point
	//		P0 is the ray origin
	//		D is the ray direction
	//		t is the ray parameter
	//	Substitute the 'P' into the cylinder equation for 'Q': 
	//		|P - Q0 - dot(P - Q0, R)R|^2 - r^2 = 0
	//		|P0 + Dt - Q0 - dot(P0 + DT - Q0, R)R|^2 - r^2 = 0
	//	which reduces to a quadratic: 
	//		At^2 + Bt + C = 0
	//		A = |a|^2
	//		B = 2 dot(a, b)
	//		C = |b|^2 - r^2
	//	where
	//		a = D - dot(D, R)R
	//		b = d0 - dot(d0, R)R
	//		d0 = P0 - Q0
	//	Solve for 't' using quadratic equation
	//		descriminant = B^2 - 4AC
	//			if (descrim > 0), solutions exist
	//				t = [-B +/- sqrt(descrim)] / 2A
	// 2. Ray vs finite with caps: 
	//	Test against caps (discs)
	//	If collision is not on caps, check against body

	// here we go...
	
	return 0;
}

// ****TO-DO: 
// finite cylinder
inline a3i32 a3rayTestCylinderFinite_internal(a3_RayHit *hit_out, const a3real4p rayOrigin, const a3real4p rayDirection, const a3real3p cylinderCenter, const a3real3p cylinderAxis, const a3real cylinderRadiusSq, const a3real cylinderAxisLengthInvSq, const a3real cylinderLength, a3real3p diff_tmp)
{
	if (a3rayTestCylinder_internal(hit_out, rayOrigin, rayDirection, cylinderCenter, cylinderAxis, cylinderRadiusSq, cylinderAxisLengthInvSq, diff_tmp))
	{

	}
	return 0;
}

// ****TO-DO: 
// axis-aligned box
inline a3i32 a3rayTestAABB_internal(a3_RayHit *hit_out, const a3real3p rayOrigin, const a3real3p rayDirection, const a3real xmin, const a3real ymin, const a3real zmin, const a3real xmax, const a3real ymax, const a3real zmax)
{
	// help: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

	// bounds, assumes centered
	const a3vec3 bounds[2] = {
		{ xmin, ymin, zmin },
		{ xmax, ymax, zmax },
	};

	// ray params
//	a3real tmin, tmax, tcmin, tcmax;

	// copy of ray, inverse direction and signs
//	a3i32 sign_x, sign_y, sign_z;

	return 0;
}


//-----------------------------------------------------------------------------

// create ray given start and end points
extern inline a3i32 a3rayCreateLine(a3_Ray *ray_out, const a3vec3 origin, const a3vec3 end)
{
	if (ray_out)
	{
		// calculate difference and use that to create a proper ray
		a3vec3 direction;
		a3real3Diff(direction.v, end.v, origin.v);
		return a3rayCreate(ray_out, origin, direction);
	}
	return 0;
}

// create ray given origin and direction (will be normalized)
extern inline a3i32 a3rayCreate(a3_Ray *ray_out, const a3vec3 origin, const a3vec3 direction)
{
	if (ray_out)
	{
		// set origin
		ray_out->origin.xyz = origin;
		ray_out->origin.w = a3realOne;

		// set direction
		a3real3GetUnit(ray_out->direction.v, direction.v);
		ray_out->direction.w = a3realZero;

		// done
		return 1;
	}
	return 0;
}

// transform a ray
extern inline a3i32 a3rayTransform(a3_Ray *ray_out, const a3_Ray *ray, const a3real4x4p transform)
{
	if (ray_out && ray)
	{
		a3real4Real4x4Product(ray_out->origin.v, transform, ray->origin.v);
		a3real4Real4x4Product(ray_out->direction.v, transform, ray->direction.v);
		return 1;
	}
	return 0;
}

// create ray given NDC coordinate and an inverse projection matrix
extern inline a3i32 a3rayCreateUnprojected(a3_Ray *ray_out, const a3vec3 v_ndc, const a3real4x4p invProj)
{
	if (ray_out)
	{
		// set origin at zero vector
		ray_out->origin = a3wVec4;

		// calculate direction
		//	(inverse projection method: reverse perspective divide)
		ray_out->direction.xyz = v_ndc;
		ray_out->direction.w = a3realOne;
		a3real4Real4x4Mul(invProj, ray_out->direction.v);
		a3real3DivS(ray_out->direction.v, ray_out->direction.w);
		a3real3Normalize(ray_out->direction.v);
		ray_out->direction.w = a3realZero;

		// done
		return 1;
	}
	return 0;
}

// reset ray hit to ray origin
extern inline a3i32 a3rayHitReset(a3_RayHit *hit_out, const a3_Ray *ray)
{
	if (hit_out && ray)
	{
		a3rayHitReset_internal(hit_out, ray);

		// done
		return 1;
	}
	return 0;
}

// validate hit: lower flag if near distance is negative
extern inline a3i32 a3rayHitValidate(a3_RayHit *hit)
{
	if (hit)
	{
		if (hit->hitFlag && hit->param0 < a3realZero)
			hit->hitFlag = 0;
		return hit->hitFlag;
	}
	return 0;
}


//-----------------------------------------------------------------------------

// pick against infinite plane
extern inline a3i32 a3rayTestPlane(a3_RayHit *hit_out, const a3_Ray *ray, const a3_Axis normalAxis, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *normal = transform[normalAxis];
		const a3real *center = transform[3];
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestPlane_internal(hit_out, ray->origin.v, ray->direction.v, center, normal, diff_tmp);
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against finite plane
extern inline a3i32 a3rayTestPlaneFinite(a3_RayHit *hit_out, const a3_Ray *ray, const a3_Axis normalAxis, const a3real width, const a3real height, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *normal = transform[normalAxis];
		const a3real *center = transform[3];
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		if (width > a3realZero && height > a3realZero)
		{
			const a3real *tangent = transform[(normalAxis + 1) % 3];
			const a3real *bitangent = transform[(normalAxis + 2) % 3];
			const a3real halfWidthSq = (width * width) * a3realQuarter;
			const a3real halfWeightSq = (height * height) * a3realQuarter;
			hit_out->hitFlag = a3rayTestPlaneFinite_internal(hit_out, ray->origin.v, ray->direction.v, center, tangent, bitangent, normal, halfWidthSq, halfWeightSq, diff_tmp);
		}
		else
		{
			hit_out->hitFlag = a3rayTestPlane_internal(hit_out, ray->origin.v, ray->direction.v, center, normal, diff_tmp);
		}
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against disc
extern inline a3i32 a3rayTestDisc(a3_RayHit *hit_out, const a3_Ray *ray, const a3_Axis normalAxis, const a3real radius, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *normal = transform[normalAxis];
		const a3real *center = transform[3];
		const a3real radiusSq = radius * radius;
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestDisc_internal(hit_out, ray->origin.v, ray->direction.v, center, normal, radiusSq, diff_tmp);
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against sphere
extern inline a3i32 a3rayTestSphere(a3_RayHit *hit_out, const a3_Ray *ray, const a3real radius, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *center = transform[3];
		const a3real radiusSq = radius * radius;
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestSphere_internal(hit_out, ray->origin.v, ray->direction.v, center, radiusSq, diff_tmp);
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against infinite cylinder
extern inline a3i32 a3rayTestCylinder(a3_RayHit *hit_out, const a3_Ray *ray, const a3_Axis normalAxis, const a3real radius, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *bodyDirection = transform[normalAxis];
		const a3real *center = transform[3];
		const a3real radiusSq = radius * radius;
		const a3real bodyLenInvSq = a3real3LengthSquaredInverse(bodyDirection);
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestCylinder_internal(hit_out, ray->origin.v, ray->direction.v, center, bodyDirection, radiusSq, bodyLenInvSq, diff_tmp);
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against finite cylinder
extern inline a3i32 a3rayTestCylinderFinite(a3_RayHit *hit_out, const a3_Ray *ray, const a3_Axis normalAxis, const a3real radius, const a3real length, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		const a3real *bodyDirection = transform[normalAxis];
		const a3real *center = transform[3];
		const a3real radiusSq = radius * radius;
		const a3real bodyLenInvSq = a3real3LengthSquaredInverse(bodyDirection);
		a3real3 diff_tmp;

		a3rayHitReset_internal(hit_out, ray);
		if (length > a3realZero)
		{
			hit_out->hitFlag = a3rayTestCylinderFinite_internal(hit_out, ray->origin.v, ray->direction.v, center, bodyDirection, radiusSq, bodyLenInvSq, length, diff_tmp);
		}
		else
		{
			hit_out->hitFlag = a3rayTestCylinder_internal(hit_out, ray->origin.v, ray->direction.v, center, bodyDirection, radiusSq, bodyLenInvSq, diff_tmp);
		}
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against axis-aligned box
extern inline a3i32 a3rayTestAxisAlignedBox(a3_RayHit *hit_out, const a3_Ray *ray, const a3real width, const a3real height, const a3real depth, const a3real4x4p transform)
{
	if (hit_out && ray)
	{
		// half dimensions
		const a3real halfWidth = a3realHalf * width;
		const a3real halfHeight = a3realHalf * height;
		const a3real halfDepth = a3realHalf * depth;

		// perform AABB test
		const a3real *center = transform[3];
		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestAABB_internal(hit_out, ray->origin.v, ray->direction.v, center[0] - halfWidth, center[1] - halfHeight, center[2] - halfDepth, center[0] + halfWidth, center[1] + halfHeight, center[2] + halfDepth);
		return hit_out->hitFlag;
	}
	return 0;
}

// pick against bounding box
extern inline a3i32 a3rayTestBoundingBox(a3_RayHit *hit_out, const a3_Ray *ray, const a3real width, const a3real height, const a3real depth, const a3real4x4p transform, const a3real4x4p transformInv)
{
	if (hit_out && ray)
	{
		// half dimensions
		const a3real halfWidth = a3realHalf * width;
		const a3real halfHeight = a3realHalf * height;
		const a3real halfDepth = a3realHalf * depth;

		// move to local space and do test
		a3_Ray rayLocal[1];
		a3rayTransform(rayLocal, ray, transformInv);
		a3rayHitReset_internal(hit_out, ray);
		hit_out->hitFlag = a3rayTestAABB_internal(hit_out, rayLocal->origin.v, rayLocal->direction.v, -halfWidth, -halfHeight, -halfDepth, +halfWidth, +halfHeight, +halfDepth);
		if (hit_out->hitFlag)
		{
			// set hit points in original space
			a3real3ProductS(hit_out->hit0.v, ray->direction.v, hit_out->param0);
			a3real3ProductS(hit_out->hit1.v, ray->direction.v, hit_out->param1);
			a3real3Add(hit_out->hit0.v, ray->origin.v);
			a3real3Add(hit_out->hit1.v, ray->origin.v);
		}
		return hit_out->hitFlag;
	}
	return 0;
}


//-----------------------------------------------------------------------------
