
include_directories(../source/src)
add_executable(qwt_simpleplot  simpleplot/simpleplot.cpp)
target_link_libraries(qwt_simpleplot  qwtX ${QT_LIBRARIES})


function(qwtMakeSample  subdir)
    file(GLOB  xhdr  ${subdir}/*.h)
    file(GLOB  xcpp   ${subdir}/*.cpp)
    Xmessage(STATUS  "hdrs,cpp:  ${xhdr} , ${xcpp}")

    if( USING_QT5 )
        QT5_WRAP_CPP(xmocz  ${xhdr}  OPTIONS ${MOC_WARNING_FLG} )
    else()
        QT4_WRAP_CPP(xmocz  ${xhdr}  OPTIONS ${MOC_WARNING_FLG} )
    endif()

    set( SampleSource   ${xcpp}  ${xmocz}  ${xhdr} )
    Xmessage(STATUS  "sample source qwt= ${SampleSource} ")
    add_executable(qwt_${subdir}  ${SampleSource})
    target_link_libraries(qwt_${subdir}  qwtX ${QT_LIBRARIES})
    file(GLOB  extraz  ${subdir}/*.xpm ${subdir}/*.png)
    install(FILES  ${extraz}  DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set_target_properties(qwt_${subdir} PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK" VS_SCC_AUXPATH "SAK" FOLDER "MosaicSourceShared/Graphs")
endfunction(qwtMakeSample)


foreach(X
        realtime
        controls
        event_filter
        oscilloscope
        refreshtest
        scatterplot
        spectrogram
        cpuplot
        )
    qwtMakeSample( ${X} )
    if(WIN32)
        set(Y  qwt_${X})
        set_target_properties(${Y}
            PROPERTIES VS_SCC_PROJECTNAME "SAK" VS_SCC_LOCALPATH "SAK" VS_SCC_PROVIDER "SAK" VS_SCC_AUXPATH "SAK" )
            set_property(TARGET ${Y} PROPERTY FOLDER "MosaicSourceShared/Graphs/qwt_test"
            )
    endif()
endforeach()

# adjust compiler warnings
if( WIN32 )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4512 /wd4267" )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4512 /wd4267" )
endif()
