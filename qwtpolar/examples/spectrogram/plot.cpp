#include <qfiledialog.h>
#include <qimagewriter.h>
#include <qpen.h>
#include <qlocale.h>
#include <qwt_raster_data.h>
#include <qwt_polar_panner.h>
#include <qwt_polar_magnifier.h>
#include <qwt_polar_grid.h>
#include <qwt_polar_spectrogram.h>
#include <qwt_polar_renderer.h>
#include <qwt_polar_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_scale_div.h>
#include <qwt_round_scale_draw.h>
#include "plot.h"

class MyPicker: public QwtPolarPicker
{
public:
    MyPicker( QwtPolarCanvas *canvas ):
        QwtPolarPicker( canvas )
    {
        setStateMachine( new QwtPickerDragPointMachine() );
        setRubberBand( QwtPicker::NoRubberBand );
        setTrackerMode( ActiveOnly );
    }

    virtual QwtText trackerTextPolar( const QwtPointPolar &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 200 );

        QwtText text = QwtPolarPicker::trackerTextPolar( pos );
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }
};

// Pointless synthetic data, showing something nice

class SpectrogramData: public QwtRasterData
{
public:
    SpectrogramData()
    {
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 10.0 ) );
    }

    virtual double value( double azimuth, double radius ) const
    {
        const double c = 0.842;
        const double x = radius / 10.0 * 3.0 - 1.5;
        const double y = azimuth / ( 2 * M_PI ) * 3.0 - 1.5;

        const double v1 = qwtSqr( x ) + ( y - c ) * ( y + c );
        const double v2 = 2 * x * ( y + c );

        const double v = 1.0 / ( qwtSqr( v1 ) + qwtSqr( v2 ) );
        return v;
    }
};

class AzimuthScaleDraw: public QwtRoundScaleDraw
{
public:
    virtual QwtText label( double value ) const
    {
        QwtText text;

        if ( qFuzzyCompare( fmod( value, 2 * M_PI ), 0.0 ) )
        {
            return QString( "0" );
        }

        if ( qFuzzyCompare( fmod( value, M_PI_4 ), 0.0 ) )
        {
            QString text;
            if ( !qFuzzyCompare( value, M_PI ) )
            {
                text += QLocale().toString( value / M_PI );
                text += " ";
            }
            text += "<FONT face=Symbol size=4>p</FONT>";
            return text;
        }

        return QwtRoundScaleDraw::label( value );
    }
};

Plot::Plot( QWidget *parent ):
    QwtPolarPlot( parent )
{
    setAutoReplot( false );
    setPlotBackground( Qt::darkBlue );


    // scales
    setScale( QwtPolar::Azimuth, 0.0, 2 * M_PI, M_PI_4 );
    setScaleMaxMinor( QwtPolar::Azimuth, 2 );

    setScale( QwtPolar::Radius, 0.0, 10.0 );
    setScaleMaxMinor( QwtPolar::Radius, 2 );

    // grids
    d_grid = new QwtPolarGrid();
    d_grid->setPen( QPen( Qt::white ) );
    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        d_grid->showGrid( scaleId );
        d_grid->showMinorGrid( scaleId );

        QPen minorPen( Qt::gray );
        d_grid->setMinorGridPen( scaleId, minorPen );
    }
    d_grid->setAxisPen( QwtPolar::AxisAzimuth, QPen( Qt::black ) );
    d_grid->setAzimuthScaleDraw( new AzimuthScaleDraw() );
    d_grid->showAxis( QwtPolar::AxisAzimuth, true );
    d_grid->showAxis( QwtPolar::AxisLeft, false );
    d_grid->showAxis( QwtPolar::AxisRight, true );
    d_grid->showAxis( QwtPolar::AxisTop, false );
    d_grid->showAxis( QwtPolar::AxisBottom, false );
    d_grid->showGrid( QwtPolar::Azimuth, true );
    d_grid->showGrid( QwtPolar::Radius, true );
    d_grid->attach( this );

    // spectrogram

    d_spectrogram = new QwtPolarSpectrogram();
    d_spectrogram->setPaintAttribute(
        QwtPolarSpectrogram::ApproximatedAtan, true );
    d_spectrogram->setRenderThreadCount( 0 ); // use multi threading
    d_spectrogram->setData( new SpectrogramData() );
    d_spectrogram->attach( this );

    d_spectrogram->setZ( 1.0 );
    d_grid->setZ( 2.0 );

    QwtPolarPicker *picker = new MyPicker( canvas() );
    picker->setMousePattern( QwtEventPattern::MouseSelect1, Qt::RightButton );

    QwtPolarMagnifier *magnifier = new QwtPolarMagnifier( canvas() );
    magnifier->setMouseButton( Qt::RightButton, Qt::ShiftModifier );

    new QwtPolarPanner( canvas() );
}

QwtPolarSpectrogram *Plot::spectrogram()
{
    return d_spectrogram;
}

void Plot::rotate()
{
    const double interval = 15.0; // degrees

    double origin = azimuthOrigin() / M_PI * 180.0;
    origin = qRound( origin / interval ) * interval + interval;

    setAzimuthOrigin( origin / 180.0 * M_PI );
    replot();
}

void Plot::mirror()
{
    const double a1 = scaleDiv( QwtPolar::Azimuth )->upperBound();
    const double a2 = scaleDiv( QwtPolar::Azimuth )->lowerBound();

    setScale( QwtPolar::Azimuth, a1, a2, qAbs( a2 - a1 ) / 8.0 );
    replot();
}

void Plot::exportDocument()
{
    QwtPolarRenderer renderer;
    renderer.exportTo( this, "spectrogram.pdf", QSizeF( 200, 200 ), 300 );
}

void Plot::showGrid( bool on )
{
    d_grid->setVisible( on );
    replot();
}
