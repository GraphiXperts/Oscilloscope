#include <views/nav_bar.hpp>
#include<iostream>

namespace vw {

NavBar::NavBar(QWidget* parent){
    QAction* action_file = new QAction("Файл", this);
    QAction* action_view = new QAction("Вид", this);
    QAction* action_tools = new QAction("Инструрменты", this);
    QAction* action_windows = new QAction("Окна", this);

    addAction(action_file);
    addAction(action_view);
    addAction(action_tools);
    addAction(action_windows);

    QMenu *menu_tools = new QMenu(this);
    action_tools->setMenu(menu_tools);

    QAction *item1 = new QAction("Item 1", this);
    QAction *item2 = new QAction("Item 2", this);
    menu_tools->addAction(item1);
    menu_tools->addAction(item2);

    connect(action_file, &QAction::triggered, this, &NavBar::fileClicked);


}

NavBar::~NavBar() {
    for(auto item : elements_) 
        delete item;
    elements_.clear();

    // for (auto item: actions_)
    //     delete item;
    // actions_.clear();
}

void NavBar::fileClicked() {
        // Обработка события активации действия
        qDebug() << "Action activated!";
    }
}
