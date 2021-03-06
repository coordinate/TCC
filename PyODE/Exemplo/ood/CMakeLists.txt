CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)




PROJECT(ood)




SET(LOCAL_PROJECT_NAME ood)



SET(OOD_SOVERSION 41)
SET(OOD_MAJOR_VERSION 2)
SET(OOD_MINOR_VERSION 3)
SET(OOD_PATCH_VERSION 0)
SET(OOD_VERSION ${OOD_MAJOR_VERSION}.${OOD_MINOR_VERSION}.${OOD_PATCH_VERSION})



IF(NOT WIN32)
    IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
        SET(LIB_POSTFIX "64" CACHE STRING "suffix for 32/64 dir placement")
        MARK_AS_ADVANCED(LIB_POSTFIX)
    ENDIF()

    SET(PKGCONFIG_FILES
            ood
            oodUtil
    )

    FOREACH(PKGCONFIG_FILE ${PKGCONFIG_FILES})
        CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/packaging/pkgconfig/${PKGCONFIG_FILE}.pc.in
        ${PROJECT_BINARY_DIR}/packaging/pkgconfig/${PKGCONFIG_FILE}.pc
        @ONLY
        )
    INSTALL(FILES ${PROJECT_BINARY_DIR}/packaging/pkgconfig/${PKGCONFIG_FILE}.pc DESTINATION lib${LIB_POSTFIX}/pkgconfig)
    ENDFOREACH(PKGCONFIG_FILE)
ENDIF(NOT WIN32)






CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/src/ood/Version.cpp.in" "${PROJECT_SOURCE_DIR}/src/ood/Version.cpp")


# Dynamic vs Static Linking
OPTION(DYNAMIC_OOD "Set to ON to build ood for dynamic linking.  Use OFF for static." ON)
IF(DYNAMIC_OOD)
    SET(OOD_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DOOD_LIBRARY)
ELSE(DYNAMIC_OOD)
    SET(OOD_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DOOD_LIBRARY_STATIC)
ENDIF(DYNAMIC_OOD)






OPTION(OOD_ANDROID_ABI "" "armeabi")



OPTION(OOD_BUILD_PLATFORM_ANDROID "" OFF)
IF(OOD_BUILD_PLATFORM_ANDROID)


#     SET(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG" )

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fno-exceptions" )

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions" )



    SET(ANDROID TRUE)
#     SET(ANDROID_PLATFORM 9)

    ADD_DEFINITIONS(-DANDROID=1)

#     SET(OOD_ANDROID_TEMPLATES "${CMAKE_SOURCE_DIR}/PlatformSpecifics/Android")




    IF(     OOD_ANDROID_ABI STREQUAL "armeabi" )

        SET( CMAKE_SYSTEM_PROCESSOR "armv5te" )

        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv5te -mtune=xscale -msoft-float" )
        SET( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -march=armv5te -mtune=xscale -msoft-float" )



    ELSEIF( OOD_ANDROID_ABI STREQUAL "armeabi-v7a" )

        SET( CMAKE_SYSTEM_PROCESSOR "armv7-a" )

        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -mfloat-abi=softfp" )
        SET( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -march=armv7-a -mfloat-abi=softfp" )


    ELSE()
        MESSAGE( WARNING "Specified ABI (" ${OOD_ANDROID_ABI} ") not in [armeabi,armeabi-v7a]" )
    ENDIF()







ENDIF(OOD_BUILD_PLATFORM_ANDROID)







OPTION(OOD_COMBINET "" OFF)
IF(OOD_COMBINET)

    ADD_DEFINITIONS(-DOOD_COMBINET_BUILD=1)

    MESSAGE(STATUS "CombiNet build")

ENDIF(OOD_COMBINET)









INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)



IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)



IF(CMAKE_BUILD_TYPE MATCHES "Debug")

    SET(PS_VERBOSE "1")
    SET(PS_ASSERT_ENABLED "1")
    SET(PS_DEFAULT_LOG_LEVEL "LOG_LEVEL_DEBUG2")

ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")



