#ifndef _VIEWS_PLOT_HPP_
#define _VIEWS_PLOT_HPP_

#include <QMdiArea>
#include <QMdiSubWindow>
#include <qcustomplot.h>
#include <models/Signal.h>

namespace views {
    
class Plot : virtual public QMdiSubWindow, virtual public QCustomPlot {
 protected:
    using Self = Plot;
    using WindowBase = QMdiSubWindow;
    using PlotBase = QCustomPlot;

 public:
    Plot(const std::string& x_label, const std::string& y_label, QWidget* parent = nullptr);
    ~Plot() override;

    void plot(const QVector<double>& x, const QVector<double>& y);
    void plot(const models::Channel& channel);

    void show();
};
    
} // namespace views

#endif