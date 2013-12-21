# -*- mode: sh -*- ##############################################
# QwtPolar Widget Library
# Copyright (C) 2008   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#################################################################

QWT_POLAR_ROOT = $${PWD}/..
include( $${QWT_POLAR_ROOT}/qwtpolarconfig.pri )
include( $${QWT_POLAR_ROOT}/qwtpolarbuild.pri )
include( $${QWT_POLAR_ROOT}/qwtpolarfunctions.pri )

TEMPLATE     = app

INCLUDEPATH += $${QWT_POLAR_ROOT}/src
DEPENDPATH  += $${QWT_POLAR_ROOT}/src
DESTDIR      = $${QWT_POLAR_ROOT}/examples/bin$${SUFFIX_STR}

contains(QWT_CONFIG, QwtFramework) {

    LIBS      += -F$${QWT_POLAR_ROOT}/lib
}
else {

    LIBS      += -L$${QWT_POLAR_ROOT}/lib
}

qwtPolarAddLibrary(qwtpolar)

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

win32 {
    contains(QWT_CONFIG, QwtPolarDll) {
        DEFINES    += QT_DLL QWT_DLL QWT_POLAR_DLL
    }
}

