#include <views/plot.hpp>

namespace views {

////////////////////////////////////////////////////////////
// Plot implementation
////////////////////////////////////////////////////////////

Plot::Plot(const std::string& x_label, const std::string& y_label, QWidget *parent) : WindowBase(parent) {
    this->WindowBase::setWidget(static_cast<PlotBase*>(this));
    this->xAxis->setLabel(x_label.c_str());
    this->yAxis->setLabel(y_label.c_str());
}

Plot::~Plot() = default;

void Plot::plot(const QVector<double>& x, const QVector<double>& y) {
    this->addGraph();
    this->graph(this->graphCount() - 1)->setData(x, y);
}

void Plot::plot(const models::Channel& channel) {
    auto bounds = channel.get_bounds();

    const size_t size = channel.get_frequency().size();

    QVector<double> x(size), y(size);
    for (int i = 0; i < size; ++i) {
        x[i] = channel.get_frequency()[i].t.to_timestamp();
        y[i] = channel.get_frequency()[i].v;
    }

    this->xAxis->setRange(bounds.start_time.to_timestamp(), bounds.end_time.to_timestamp());
    this->yAxis->setRange(bounds.min_value, bounds.max_value);

    this->plot(x, y);
}

void Plot::show() {
    this->WindowBase::show();
}

}

