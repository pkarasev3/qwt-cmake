
add_definitions(-DQT_DLL -DQWT_DLL ) # making qwt_polar as static, no import -DQWT_POLAR_DLL -DQWT_POLAR_MAKEDLL
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
QT4_WRAP_CPP(qwtpolar_MOC_SRCS ${qwtpolar_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
set( QWT_POLAR_INCLUDE_DIR     ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include  
    ${CMAKE_CURRENT_SOURCE_DIR}/../qwt-6.1/source/src
    CACHE  STRING "qwtpolar include dir" FORCE)
add_library(qwtpolarX STATIC ${qwtpolar_SRC} ${qwtpolar_MOC_SRCS})

target_link_libraries(qwtpolarX
                                 ${QT_QTCORE_LIBRARY}
                                 ${QT_QTGUI_LIBRARY}        
                                 ${QT_QTXML_LIBRARY} 
                                 qwtX
                                 )
                                 #${QWT_LIBRARY}  )

set_target_properties(qwtpolarX PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK")


include(CMakeInstallPackage.txt)