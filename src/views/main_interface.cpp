#include <views/main_interface.hpp>
#include <controllers/use_cases.hpp>

namespace vw {

////////////////////////////////////////////////////////////////
/// MainInterface implementation
////////////////////////////////////////////////////////////////

MainInterface::MainInterface(QWidget *parent) : Base(parent) {
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);
    
    nav_bar_.addButton(L"Файл", [this](){
        QString filter = tr("*.txt");
        QString file_name = QFileDialog::getOpenFileName(nullptr, QString::fromStdWString(L"Открыть файл"), "", filter);
        auto result = ctrl::addSignalFromFile(file_name.toStdString());

        if (result)
            this->PlotSignal(*result);
        else
            QMessageBox::critical(nullptr, QString::fromStdWString(L"Ошибка"), QString::fromStdWString(L"Не удалось открыть файл"));

    });

    this->addLayout(&nav_bar_);
    this->addWidget(&workspace_);
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