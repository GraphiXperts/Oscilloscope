#include <views/main_interface.hpp>
#include <controllers/use_cases.hpp>
#include <QApplication>
#include <QMainWindow>

#include <controllers/modeling.hpp>
int main(int argc, char *argv[]) {
    ctrl::init();
	ctrl::Modeling::delayedSingleImpulse(0, 10,  1, 2, 1);
	QApplication app(argc, argv);

	vw::MainInterface main_interface;

	main_interface.show();
	app.exec();

}