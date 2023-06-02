#ifndef _VIEWS_PLOTS_HPP_
#define _VIEWS_PLOTS_HPP_

#include <qcustomplot.h>

#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <controllers/signal_list.hpp>
#include <models/signal.hpp>
#include <string>

namespace vw {

////////////////////////////////////////////////////////////////
// \brief Object that contains bounds of any object.
////////////////////////////////////////////////////////////////
struct Bounds {
    double top;
    double bottom;
    double right;
    double left;

    // Default constructor
    Bounds();
    // Constructor from values
    Bounds(double top, double bottom, double right, double left);
    // Constructor from position
    Bounds(double x, double y);
    // Copy constructor
    Bounds(const Bounds& other);
    // Move constructor
    Bounds(Bounds&& other);
    // Destructor
    ~Bounds();

    // Binary operators

    // Sum of two bounds
    Bounds operator+(const Bounds& other) const;
    // Sum assignment
    Bounds& operator+=(const Bounds& other);

    // Assignment operator

    // Copy assignment operator
    Bounds& operator=(const Bounds& other);
    // Move assignment operator
    Bounds& operator=(Bounds&& other);

};

////////////////////////////////////////////////////////////////
// \brief Vector of points
////////////////////////////////////////////////////////////////
struct Points {
    Bounds bounds;

    QVector<double> x;  // x positions
    QVector<double> y;  // y positions

    // Add a point
    void add(double x, double y);
    // Resize the vector to the given size
    void resize(size_t count);
    // Clear the vector
    void clear();
    // Get size
    size_t size() const;
};

Points getPoints(mdl::Range range);

////////////////////////////////////////////////////////////////
// \brief Channel plot.
////////////////////////////////////////////////////////////////

class ChannelPlot : public QMdiSubWindow,
                    public QVBoxLayout,
                    public ctrl::SignalPointer {
 protected:
    using Self  = ChannelPlot;
    using WBase = QMdiSubWindow;
    using LBase = QVBoxLayout;
    using PBase = ctrl::SignalPointer;

    using WidgetList = std::list<QWidget*>;
    
    const mdl::Channel* channel_;

 public:
    // Default constructor
    ChannelPlot(QWidget* parent = nullptr);
    // Destructor
    ~ChannelPlot() override;

    // Notify from signal
    void notify(ctrl::SignalMessage mes) override;
    // Set pointer to signal
    void setPointer(ctrl::SignalPointer ptr);
    // Set reference to channel
    void setChannel(const mdl::Channel& channel);
    // Update plot
    void update();
    // Show
    void show();
    
}; 

////////////////////////////////////////////////////////////////
// \brief Object that plots signals
////////////////////////////////////////////////////////////////
class SignalPlot : public QMdiSubWindow,
                   public QVBoxLayout,
                   public ctrl::SignalPointer {
 private:
    using Self  = SignalPlot;
    using WBase = QMdiSubWindow;
    using LBase = QVBoxLayout;
    using PBase = ctrl::SignalPointer;

    using WidgetList = std::list<QWidget*>;

    size_t plot_count_;
    WidgetList widgets_;
    std::function<void(ChannelPlot*)> click_;

    void clear_plots();
    void add_plot(const mdl::Channel& channel);

 public:
    // Default constructor
    SignalPlot(QWidget* parent = nullptr);
    // Destructor
    ~SignalPlot() override;

    // Notify from signal
    void notify(ctrl::SignalMessage mes) override;
    // Set pointer to signal
    void setPointer(ctrl::SignalPointer ptr);
    // Set click callback
    void setClickCallback(std::function<void(ChannelPlot*)>&& cb);
    // Update plot
    void update();
    // Show
    void show();
};



}  // namespace vw

#endif  // _VIEWS_PLOTS_HPP_