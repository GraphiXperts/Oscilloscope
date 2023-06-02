#include <iostream>
#include <views/plots.hpp>

namespace vw {

////////////////////////////////////////////////////////////////
/// Bounds implementation
////////////////////////////////////////////////////////////////

Bounds::Bounds()
    : top(-INFINITY), bottom(INFINITY), left(INFINITY), right(-INFINITY) {}

Bounds::Bounds(double top, double bottom, double left, double right)
    : top(top), bottom(bottom), left(left), right(right) {}

Bounds::Bounds(double x, double y) : top(y), bottom(y), left(x), right(x) {}

Bounds::Bounds(const Bounds& other) = default;

Bounds::Bounds(Bounds&& other) = default;

Bounds::~Bounds() = default;

//----------------------------------------------------------------

Bounds& Bounds::operator=(const Bounds& other) = default;

Bounds& Bounds::operator=(Bounds&& other) = default;

//----------------------------------------------------------------

Bounds Bounds::operator+(const Bounds& other) const {
    return Bounds(std::max(top, other.top), std::min(bottom, other.bottom),
                  std::min(left, other.left), std::max(right, other.right));
}

Bounds& Bounds::operator+=(const Bounds& other) {
    return *this = *this + other;
}

////////////////////////////////////////////////////////////////
/// Points implementation
////////////////////////////////////////////////////////////////

void Points::add(double x, double y) {
    bounds += Bounds(x, y);

    this->x.push_back(x);
    this->y.push_back(y);
}

void Points::resize(size_t size) {
    this->x.resize(size);
    this->y.resize(size);

    bounds = Bounds();
    for (int i = 0; i < size; i++)
        bounds += Bounds(x[i], y[i]);
}

void Points::clear() {
    this->x.clear();
    this->y.clear();

    bounds = Bounds();
}

size_t Points::size() const {
    return std::min(x.size(), y.size());
}

Points getPoints(mdl::Range range) {
    Points points;
    points.clear();

    for (auto& el : range)
        points.add(el.value, el.time);
    
    return points;
}

////////////////////////////////////////////////////////////////
/// SignalPlot implementation
////////////////////////////////////////////////////////////////

void SignalPlot::clear_plots() {
    for (auto el : widgets_) delete el;
    widgets_.clear();
}

void SignalPlot::add_plot(const mdl::Channel& channel) {
    QCustomPlot* plot = new QCustomPlot();

    auto res = channel.range(0, channel.size() - 1);
    Points points = getPoints(*res);

    plot->xAxis->setRange(points.bounds.left, points.bounds.right);
    plot->yAxis->setRange(points.bounds.bottom, points.bounds.top);
    plot->xAxis->setTickLabels(false);
    plot->yAxis->setTickLabels(false);

    auto graph = plot->addGraph();
    graph->setData(points.x, points.y);
    graph->setPen(QPen(Qt::black));

    plot->setFixedSize(300, 200);

    this->LBase::addWidget(plot);
    widgets_.push_back(plot);

    plot_count_++;

    this->WBase::setMinimumHeight(200 * plot_count_);
}

//----------------------------------------------------------------

SignalPlot::SignalPlot(QWidget* parent) : WBase(parent) {
    this->WBase::setLayout(static_cast<LBase*>(this));
    this->WBase::setMinimumSize(300, 200);
}

SignalPlot::~SignalPlot() { this->PBase::send({ctrl::mes::SignalDestroyed}); }

void SignalPlot::notify(ctrl::SignalMessage msg) {
    switch (msg.type) {
        case ctrl::mes::SignalDestroyed:
            this->PBase::operator=(nullptr);
            break;
        default:
            std::cout << "SignalPointer " << this
                      << " got unknown message type " << msg.type << std::endl;
    }
}

void SignalPlot::setPointer(ctrl::SignalPointer ptr) {
    this->PBase::operator=(ptr);
}

void SignalPlot::update() { 
    clear_plots();

    const size_t signal_size = this->PBase::getSignal().size();
    for (size_t i = 0; i < signal_size; i++)
        add_plot(this->PBase::getSignal().at(i));
}

void SignalPlot::show() { this->WBase::show(); }

}  // namespace vw