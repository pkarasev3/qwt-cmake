add_subdirectory(source)

add_subdirectory(examples)

#file(GLOB bodeplotSRC examples/bode/*.h examples/bode/*.cpp)
#add_executable(qwt_bodeplot  ${bodeplotSRC})
#target_link_libraries(qwt_bodeplot qwtX ${QT_LIBRARIES})

#file(GLOB legendSRC examples/legends/*.h examples/legends/*.cpp)
#add_executable(qwt_legends  ${legendSRC})
#target_link_libraries(qwt_legends qwtX ${QT_LIBRARIES})
