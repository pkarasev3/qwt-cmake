/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * QwtPolar Widget Library
 * Copyright (C) 2008   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#if defined(_MSC_VER) /* MSVC Compiler */
#pragma warning ( disable : 4786 )
#endif

#include <qglobal.h>
#include <qaction.h>
#include <QtPlugin>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowCursorInterface>
#include <QExtensionManager>
#include <QErrorMessage>

#include "qwt_polar_designer_plugin.h"
#include "qwt_polar_plot.h"

using namespace QwtPolarDesignerPlugin;

PolarPlotInterface::PolarPlotInterface( QObject *parent ):
    QObject( parent )
{
}

bool PolarPlotInterface::isContainer() const
{
    return false;
}

QIcon PolarPlotInterface::icon() const
{
    return QPixmap( ":/pixmaps/qwt_polar_plot.png" );
}

QString PolarPlotInterface::domXml() const
{
    return QString(
        "<widget class=\"QwtPolarPlot\" name=\"qwtPolarPlot\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>400</width>\n"
        "   <height>400</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n"
    );
}

QString PolarPlotInterface::group() const
{
    return "QwtPolarPlot";
}

QString PolarPlotInterface::includeFile() const
{
    return "qwt_polar_plot.h";
}

QString PolarPlotInterface::name() const
{
    return "QwtPolarPlot";
}

QString PolarPlotInterface::toolTip() const
{
    return "QwtPolarPlot";
}

QString PolarPlotInterface::whatsThis() const
{
    return "A polar plot widget";
}

QWidget *PolarPlotInterface::createWidget( QWidget *parent )
{
    return new QwtPolarPlot( parent );
}

CustomWidgetCollectionInterface::CustomWidgetCollectionInterface(
        QObject *parent ):
    QObject( parent )
{
    d_plugins.append( new PolarPlotInterface( this ) );
}

QList<QDesignerCustomWidgetInterface*>
CustomWidgetCollectionInterface::customWidgets( void ) const
{
    return d_plugins;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( QwtPolarDesignerPlugin, CustomWidgetCollectionInterface )
#endif
