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
        points.add(el.time, el.value);
    
    return points;
}

////////////////////////////////////////////////////////////////
/// ChannelPlot implementation
////////////////////////////////////////////////////////////////

ChannelPlot::ChannelPlot(QWidget* parent) : WBase(parent) {
    QWidget* widget = new QWidget();
    this->WBase::setWidget(widget);
    this->WBase::setMinimumSize(300, 200);
    widget->setLayout(static_cast<LBase*>(this));
    this->LBase::setSpacing(0);
    this->LBase::setContentsMargins(0, 0, 0, 0);
}

ChannelPlot::~ChannelPlot() {
    this->PBase::send({ctrl::mes::PointerDestroyed}); 
}

void ChannelPlot::notify(ctrl::SignalMessage msg) {
    switch (msg.type) {
        case ctrl::mes::SignalDestroyed:
            this->PBase::operator=(nullptr);
            break;
        default:
            std::cout << "SignalPointer " << this
                      << " got unknown message type " << msg.type << std::endl;
    }
}

void ChannelPlot::setPointer(ctrl::SignalPointer ptr) {
    this->PBase::operator=(ptr);
}

void ChannelPlot::setChannel(const mdl::Channel& channel) {
    channel_ = &channel;
}

void ChannelPlot::update() {
    QCustomPlot* plot = new QCustomPlot();

    auto res = channel_->range(0, channel_->size() - 1);
    Points points = getPoints(*res);

    plot->xAxis->setRange(points.bounds.left, points.bounds.right);
    plot->yAxis->setRange(points.bounds.bottom, points.bounds.top);
    plot->xAxis->setLabel("t");
    plot->yAxis->setLabel("v");

    auto graph = plot->addGraph();
    graph->setData(points.x, points.y);
    graph->setPen(QPen(Qt::black));

    plot->setMinimumSize(150, 60);

    this->LBase::addWidget(plot);
    plot->replot();

}

void ChannelPlot::show() {
    this->WBase::show();
}

////////////////////////////////////////////////////////////////
/// SignalPlot implementation
////////////////////////////////////////////////////////////////

void SignalPlot::clear_plots() {
    plot_count_ = 0;
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
    plot->xAxis->setVisible(false);

    plot->axisRect()->setAutoMargins(QCP::msNone);
    plot->axisRect()->setMargins(QMargins(0, 0, 0, 0));

    auto graph = plot->addGraph();
    graph->setData(points.x, points.y);
    graph->setPen(QPen(Qt::black));

    QCPItemText* text = new QCPItemText(plot);
    text->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
    text->position->setType(QCPItemPosition::ptAxisRectRatio);
    text->position->setCoords(0.03, 1);
    text->setText(QString::fromStdWString(channel.name()));

    plot->setMinimumSize(150, 60);

    this->LBase::addWidget(plot);
    plot->replot();

    QObject::connect(plot, &QCustomPlot::mousePress, [&channel, this]{
        ChannelPlot* plot = new ChannelPlot();
        plot->setPointer(*this);
        plot->setChannel(channel);
        plot->update();
        click_(plot);
    });

    widgets_.push_back(plot);

    plot_count_++;

    this->WBase::setMinimumHeight(60 * plot_count_);
}

//----------------------------------------------------------------

SignalPlot::SignalPlot(QWidget* parent) : WBase(parent) {
    QWidget* widget = new QWidget();
    this->WBase::setWidget(widget);
    this->WBase::setMinimumWidth(150);
    widget->setLayout(static_cast<LBase*>(this));
    this->LBase::setSpacing(2);
    this->LBase::setContentsMargins(1, 1, 1, 1);
}

SignalPlot::~SignalPlot() { 
    this->PBase::send({ctrl::mes::PointerDestroyed}); 
}

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
    update();
}

void SignalPlot::setClickCallback(std::function<void(ChannelPlot*)>&& cb) {
    click_ = std::move(cb);
}

void SignalPlot::update() { 
    clear_plots();

    const size_t signal_size = this->PBase::getSignal().size();
    for (size_t i = 0; i < signal_size; i++)
        add_plot(this->PBase::getSignal().at(i));

    show();
}

void SignalPlot::show() { this->WBase::show(); }



}  // namespace vw