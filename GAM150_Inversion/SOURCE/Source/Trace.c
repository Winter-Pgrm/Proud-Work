//------------------------------------------------------------------------------
//
// File Name:	Trace.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Trace.h"
#include <stdarg.h>
#define MAXLENGTH 1000;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.
static FILE * traceFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
void TraceInit()
{
	// TODO: Open "trace.log" for writing (text mode).
	
	
	fopen_s(&traceFile,"trace.log", "wt");
	
	
}

// Output a message to the Tracing/Logging file.
void TraceMessage(const char * message)
{
	UNREFERENCED_PARAMETER(message);
	if (traceFile)
	{
		va_list arg_ptr;
		va_start(arg_ptr, message);
		vfprintf_s(traceFile, message, arg_ptr);
		fprintf_s(traceFile, "\n");
		va_end(arg_ptr);

	}

	// TODO: Write the message to the Tracing/Logging file.

	// TODO: Also print the message to the console window.
}

// Shutdown the Tracing/Logging module.
void TraceShutdown()
{
	if (traceFile)
	{
		fclose(traceFile);
		printf("File is closed!");
	}
	// TODO: Close "trace.log" if it has been opened successfully.
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

