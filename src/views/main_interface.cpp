#include <views/main_interface.hpp>
#include <controllers/use_cases.hpp>

namespace vw {

////////////////////////////////////////////////////////////////
/// MainInterface implementation
////////////////////////////////////////////////////////////////

MainInterface::MainInterface() {

    NavBar* nav_bar = new NavBar(&this->workspace_);

    this->addToolBar(nav_bar);
    this->setCentralWidget(&workspace_);
}

MainInterface::~MainInterface() = default;

void MainInterface::PlotSignal(ctrl::SignalPointer pointer) {
    SignalPlot* plot = new SignalPlot(&workspace_); 
    plot->setPointer(pointer);
    plot->setClickCallback([this](ChannelPlot* plot){
        workspace_.addSubWindow(plot);
        plot->show();
    });
    plot->show();
}


} // namespace vw