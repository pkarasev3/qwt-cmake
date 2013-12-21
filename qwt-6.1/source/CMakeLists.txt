
ADD_DEFINITIONS( ${QT_DEFINITIONS} )
add_definitions(-DQT_DLL -DQWT_MAKEDLL )
# making qwt_polar as static, no import -DQWT_POLAR_DLL -DQWT_POLAR_MAKEDLL
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
QT4_WRAP_CPP(qwt_MOC_SRCS ${qwt_MOCHDR} OPTIONS ${MOC_WARNING_FLG} )
set( QWT_INCLUDE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src 
    CACHE  STRING "qwt include dir" FORCE)
add_library(qwtX SHARED ${qwt_SRC} ${qwt_MOC_SRCS})

target_link_libraries(qwtX
                                 ${QT_LIBRARIES}
                            )

set_target_properties(qwtX PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK")

FIND_PACKAGE(EEsofPublish)
SET(qwtX_LIBRARIES SHARED qwtX ${QTCORE_LIB})
INCLUDE_DIRECTORIES(BEFORE ${QWT_INCLUDE_DIR})
include(CMakeInstallPackage.txt)

