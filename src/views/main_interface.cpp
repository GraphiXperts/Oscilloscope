#include <QFileDialog>
#include <QLabel>
#include <QObject>
#include <cmath>
#include <iostream>
#include <views/main_interface.hpp>
#include <views/plot.hpp>
#include <models/Parsers/Parser.h>

namespace views {

////////////////////////////////////////////////////////////
// Navigation implementation
////////////////////////////////////////////////////////////

Navigation::Navigation(QVBoxLayout* parent) : Base() {
    this->setContentsMargins(5, 5, 5, 5);
    this->setSpacing(5);
    this->setAlignment(Qt::AlignLeft);
}

Navigation::~Navigation() = default;

void Navigation::addButton(const std::string& label,
                           std::function<void()>&& func) {
    QPushButton* button = new QPushButton(label.c_str());

    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setFixedSize(button->sizeHint());

    connect(button, &QPushButton::clicked, func);
    this->addWidget(button);
};

////////////////////////////////////////////////////////////
// MainInterface implementation
////////////////////////////////////////////////////////////

void MainInterface::addPlot() {
    QFileDialog* file_dialog = new QFileDialog(window_);
    QString file_name = file_dialog->getOpenFileName();
    parse::FileParser file_parser;
    models::Signal signal(file_parser.Parse(file_name.toStdString()));

    std::vector<models::Channel>& channels = signal.get_channels();

    for(int i = 0; i < channels.size(); ++i) {
        Plot* window = new Plot("t", "v", this->workspace_);
        window->plot(channels[i]);
        window->show();
    }

}

MainInterface::MainInterface(QMainWindow* window) {
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);

    QWidget* widget = new QWidget();
    widget->setLayout(this);
    window->setCentralWidget(widget);

    workspace_ = new QMdiArea();
    this->addWidget(workspace_);
    workspace_->setStyleSheet("background-color: white;");

    std::cout << "Creating navigation" << std::endl;
    navigation_ = new Navigation();
    std::cout << "Finished creating navigation" << std::endl;

    navigation_->addButton("Open window", [this]{this->addPlot();});

    this->addLayout(navigation_);
    this->addWidget(workspace_);
    window->setLayout(this);
}

MainInterface::~MainInterface() {}

}  // namespace views