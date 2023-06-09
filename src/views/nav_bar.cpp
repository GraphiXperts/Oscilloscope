#include <views/nav_bar.hpp>
#include <iostream>
#include <controllers/use_cases.hpp>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <views/plots.hpp>
#include <views/modeling_choose.hpp>
namespace vw {

NavBar::NavBar(QMdiArea* workspace): workspace_(workspace){ 
    QAction* action_file = new QAction("Файл", this);
    
    addAction(action_file);

    QToolButton *toolButton = new QToolButton(this);
    toolButton->setPopupMode(QToolButton::InstantPopup);
    toolButton->setText("Инструменты");
    addWidget(toolButton);
    QMenu *menu_tools = new QMenu(this);
    toolButton->setMenu(menu_tools);

    QAction *signal_info = new QAction("Информация о сигнале", this);
    QAction *modeling = new QAction("Моделирование", this);
    menu_tools->addAction(signal_info);
    menu_tools->addAction(modeling);

    // привязка элементов навбара к ебучим функциям обработки событий
    connect(action_file, &QAction::triggered, this, &NavBar::fileClicked);
    connect(signal_info, &QAction::triggered, this, &NavBar::signalInfoClicked);
    connect(modeling, &QAction::triggered, this, &NavBar::modelingClicked);
}

NavBar::~NavBar() {
    for(auto item : elements_) 
        delete item;
    elements_.clear();

    // for (auto item: actions_)
    //     delete item;
    // actions_.clear();
}
// Обработка события активации действия "Файл"
void NavBar::fileClicked() {    
        QString filter = tr("*.txt");
        QString file_name = QFileDialog::getOpenFileName(nullptr, QString::fromStdWString(L"Открыть файл"), "", filter);
        auto result = ctrl::addSignalFromFile(file_name.toStdString());
        
        if (result) {
            SignalPlot* plot = new SignalPlot(workspace_); 
            plot->setPointer(*result);
            plot->setClickCallback([this](ChannelPlot* plot){
                workspace_->addSubWindow(plot);
                plot->show();
            });
            plot->show();
        }
            
        else
            QMessageBox::critical(nullptr, QString::fromStdWString(L"Ошибка"), QString::fromStdWString(L"Не удалось открыть файл"));

    }

QString formatInfoString(mdl::Signal& signal) {
    
    std::string info;
    auto start_time = mdl::localtime(signal.info().start_time);
    auto end_time = mdl::localtime(signal.info().finish_time);
    auto duration = signal.info().finish_time - signal.info().start_time;



    int days = floor(duration / 86400);
    int hours =  floor((duration - days * 24 * 60) / 3600);
    int minutes = floor((duration - days * 24 * 60 - hours * 60) / 60);
    double seconds = duration - days * 24 * 60 - hours * 60 - minutes * 60;


    info += "Число каналов: " + std::to_string(signal.info().channel_count) + "\n";
    info += "Общее количество отчётов: " + std::to_string(signal.info().sample_count) +"\n";
    info += "Частота дискретизации(Гц): " + std::to_string(signal.info().max_frequency) + " ";
    info += "(шаг между отчётами " + std::to_string( 1.0 / signal.info().max_frequency) + " сек)\n";

    info += "Дата и время начала записи: " + std::to_string(start_time.tm_mday) + "-" + std::to_string(start_time.tm_mon + 1) + "-" + std::to_string(start_time.tm_year + 1900) + " ";
    info += std::to_string(start_time.tm_hour) + ":" + std::to_string(start_time.tm_min) + ":" + std::to_string(start_time.tm_sec) + "\n";

    info += "Дата и время окончания записи: " + std::to_string(end_time.tm_mday) + "-" + std::to_string(end_time.tm_mon + 1) + "-" + std::to_string(end_time.tm_year + 1900) + " ";
    info += std::to_string(end_time.tm_hour) + ":" + std::to_string(end_time.tm_min) + ":" + std::to_string(end_time.tm_sec) + "\n";

    
    info += "Длительность: " + std::to_string( seconds ) + " - суток " + std::to_string(hours) + " - часов " + std::to_string(minutes) + " - минут " + std::to_string(seconds) + " - секунд\n";

    return QString::fromStdString(info);
}

void NavBar::signalInfoClicked() {
    auto result = ctrl::getSignal();
    if (!result) {
        QMessageBox::critical(this, "СМЭРТЬ", QString::fromStdString(result.m()));
    } else {
        
        auto& signal = result->getSignal();
        QMdiSubWindow* sub_window = new QMdiSubWindow();
        workspace_->addSubWindow(sub_window);
        
        QLabel* signal_info = new QLabel();
        // Необходимо изменять размер у sub_window!
        sub_window->setStyleSheet("QLabel { margin-top: 50px; }");
        sub_window->setMinimumSize(500, 200); 
        signal_info->setText(formatInfoString(signal));
        signal_info->adjustSize();

        sub_window->setWidget(signal_info);
        sub_window->show();
    }

}

void NavBar::modelingClicked() {
    ChooseModelWindow secondaryWindow;
    secondaryWindow.exec();
}

NavBar::NavBar() = default; //xdd
}// namespace vw


