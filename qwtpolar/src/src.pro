# -*- mode: sh -*- ##############################################
# QwtPolar Widget Library
# Copyright (C) 2008   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#################################################################

# qmake project file for building the qwtpolar libraries

QWT_POLAR_ROOT = $${PWD}/..
include( $${QWT_POLAR_ROOT}/qwtpolarconfig.pri )
include( $${QWT_POLAR_ROOT}/qwtpolarbuild.pri )
include( $${QWT_POLAR_ROOT}/qwtpolarfunctions.pri )

TEMPLATE          = lib
TARGET            = $$qwtPolarLibraryTarget(qwtpolar)

DESTDIR           = $${QWT_POLAR_ROOT}/lib

contains(QWT_POLAR_CONFIG, QwtPolarDll ) {

    CONFIG += dll
    win32|symbian: DEFINES += QT_DLL QWT_DLL QWT_POLAR_DLL QWT_POLAR_MAKEDLL
}
else {
    CONFIG += staticlib
}

contains(QWT_CONFIG, QwtFramework) {

    CONFIG += lib_bundle
}

HEADERS += \
    qwt_polar_global.h \
    qwt_polar.h \
    qwt_polar_fitter.h \
    qwt_polar_item.h \
    qwt_polar_picker.h \
    qwt_polar_panner.h \
    qwt_polar_magnifier.h \
    qwt_polar_grid.h \
    qwt_polar_curve.h \
    qwt_polar_spectrogram.h \
    qwt_polar_marker.h \
    qwt_polar_itemdict.h \
    qwt_polar_canvas.h \
    qwt_polar_layout.h \
    qwt_polar_renderer.h \
    qwt_polar_plot.h

SOURCES += \
    qwt_polar_fitter.cpp \
    qwt_polar_item.cpp \
    qwt_polar_picker.cpp \
    qwt_polar_panner.cpp \
    qwt_polar_magnifier.cpp \
    qwt_polar_grid.cpp \
    qwt_polar_curve.cpp \
    qwt_polar_spectrogram.cpp \
    qwt_polar_marker.cpp \
    qwt_polar_itemdict.cpp \
    qwt_polar_canvas.cpp \
    qwt_polar_layout.cpp \
    qwt_polar_renderer.cpp \
    qwt_polar_plot.cpp

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
    QT += concurrent
}

contains(QWT_CONFIG, QwtPolarSvg) {

    QT += svg
}
else {

    DEFINES += QWT_POLAR_NO_SVG
}

# Install directives

target.path    = $${QWT_POLAR_INSTALL_LIBS}

doc.files      = $${QWT_POLAR_ROOT}/doc/html
unix:doc.files      += $${QWT_POLAR_ROOT}/doc/man 
doc.path       = $${QWT_POLAR_INSTALL_DOCS}

INSTALLS       = target doc

CONFIG(lib_bundle) {

    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files = $${HEADERS}
    FRAMEWORK_HEADERS.path = Headers
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}
else {

    headers.files  = $${HEADERS}
    headers.path   = $${QWT_POLAR_INSTALL_HEADERS}
    INSTALLS += headers
}
