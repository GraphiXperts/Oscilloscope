#ifndef _VIEWS_MODELING_HPP_
#define _VIEWS_MODELING_HPP_
#include <QDialog>

//TODO: Перенести в CPP файл
namespace vw {
class ModelingWindow : public QDialog
{
public:
    ModelingWindow(QWidget *parent = nullptr)
        : QDialog(parent) {
    
        setWindowTitle("Моделирование");

        resize(600, 400);

        // Создание других элементов интерфейса, добавление их на окно
        // ...

        // Пример привязки сигнала к слоту
        //connect(button, &QPushButton::clicked, this, &SecondaryWindow::handleButtonClick);
    }

private slots:
    void handleButtonClick() {
        // Обработка события нажатия на кнопку
    }

private:
    // Декларация элементов интерфейса, таких как кнопки, текстовые поля и т.д.
    // ...
};

} // namespace vw
#endif // _VIEWS_MODELING_HPP_
