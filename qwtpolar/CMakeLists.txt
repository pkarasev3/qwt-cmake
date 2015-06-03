add_definitions( ${QT_DEFINITIONS} )
add_definitions(-DQT_DLL -DQWT_DLL -DQWT_POLAR_MAKEDLL )

#add_definitions(-DQT_DLL -DQWT_DLL ) # making qwt_polar as static, no import -DQWT_POLAR_DLL -DQWT_POLAR_MAKEDLL


file(GLOB  qwtpolar_SRC  ./include/*.h  ./src/*.cpp)

set(qwtpolar_MOCHDR   
./include/qwt_polar_panner.h
./include/qwt_polar_canvas.h
./include/qwt_polar_plot.h
./include/qwt_polar_picker.h
./include/qwt_polar_magnifier.h
./include/qwt_polar_renderer.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${QWT_INCLUDE_DIR})

if( USING_QT5 )
QT5_WRAP_CPP(qwtpolar_MOC_SRCS ${qwtpolar_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
else()
QT4_WRAP_CPP(qwtpolar_MOC_SRCS ${qwtpolar_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
endif()


set( QWT_POLAR_INCLUDE_DIR     ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include  
    ${CMAKE_CURRENT_SOURCE_DIR}/../qwt-6.1/source/src
    CACHE  STRING "qwtpolar include dir" FORCE)
add_library(qwtpolarX SHARED ${qwtpolar_SRC} ${qwtpolar_MOC_SRCS})

if( USING_QT5 )
qt5_use_modules(qwtpolarX Core Gui Widgets PrintSupport Svg OpenGL Concurrent)
endif()

target_link_libraries(qwtpolarX
                                 ${QT_QTCORE_LIBRARY}
                                 ${QT_QTGUI_LIBRARY}        
                                 ${QT_QTXML_LIBRARY} 
                                 qwtX
                                 )
                                 #${QWT_LIBRARY}  )

set_target_properties(qwtpolarX PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK" VS_SCC_AUXPATH "SAK")

include(CMakeInstallPackage.txt)

# adjust compiler warnings
if( WIN32 )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4127 /wd4512" )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4244 /wd4127 /wd4512" )
endif()
