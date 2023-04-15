#ifndef _VIEWS_MAIN_INTERFACE_HPP_
#define _VIEWS_MAIN_INTERFACE_HPP_

#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QVBoxLayout>

namespace views {

class Navigation : public QHBoxLayout {
 protected:
    using Self = Navigation;
    using Base = QHBoxLayout;

 public:
    Navigation(QVBoxLayout* parent = nullptr);
    ~Navigation() override;

    void addButton(const std::string& label, std::function<void()>&& func = []{});
};

class MainInterface : public QVBoxLayout {
 protected:
    using Self = MainInterface;
    using Base = QVBoxLayout;

    Navigation* navigation_;
    QMdiArea* workspace_;
    QMainWindow* window_;

    void addPlot();

 public:
    MainInterface(QMainWindow *main_window);
    ~MainInterface();
};

}  // namespace views

#endif