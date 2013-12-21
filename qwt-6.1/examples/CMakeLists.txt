
include_directories(../source/src)
add_executable(qwt_simpleplot  simpleplot/simpleplot.cpp)
target_link_libraries(qwt_simpleplot  qwtX ${QT_LIBRARIES})

