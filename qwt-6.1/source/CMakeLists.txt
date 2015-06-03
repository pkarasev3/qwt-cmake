
add_definitions( ${QT_DEFINITIONS} )
add_definitions(-DQT_DLL -DQWT_MAKEDLL )
if(WIN32)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  /wd4267  /wd4512 /wd4244")
endif()

file(GLOB  qwt_SRC  ./src/*.h  ./src/*.cpp)

set(qwt_MOCHDR
./src/qwt_abstract_legend.h
./src/qwt_abstract_scale.h
./src/qwt_abstract_slider.h
./src/qwt_analog_clock.h
./src/qwt_compass.h
./src/qwt_counter.h
./src/qwt_dial.h
./src/qwt_dyngrid_layout.h
./src/qwt_knob.h
./src/qwt_legend.h
./src/qwt_legend_label.h
./src/qwt_magnifier.h
./src/qwt_plot_opengl_canvas.h
./src/qwt_panner.h
./src/qwt_picker.h
./src/qwt_plot_canvas.h
./src/qwt_plot_glcanvas.h
./src/qwt_plot.h
./src/qwt_plot_magnifier.h
./src/qwt_plot_panner.h
./src/qwt_plot_picker.h
./src/qwt_plot_renderer.h
./src/qwt_plot_zoomer.h
./src/qwt_sampling_thread.h
./src/qwt_scale_widget.h
./src/qwt_slider.h
./src/qwt_text_label.h
./src/qwt_thermo.h
./src/qwt_wheel.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if( USING_QT5 )
QT5_WRAP_CPP(qwt_MOC_SRCS ${qwt_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
else()
QT4_WRAP_CPP(qwt_MOC_SRCS ${qwt_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
endif()

set( QWT_INCLUDE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    CACHE  STRING "qwt include dir" FORCE)
add_library(qwtX SHARED ${qwt_SRC} ${qwt_MOC_SRCS})

if( USING_QT5 )
qt5_use_modules(qwtX Core Gui Widgets PrintSupport Svg OpenGL Concurrent)
endif()

target_link_libraries( qwtX ${QT_LIBRARIES} )

if(DEFINED ProfilerLib)
    if( EESOF_CMAKE_VERBOSE )
     message(STATUS "trying to link with ${EESOF_gperftools_library_dir}/libprofiler.so ")
    endif( EESOF_CMAKE_VERBOSE )
    target_link_libraries(qwtX  ${EESOF_gperftools_library_dir}/libprofiler.so)
endif()

set_target_properties(qwtX PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK" VS_SCC_AUXPATH "SAK")

find_package(EEsofPublish)
SET(qwtX_LIBRARIES SHARED qwtX ${QTCORE_LIB})
include_directories(BEFORE ${QWT_INCLUDE_DIR})
include(CMakeInstallPackage.txt)


# adjust compiler warnings
if( WIN32 )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127 /wd4189" )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4127 /wd4189" )
endif()
