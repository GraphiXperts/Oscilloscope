#include <views/main_interface.hpp>
#include <controllers/use_cases.hpp>

namespace vw {

////////////////////////////////////////////////////////////////
/// MainInterface implementation
////////////////////////////////////////////////////////////////

MainInterface::MainInterface() {

    NavBar* nav_bar = new NavBar();

    this->addToolBar(nav_bar);


    // this->addLayout(&nav_bar_);
    // this->addWidget(&workspace_);
}

MainInterface::~MainInterface() = default;

void MainInterface::PlotSignal(ctrl::SignalPointer pointer) {
    SignalPlot* plot = new SignalPlot(&workspace_); 
    plot->setPointer(pointer);
    plot->show();
}


} // namespace vw