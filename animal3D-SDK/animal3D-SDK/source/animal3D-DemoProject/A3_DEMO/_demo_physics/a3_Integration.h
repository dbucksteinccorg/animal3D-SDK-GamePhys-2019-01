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
	
	a3_Integration.h
	Utility for handling complex general integration algorithms.
*/

#ifndef __ANIMAL3D_INTEGRATION_H
#define __ANIMAL3D_INTEGRATION_H


//-----------------------------------------------------------------------------

// math library
#include "animal3D-A3DM/animal3D-A3DM.h"


//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
	typedef struct a3_Function		a3_Function;
#endif	// __cplusplus
	
	
//-----------------------------------------------------------------------------

	struct a3_Function;

	// typedefs for functions: 
	//	general vector integrator
	typedef a3ret(*a3vectorIntegrateFunc)(const a3_Function *func, const a3real dt);

	//	general vector derivative calculator
	typedef a3real *(*a3vectorDifferentiateFunc)(a3real *derivative_result, const a3real *value, const a3_Function *func, const a3real dt);


//-----------------------------------------------------------------------------

	// function
	// this is a "controller" for any mathematical function of time
	//	e.g. position, velocity...
	// utility to integrate based on a given step size
	struct a3_Function
	{
		// ****TO-DO: 
		//	(1) add value, derivative function and integrator
		//	(2) add other utilities
		
		
		// 2: valid flag
		a3boolean valid;
	};


//-----------------------------------------------------------------------------

	// integration evaluators and helpers

	// initialize function
	a3i32 a3functionInitialize(a3_Function *func, const a3_Function *derivative, a3real *value, a3vectorIntegrateFunc integrateFunc, a3vectorDifferentiateFunc differentiateFunc);

	// check if function has everything
	inline a3i32 a3functionIsValid(a3_Function *func);

	// call integrator
	inline a3i32 a3functionIntegrate(const a3_Function *func, const a3real dt);


	// ****TO-DO: 
	//	- implement some basic example integration methods
	//	- implement utilities to help with more advanced methods


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__ANIMAL3D_INTEGRATION_H