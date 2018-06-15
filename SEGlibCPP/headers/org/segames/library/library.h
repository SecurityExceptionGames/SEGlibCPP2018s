#pragma once

// Compiler macros:
//	SEG_API_DLL						Enables the dll features of the API, dll-import as standard
//	SEG_API_DLL_EXPORT				Sets the dll to export
//	SEG_API_DEBUG					Enables all debug macros
//	SEG_API_DEBUG_THROW				Enables throwing of debug exception, eg. index out of bounds
//	SEG_API_MEMORY_HANDLING_STRICT	Enforces stricter memory handling, eg. no memory blocks of void
//	SEG_API_ARRAY_LIST_CAPACITY		Standard start capacity of org::segames::library::util::ArrayList, standard value is 32

#ifdef SEG_API_DEBUG //Enables all debug macros
#ifndef SEG_API_DEBUG_THROW
#define SEG_API_DEBUG_THROW
#endif
#endif

#ifndef ZERO
#define ZERO 0						//The number zero
#endif

#ifndef PI
#define PI 3.141592653589793238L	//PI
#endif