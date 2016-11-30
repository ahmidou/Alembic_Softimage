cmake_minimum_required (VERSION 2.6)

project (Softimage_Alembic)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMake/Modules  ${PROJECT_SOURCE_DIR}/../alembic/cmake/Modules)
find_package (Softimage)

message (STATUS "---configuring Softimage Alembic plugin---")

# We only need boost if including PyAlembic, or using it in the lib
IF (ALEMBIC_LIB_USES_BOOST OR USE_PYALEMBIC)
    INCLUDE("../alembic/cmake/AlembicBoost.cmake")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF()

# IlmBase
INCLUDE("../alembic/cmake/AlembicIlmBase.cmake")
INCLUDE_DIRECTORIES(${ALEMBIC_ILMBASE_INCLUDE_DIRECTORY})


# HDF5
IF (USE_HDF5)
    FIND_PACKAGE(ZLIB REQUIRED)
    SET(ALEMBIC_WITH_HDF5 "1")
    INCLUDE("../alembic/cmake/AlembicHDF5.cmake")
    INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DH5_USE_18_API")
ENDIF()

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/AbcFramework/include)
LINK_DIRECTORIES(${BOOST_LIBRARYDIR})

set (SOURCES
    AbcImportExport/AbcXsiUtils.cpp
    AbcImportExport/ExportHelper.cpp
    AbcImportExport/AbcImportExport.cpp
    AbcImportExport/AbcXsiExporter.cpp
    AbcImportExport/AbcXsiImporter.cpp
    AbcImportExport/AbcXsiIO.cpp
    AbcFramework/src/CAbcOArchive.cpp
    AbcFramework/src/CAbcOCamera.cpp
    AbcFramework/src/CAbcOFaceSet.cpp
    AbcFramework/src/CAbcOObjectFactory.cpp
    AbcFramework/src/CAbcOPoints.cpp
    AbcFramework/src/CAbcOPolyMesh.cpp
    AbcFramework/src/CAbcOProperty.cpp
    AbcFramework/src/CAbcOPropertyFactory.cpp
    AbcFramework/src/CAbcOXform.cpp
    AbcFramework/src/CAbcTimeSampling.cpp
    AbcFramework/src/CAbcUtils.cpp
    AbcFramework/src/CAbcDataTypeHelper.cpp
    AbcFramework/src/CAbcFramework.cpp
    AbcFramework/src/CAbcIArchive.cpp
    AbcFramework/src/CAbcICamera.cpp
    AbcFramework/src/CAbcIFaceSet.cpp
    AbcFramework/src/CAbcInput.cpp
    AbcFramework/src/CAbcIPoints.cpp
    AbcFramework/src/CAbcIPolyMesh.cpp
    AbcFramework/src/CAbcIPropertyAccessor.cpp
    AbcFramework/src/CAbcIPropertyFactory.cpp
    AbcFramework/src/CAbcISampleSelector.cpp
    AbcFramework/src/CAbcIXform.cpp
)

set (HEADERS
    AbcImportExport/AbcXsiImporter.h
    AbcImportExport/AbcXsiIO.h
    AbcImportExport/AbcXsiUtils.h
    AbcImportExport/ExportHelper.h
    AbcImportExport/sidictres.h
    AbcImportExport/AbcXsiExportDataTypeConverter.h
    AbcImportExport/AbcXsiExporter.h
)

add_definitions(
    -DAbcImportExport_EXPORTS
    -DABCFRAMEWORK_IMPL
    -DABCFRAMEWORK_EXPORTS
    -DNOMINMAX)

add_softimage_plugin (AbcImportExport ${SOURCES} ${HEADERS})

MESSAGE(STATUS "BOOST LIBRARIES: ${Boost_LIBRARIES}")

IF (USE_HDF5)
    TARGET_LINK_LIBRARIES(AbcImportExport
        ${ALEMBIC_LIBRARYDIR}/Alembic.lib
        ${HDF5_LIBRARIES}
        ${ALEMBIC_ILMBASE_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
        ${ZLIB_LIBRARIES}
        ${EXTERNAL_MATH_LIBS}
    )
ELSE()
    TARGET_LINK_LIBRARIES(AbcImportExport
        ${ALEMBIC_LIBRARYDIR}/Alembic.lib
        ${ALEMBIC_ILMBASE_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
        ${EXTERNAL_MATH_LIBS}
    )
ENDIF()


