#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QLabel>
#include <views/main_interface.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;

    views::MainInterface main_interface(&window);

    window.show();

    return app.exec();
}
