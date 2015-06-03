/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_glcanvas.h"
#include "qwt_plot.h"
#include <qevent.h>
#include <qglframebufferobject.h>

class QwtPlotGLCanvas::PrivateData
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

    QGLFramebufferObject* fbo;
};

class QwtPlotGLCanvasFormat: public QGLFormat
{
public:
    QwtPlotGLCanvasFormat():
        QGLFormat( QGLFormat::defaultFormat() )
    {
        setSampleBuffers( true );
    }
};

/*! 
  \brief Constructor

  \param plot Parent plot widget
  \sa QwtPlot::setCanvas()
*/
QwtPlotGLCanvas::QwtPlotGLCanvas( QwtPlot *plot ):
    QGLWidget( QwtPlotGLCanvasFormat(), plot ),
    QwtPlotAbstractGLCanvas( this )
{
    d_data = new PrivateData;
#if 1
    setAttribute( Qt::WA_OpaquePaintEvent, true );
#endif
}

QwtPlotGLCanvas::QwtPlotGLCanvas( const QGLFormat &format, QwtPlot *plot ):
    QGLWidget( format, plot ),
    QwtPlotAbstractGLCanvas( this )
{
    d_data = new PrivateData;
#if 1
    setAttribute( Qt::WA_OpaquePaintEvent, true );
#endif
}

//! Destructor
QwtPlotGLCanvas::~QwtPlotGLCanvas()
{
    delete d_data;
}

/*!
  Paint event

  \param event Paint event
  \sa QwtPlot::drawCanvas()
*/
void QwtPlotGLCanvas::paintEvent( QPaintEvent *event )
{
    QGLWidget::paintEvent( event );
}

/*!
  Qt event handler for QEvent::PolishRequest and QEvent::StyleChange
  \param event Qt Event
  \return See QGLWidget::event()
*/
bool QwtPlotGLCanvas::event( QEvent *event )
{
    const bool ok = QGLWidget::event( event );

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

void QwtPlotGLCanvas::replot()
{
    QwtPlotAbstractGLCanvas::replot();
}

void QwtPlotGLCanvas::invalidateBackingStore()
{
    delete d_data->fbo;
    d_data->fbo = NULL;
}

QPainterPath QwtPlotGLCanvas::borderPath( const QRect &rect ) const
{
    return QwtPlotAbstractGLCanvas::borderPath( rect );
}

void QwtPlotGLCanvas::initializeGL()
{
}

void QwtPlotGLCanvas::paintGL()
{
    const bool hasFocusIndicator =
        hasFocus() && focusIndicator() == CanvasFocusIndicator;

    QPainter painter;

#if QT_VERSION < 0x040600
    painter.begin( this );
    draw( &painter );
#else
    if ( testPaintAttribute( QwtPlotGLCanvas::BackingStore ) )
    {
        if ( d_data->fbo == NULL || d_data->fbo->size() != size() )
        {
            invalidateBackingStore();

            const int numSamples = 16;

            QGLFramebufferObjectFormat format;
            format.setSamples( numSamples );
            format.setAttachment(QGLFramebufferObject::CombinedDepthStencil);

            QGLFramebufferObject fbo( size(), format );

            QPainter fboPainter( &fbo );
            draw( &fboPainter);
            fboPainter.end();

            d_data->fbo = new QGLFramebufferObject( size() );

            QRect rect(0, 0, width(), height());
            QGLFramebufferObject::blitFramebuffer(d_data->fbo, rect, &fbo, rect);
        }

        // drawTexture( QRectF( -1.0, 1.0, 2.0, -2.0 ), d_data->fbo->texture() );

        if ( hasFocusIndicator )
            painter.begin( this );
        
		Q_ASSERT(0);
        //glBindTexture(GL_TEXTURE_2D, d_data->fbo->texture());
        //
        //glEnable(GL_TEXTURE_2D);
        //
        //glBegin(GL_QUADS);
        //
        //glTexCoord2f(0.0f, 0.0f);
        //glVertex2f(-1.0f, -1.0f);
        //glTexCoord2f(1.0f, 0.0f);
        //glVertex2f( 1.0f, -1.0f);
        //glTexCoord2f(1.0f, 1.0f);
        //glVertex2f( 1.0f,  1.0f);
        //glTexCoord2f(0.0f, 1.0f);
        //glVertex2f(-1.0f,  1.0f);
        //
        //glEnd();
    }
    else
    {
        painter.begin( this );
        draw( &painter );
    }
#endif

    if ( hasFocus() && focusIndicator() == CanvasFocusIndicator )
        drawFocusIndicator( &painter );
}

void QwtPlotGLCanvas::resizeGL( int, int )
{
    invalidateBackingStore();
}
