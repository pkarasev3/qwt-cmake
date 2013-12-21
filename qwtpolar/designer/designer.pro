# -*- mode: sh -*- ###########################
# QwtPolar Widget Library
# Copyright (C) 2008   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
##############################################

QWT_POLAR_ROOT = $${PWD}/..

include ( $${QWT_POLAR_ROOT}/qwtpolarconfig.pri )
include ( $${QWT_POLAR_ROOT}/qwtpolarbuild.pri )
include ( $${QWT_POLAR_ROOT}/qwtpolarfunctions.pri )

contains(QWT_POLAR_CONFIG, QwtPolarDesigner) {

    CONFIG    += qt plugin
	CONFIG    += warn_on

    greaterThan(QT_MAJOR_VERSION, 4) {

        QT += designer
    }
    else {

        CONFIG    += designer
    }

	TEMPLATE        = lib
	TARGET          = qwt_polar_designer_plugin

	DESTDIR         = plugins/designer

	INCLUDEPATH    += $${QWT_POLAR_ROOT}/src 
	DEPENDPATH     += $${QWT_POLAR_ROOT}/src 

    contains(QWT_CONFIG, QwtFramework) {

        LIBS      += -F$${QWT_POLAR_ROOT}/lib
    }
    else {

        LIBS      += -L$${QWT_POLAR_ROOT}/lib
    }

	qwtPolarAddLibrary(qwtpolar)

	contains(CONFIG, QwtPolarDll) {

		win32 {
			DEFINES += QT_DLL QWT_DLL QWT_POLAR_DLL
		}
	}

	HEADERS += qwt_polar_designer_plugin.h
	SOURCES += qwt_polar_designer_plugin.cpp
	RESOURCES += qwt_polar_designer_plugin.qrc

	target.path = $${QWT_POLAR_INSTALL_PLUGINS}
	INSTALLS += target
}
else {
	TEMPLATE        = subdirs # do nothing
}