IF(CMAKE_BUILD_TYPE MATCHES "Release")

    SET(PS_VERBOSE "0")
    SET(PS_ASSERT_ENABLED "0")
    SET(PS_DEFAULT_LOG_LEVEL "LOG_LEVEL_NONE")

ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")



IF(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")

    SET(PS_VERBOSE "1")
    SET(PS_ASSERT_ENABLED "1")
    SET(PS_DEFAULT_LOG_LEVEL "LOG_LEVEL_NONE")

ENDIF(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")



IF(CMAKE_BUILD_TYPE MATCHES "MinSizeRel")

    SET(PS_VERBOSE "0")
    SET(PS_ASSERT_ENABLED "0")
    SET(PS_DEFAULT_LOG_LEVEL "LOG_LEVEL_NONE")

ENDIF(CMAKE_BUILD_TYPE MATCHES "MinSizeRel")


MESSAGE(STATUS "ood build: ${CMAKE_BUILD_TYPE}")




OPTION(OOD_REPORT_FILE_AND_LINE "" OFF)
IF(OOD_REPORT_FILE_AND_LINE)
    SET(PS_REPORT_FILE_AND_LINE "1")
ELSE(OOD_REPORT_FILE_AND_LINE)
    SET(PS_REPORT_FILE_AND_LINE "0")
ENDIF(OOD_REPORT_FILE_AND_LINE)




OPTION(OOD_USE_SINGLE_PRECISION "" ON)

MARK_AS_ADVANCED(OOD_USE_SINGLE_PRECISION)

IF(OOD_USE_SINGLE_PRECISION)
    SET(OOD_SINGLE_PRECISION "1")
    SET(OOD_REAL "float")

ELSE(OOD_USE_SINGLE_PRECISION)
    SET(OOD_SINGLE_PRECISION "0")
    SET(OOD_REAL "double")

ENDIF(OOD_USE_SINGLE_PRECISION)

MESSAGE(STATUS "ood precision: ${OOD_REAL}")





IF( WIN32 )
    ADD_DEFINITIONS(-W4 /wd4127)
ELSE( WIN32 )
    ADD_DEFINITIONS(-Wall -fPIC)
ENDIF( WIN32 )




CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/include/ood/Config.in" "${PROJECT_SOURCE_DIR}/include/ood/Config")





IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    ADD_DEFINITIONS(-DIS_X86_64=1)

ELSE( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    ADD_DEFINITIONS(-DIS_X86_64=0)

ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 8 )







IF( WIN32 )
    SET(OOD_OSG_BINARIES "$ENV{PROGRAMFILES}\\OpenSceneGraph\\bin" CACHE PATH "OSG binaries")
    MESSAGE(STATUS "OSG binaries: ${OOD_OSG_BINARIES}")
ENDIF( WIN32 )






IF( WIN32 )

    SET(OOD_OSG_INCLUDE "$ENV{PROGRAMFILES}\\OpenSceneGraph\\include" CACHE PATH "OSG Headers")
    SET(OOD_ODE_INCLUDE "$ENV{PROGRAMFILES}\\OpenDynamicsEngine\\include" CACHE PATH "ODE Headers")

    SET(OOD_OSG_LIBRARIES "$ENV{PROGRAMFILES}\\OpenSceneGraph\\lib" CACHE PATH "OSG Libraries")
    SET(OOD_ODE_LIBRARIES "$ENV{PROGRAMFILES}\\OpenDynamicsEngine\\lib" CACHE PATH "ODE Libraries")

    EXECUTE_PROCESS(COMMAND ${OOD_OSG_BINARIES}\\osgversion.exe --version-number OUTPUT_VARIABLE OSG_VERSION)
    STRING(REGEX REPLACE "\n" "" OOD_OSG_VERSION "${OSG_VERSION}")


ELSE( WIN32 )

    FIND_PACKAGE( PkgConfig )

    PKG_CHECK_MODULES( ODE REQUIRED ode )
    PKG_CHECK_MODULES( OSG REQUIRED openscenegraph-osg )

    SET(OOD_OSG_INCLUDE ${OSG_INCLUDE_DIRS} CACHE PATH "OSG Headers")
    SET(OOD_ODE_INCLUDE ${ODE_INCLUDE_DIRS} CACHE PATH "ODE Headers")

    SET(OOD_OSG_LIBRARIES ${OSG_LIBRARY_DIRS} CACHE PATH "OSG Headers")
    SET(OOD_ODE_LIBRARIES ${ODE_LIBRARY_DIRS} CACHE PATH "ODE Headers")

    SET(OOD_OSG_VERSION ${OSG_VERSION} CACHE PATH "OSG Version")

ENDIF( WIN32 )



MESSAGE(STATUS "OSG include: ${OOD_OSG_INCLUDE}")
MESSAGE(STATUS "ODE include: ${OOD_ODE_INCLUDE}")

MESSAGE(STATUS "OSG libraries: ${OOD_OSG_LIBRARIES}")
MESSAGE(STATUS "ODE libraries: ${OOD_ODE_LIBRARIES}")




INCLUDE_DIRECTORIES(${OOD_OSG_INCLUDE})
INCLUDE_DIRECTORIES(${OOD_ODE_INCLUDE})

LINK_DIRECTORIES( ${OOD_OSG_LIBRARIES} )
LINK_DIRECTORIES( ${OOD_ODE_LIBRARIES} )





CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")





SET(OOD_DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/doc" CACHE PATH "Doxygen output directory")



SET(OOD_TEMP_DOXYGEN_INPUT "${PROJECT_BINARY_DIR}/doc/ood_doxygen_input_files.txt")
MARK_AS_ADVANCED(OOD_TEMP_DOXYGEN_INPUT)

FILE(WRITE ${OOD_TEMP_DOXYGEN_INPUT} "${PROJECT_SOURCE_DIR}/README\n")
FILE(APPEND ${OOD_TEMP_DOXYGEN_INPUT} "${PROJECT_SOURCE_DIR}/README_WINDOWS\n")
FILE(APPEND ${OOD_TEMP_DOXYGEN_INPUT} "${PROJECT_SOURCE_DIR}/README_ANDROID\n")


FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(  doc
                        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        COMMENT "Generating API documentation with Doxygen"
                        VERBATIM
    )
ENDIF(DOXYGEN_FOUND)




SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

INCLUDE(oodMacros)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(doc)


IF( NOT ANDROID )

    OPTION(OOD_BUILD_EXAMPLES "Build ood examples" OFF)
    MESSAGE(STATUS "ood examples: ${OOD_BUILD_EXAMPLES}")

    OPTION(OOD_BUILD_OOS_EXAMPLES "Build ood examples based on the o.O Sound library" OFF)
    MESSAGE(STATUS "ood o.O Sound examples: ${OOD_BUILD_OOS_EXAMPLES}")


    IF( OOD_BUILD_EXAMPLES )

        SET(OOD_SAMPLE_DATA "${CMAKE_SOURCE_DIR}/../ood-data-2.0.0" CACHE PATH "ood sample data")
        MESSAGE(STATUS "ood sample data: ${OOD_SAMPLE_DATA}")

        ADD_SUBDIRECTORY( examples )

    ENDIF( OOD_BUILD_EXAMPLES )




    OPTION(OOD_BUILD_APPLICATIONS "Build ood applications" ON)
    MESSAGE(STATUS "ood applications: ${OOD_BUILD_APPLICATIONS}")


    IF( OOD_BUILD_APPLICATIONS )
        ADD_SUBDIRECTORY( applications )
    ENDIF( OOD_BUILD_APPLICATIONS )

ENDIF( NOT ANDROID )




FILE(REMOVE ${OOD_TEMP_DOXYGEN_INPUT})




MESSAGE(STATUS "${PROJECT_NAME} install prefix: ${CMAKE_INSTALL_PREFIX}")
