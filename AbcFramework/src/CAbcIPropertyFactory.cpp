//*****************************************************************************
/*!
	Copyright 2013 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*

#include "AbcFrameworkUtil.h"
#include "CAbcDataTypeHelper.h"
#include "CAbcIPropertyFactory.h"
#include "CAbcIPropertyAccessor.h"

EAbcResult CAbcIPropertyFactory::WrapIGeomParam( IAbcIGeomParam** out_ppGeomParam, IAbcIPropertyAccessor* in_pProp )
{
	if (out_ppGeomParam == NULL || in_pProp == NULL)
		return EResult_InvalidPtr;

	IAbcIGeomParam* l_pGeomParam = NULL;
	
	CAbcPtr<CAbcICompoundPropertyAccessor> l_spParentCompound;
	in_pProp->GetParentProperty( (IAbcIPropertyAccessor**)&l_spParentCompound );


#define CASE_WRAP_GEOMPARAM( ETYPE, TRAITS ) case ETYPE: l_pGeomParam = new CAbcIGeomParamImpl< TRAITS >( l_spParentCompound->GetInternal().getPtr(), in_pProp->GetName() );	break

	EAbcDataTraits traits = EDataTraits_Unknown;

	if ( in_pProp->GetPropertyType() == EPropertyType_Compound )
	{
		CAbcPtr<CAbcICompoundPropertyAccessor> l_spCompound = static_cast<CAbcICompoundPropertyAccessor*>(in_pProp);
		CAbcPtr<IAbcIPropertyAccessor> l_spValsProp;
		l_spCompound->GetChildProperty( ".vals", (IAbcIPropertyAccessor**)&l_spValsProp );

		if ( l_spValsProp != NULL )
		{
			traits = l_spValsProp->GetDataType().m_eTraits;
		}
	}
	else if ( in_pProp->GetPropertyType() == EPropertyType_Array )
	{
		traits = in_pProp->GetDataType().m_eTraits;
	}

	switch ( traits )
	{
		CASE_WRAP_GEOMPARAM( EDataTraits_Bool, Alembic::Abc::BooleanTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_UInt8, Alembic::Abc::Uint8TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Int8, Alembic::Abc::Int8TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_UInt16, Alembic::Abc::Uint16TPTraits);
		CASE_WRAP_GEOMPARAM( EDataTraits_Int16, Alembic::Abc::Int16TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_UInt32, Alembic::Abc::Uint32TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Int32, Alembic::Abc::Int32TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_UInt64, Alembic::Abc::Uint64TPTraits);
		CASE_WRAP_GEOMPARAM( EDataTraits_Int64, Alembic::Abc::Int64TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Float16, Alembic::Abc::Float16TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Float32, Alembic::Abc::Float32TPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Float64, Alembic::Abc::Float64TPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_StringPtr, Alembic::Abc::StringTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_WStringPtr, Alembic::Abc::WstringTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_V2s , Alembic::Abc::V2sTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V2i , Alembic::Abc::V2iTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V2f , Alembic::Abc::V2fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V2d , Alembic::Abc::V2dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_V3s , Alembic::Abc::V3sTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V3i , Alembic::Abc::V3iTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V3f , Alembic::Abc::V3fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_V3d , Alembic::Abc::V3dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_P2s, Alembic::Abc::P2sTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_P2i, Alembic::Abc::P2iTPTraits );  
		CASE_WRAP_GEOMPARAM( EDataTraits_P2f, Alembic::Abc::P2fTPTraits );  
		CASE_WRAP_GEOMPARAM( EDataTraits_P2d, Alembic::Abc::P2dTPTraits );  

		CASE_WRAP_GEOMPARAM( EDataTraits_P3s, Alembic::Abc::P3sTPTraits );  
		CASE_WRAP_GEOMPARAM( EDataTraits_P3i, Alembic::Abc::P3iTPTraits );  
		CASE_WRAP_GEOMPARAM( EDataTraits_P3f, Alembic::Abc::P3fTPTraits );  
		CASE_WRAP_GEOMPARAM( EDataTraits_P3d, Alembic::Abc::P3dTPTraits );  

		CASE_WRAP_GEOMPARAM( EDataTraits_Box2s, Alembic::Abc::Box2sTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box2i, Alembic::Abc::Box2iTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box2f, Alembic::Abc::Box2fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box2d, Alembic::Abc::Box2dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_Box3s, Alembic::Abc::Box3sTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box3i, Alembic::Abc::Box3iTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box3f, Alembic::Abc::Box3fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Box3d, Alembic::Abc::Box3dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_M33f, Alembic::Abc::M33fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_M33d, Alembic::Abc::M33dTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_M44f, Alembic::Abc::M44fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_M44d, Alembic::Abc::M44dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_Quatf, Alembic::Abc::QuatfTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Quatd, Alembic::Abc::QuatdTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_C3h , Alembic::Abc::C3hTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_C3f , Alembic::Abc::C3fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_C3c , Alembic::Abc::C3cTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_C4h , Alembic::Abc::C4hTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_C4f , Alembic::Abc::C4fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_C4c , Alembic::Abc::C4cTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_N2f, Alembic::Abc::N2fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_N2d , Alembic::Abc::N2dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_N3f, Alembic::Abc::N3fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_N3d , Alembic::Abc::N3dTPTraits );

		CASE_WRAP_GEOMPARAM( EDataTraits_V4f , AbcFramework::V4fTPTraits );
		CASE_WRAP_GEOMPARAM( EDataTraits_Rotf, AbcFramework::VRotationfTraits );
	}

#undef CASE_WRAP_GEOMPARAM

	if ( l_pGeomParam )
	{
		l_pGeomParam->AddRef();
		*out_ppGeomParam = l_pGeomParam;

		return EResult_Success;
	}

	return EResult_Fail;
}

