#include <views/main_interface.hpp>
#include <controllers/use_cases.hpp>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    ctrl::init();

	QApplication app(argc, argv);

	vw::MainInterface main_interface;

	main_interface.show();
	app.exec();

}