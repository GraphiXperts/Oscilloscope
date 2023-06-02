#ifndef _VIEWS_MAIN_INTERFACE_HPP_
#define _VIEWS_MAIN_INTERFACE_HPP_

#include <views/nav_bar.hpp>
#include <views/plots.hpp>
#include <models/signal.hpp>
#include <controllers/signal_list.hpp>
#include <QVBoxLayout>
#include <QMdiArea>
#include <list>

namespace vw {

////////////////////////////////////////////////////////////////
// \brief Object that used to draw interface.
////////////////////////////////////////////////////////////////
class MainInterface : public QVBoxLayout {
 protected:
	using Self = MainInterface;
	using Base = QVBoxLayout;
	
	using WidList = std::list<QWidget*>;

	NavBar nav_bar_;
	QMdiArea workspace_;

 public:
	// Default constructor
	MainInterface(QWidget* parent = nullptr);
	// Destructor
	~MainInterface();

    // Plot signal
	void PlotSignal(ctrl::SignalPointer pointer);
	
};

} // namespace vw

#endif // _VIEWS_MAIN_INTERFACE_HPP_