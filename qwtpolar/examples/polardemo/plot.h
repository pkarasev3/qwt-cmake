#ifndef _PLOT_H_
#define _PLOT_H_ 1

#include <qwt_polar_plot.h>

class QwtPolarGrid;
class QwtPolarCurve;

class PlotSettings
{
public:
    enum Curve
    {
        Spiral,
        Rose,

        NumCurves
    };

    enum Flag
    {
        MajorGridBegin,
        MinorGridBegin = MajorGridBegin + QwtPolar::ScaleCount,
        AxisBegin = MinorGridBegin + QwtPolar::ScaleCount,

        AutoScaling = AxisBegin + QwtPolar::AxesCount,
        Inverted,
        Logarithmic,

        Antialiasing,

        CurveBegin,

        NumFlags = CurveBegin + NumCurves
    };

    bool flags[NumFlags];
};

class Plot: public QwtPolarPlot
{
    Q_OBJECT

public:
    Plot( QWidget * = NULL );
    PlotSettings settings() const;

public Q_SLOTS:
    void applySettings( const PlotSettings & );

private:
    QwtPolarCurve *createCurve( int id ) const;

    QwtPolarGrid *d_grid;
    QwtPolarCurve *d_curve[PlotSettings::NumCurves];
};

#endif


