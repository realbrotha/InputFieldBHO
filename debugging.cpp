#include "StdAfx.h"

#include <stdio.h>
#include <tchar.h>
#include "dv.h"

void dv(char *fmt, ...) 
{ 
	char msg[512] = {0}; 
	
	va_list vargs; 
	va_start( vargs, fmt ); 
	_vsntprintf( msg + strlen(msg), sizeof(msg), fmt, vargs ); 
	va_end( vargs ); 
	
	OutputDebugString(msg); 

} 
