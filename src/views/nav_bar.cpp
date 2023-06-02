#include <views/nav_bar.hpp>
#include<iostream>

namespace vw {

NavBar::NavBar(QWidget* parent = nullptr){
    QAction* action_file = new QAction("Файл", this);
    QAction* action_view = new QAction("Вид", this);
    QAction* action_tools = new QAction("Инструрменты", this);
    QAction* action_windows = new QAction("Окна", this);

    QMenu* menu = new QMenu(this);
    menu->addAction("Информация о канале");
    menu->addAction("Option 2");
    menu->addAction("Option 3");

    action_tools->setMenu(menu);

    addAction(action_file);
    addAction(action_view);
    addAction(action_tools);
    addAction(action_windows);

    QObject::connect(menu, &QMenu::triggered, [&](QAction* action) {
        if (action == menu->actions().at(0)) { // Проверка, что выбрана Option 1
            emit signal_info(); // Вызов сигнала о выборе Option 1
        } else {
            QMessageBox::information(parentWidget(), "Selected Option", action->text());
        }
    });

}

NavBar::~NavBar() {
    for(auto item : elements_) 
        delete item;
    elements_.clear();
}

void NavBar::signal_info() {
    return;
}

}
