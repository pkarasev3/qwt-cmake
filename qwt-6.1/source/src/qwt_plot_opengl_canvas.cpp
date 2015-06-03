/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/
#ifdef USING_QT5

#include "qwt_plot_opengl_canvas.h"
#include "qwt_plot.h"
#include <qevent.h>
#include <qopenglframebufferobject.h>
#include <qopenglpaintdevice.h>

class QwtPlotOpenGLCanvas::PrivateData
{
public:
    PrivateData():
        fbo( NULL )
    {
    }

    ~PrivateData()
    {
        delete fbo;
    }

    QOpenGLFramebufferObject* fbo;
};


/*! 
  \brief Constructor

  \param plot Parent plot widget
  \sa QwtPlot::setCanvas()
*/
QwtPlotOpenGLCanvas::QwtPlotOpenGLCanvas( QwtPlot *plot ):
    QOpenGLWidget( plot ),
    QwtPlotAbstractGLCanvas( this )
{
    QSurfaceFormat fmt = format();
    fmt.setSamples(16);
    setFormat( fmt );

    d_data = new PrivateData;
#if 1
    setAttribute( Qt::WA_OpaquePaintEvent, true );
#endif
}

QwtPlotOpenGLCanvas::QwtPlotOpenGLCanvas( const QSurfaceFormat &format, QwtPlot *plot ):
    QOpenGLWidget( plot ),
    QwtPlotAbstractGLCanvas( this )
{
    setFormat( format );
    d_data = new PrivateData;
#if 1
    setAttribute( Qt::WA_OpaquePaintEvent, true );
#endif
}

//! Destructor
QwtPlotOpenGLCanvas::~QwtPlotOpenGLCanvas()
{
    delete d_data;
}

/*!
  Paint event

  \param event Paint event
  \sa QwtPlot::drawCanvas()
*/
void QwtPlotOpenGLCanvas::paintEvent( QPaintEvent *event )
{
    QOpenGLWidget::paintEvent( event );
}

/*!
  Qt event handler for QEvent::PolishRequest and QEvent::StyleChange
  \param event Qt Event
  \return See QGLWidget::event()
*/
bool QwtPlotOpenGLCanvas::event( QEvent *event )
{
    const bool ok = QOpenGLWidget::event( event );

    if ( event->type() == QEvent::PolishRequest ||
        event->type() == QEvent::StyleChange )
    {
        // assuming, that we always have a styled background
        // when we have a style sheet

        setAttribute( Qt::WA_StyledBackground,
            testAttribute( Qt::WA_StyleSheet ) );
    }

    return ok;
}

void QwtPlotOpenGLCanvas::replot()
{
    QwtPlotAbstractGLCanvas::replot();
}

void QwtPlotOpenGLCanvas::invalidateBackingStore()
{
    delete d_data->fbo;
    d_data->fbo = NULL;
}

QPainterPath QwtPlotOpenGLCanvas::borderPath( const QRect &rect ) const
{
    return QwtPlotAbstractGLCanvas::borderPath( rect );
}

void QwtPlotOpenGLCanvas::initializeGL()
{
}

void QwtPlotOpenGLCanvas::paintGL()
{
    const bool hasFocusIndicator = 
        hasFocus() && focusIndicator() == CanvasFocusIndicator;

    QPainter painter;

    if ( testPaintAttribute( QwtPlotOpenGLCanvas::BackingStore ) )
    {
        if ( d_data->fbo == NULL || d_data->fbo->size() != size() )
        {
            invalidateBackingStore();

            const int numSamples = 16;

            QOpenGLFramebufferObjectFormat format;
            format.setSamples( numSamples );
            format.setAttachment( QOpenGLFramebufferObject::CombinedDepthStencil );

            QOpenGLFramebufferObject fbo( size(), format );

            QOpenGLPaintDevice pd( size() );

            QPainter fboPainter( &pd );
            draw( &fboPainter);
            fboPainter.end();

            d_data->fbo = new QOpenGLFramebufferObject( size() );
            QOpenGLFramebufferObject::blitFramebuffer(d_data->fbo, &fbo );
        }

        if ( hasFocusIndicator )
            painter.begin( this );

		Q_ASSERT(0);
        //glBindTexture(GL_TEXTURE_2D, d_data->fbo->texture());

        //glEnable(GL_TEXTURE_2D);

        //glBegin(GL_QUADS);

        //glTexCoord2f(0.0f, 0.0f);
        //glVertex2f(-1.0f, -1.0f);
        //glTexCoord2f(1.0f, 0.0f);
        //glVertex2f( 1.0f, -1.0f);
        //glTexCoord2f(1.0f, 1.0f);
        //glVertex2f( 1.0f,  1.0f);
        //glTexCoord2f(0.0f, 1.0f);
        //glVertex2f(-1.0f,  1.0f);

        //glEnd();
    }
    else
    {
        painter.begin( this );
        draw( &painter );
    }

    if ( hasFocusIndicator )
        drawFocusIndicator( &painter );
}

void QwtPlotOpenGLCanvas::resizeGL( int, int )
{
    invalidateBackingStore();
}

#endif