//*****************************************************************************
/*!
	Copyright 2013 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*

#ifndef CABCOPROPERTYFACTORY_H
#define CABCOPROPERTYFACTORY_H

#include "IAbcFramework.h"
#include "IAbcInput.h"

class CAbcIPropertyFactory
{
public:
	static EAbcResult WrapIGeomParam( 
		IAbcIGeomParam** out_ppGeomParam, 
		IAbcIPropertyAccessor* in_pProp
		);
};


#endif