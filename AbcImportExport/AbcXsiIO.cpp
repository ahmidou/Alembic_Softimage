//*****************************************************************************
/*!
	Copyright 2013 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*

#include "AbcXsiIO.h"
#include <xsi_application.h>
using namespace XSI;

IAbcFramework* GetFrameworkInterface()
{
  IAbcFramework* l_pInterface = CAbcFramework::GetInstance();
  return l_pInterface;
}

AbcXsiIO::AbcXsiIO()
{
    CAbcFramework::Init();
		m_spIFramework = GetFrameworkInterface();
		if ( !m_spIFramework )
			Application().LogMessage( L"Unable to get an Alembic Framework Interface", siErrorMsg );
}

AbcXsiIO::~AbcXsiIO()
{
	// Be sure to release first before unloading the DLL
	if ( m_spIFramework )
		m_spIFramework = NULL;
  CAbcFramework::Destroy();
}
