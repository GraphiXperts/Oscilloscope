#pragma once

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <map>

namespace vw {

class ExponentialEnvelope: public QDialog
{
public:
    ExponentialEnvelope(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Моделирование");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        // QLabel *time_freq = new QLabel("Частота");
        // time_freq_edit = new QLineEdit;
        // formLayout->addRow(time_freq, time_freq_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);
        
        QLabel *env_width = new QLabel("Параметр ширины огибающей");
        env_width_edit = new QLineEdit;
        formLayout->addRow(env_width, env_width_edit);

        QLabel *freq = new QLabel("Частота несущей");
        freq_edit = new QLineEdit;
        formLayout->addRow(freq, freq_edit);

        QLabel *phase = new QLabel("Начальная фаза несущей");
        phase_edit = new QLineEdit;
        formLayout->addRow(phase, phase_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &ExponentialEnvelope::handleButtonClick);
    }

private slots:
    void handleButtonClick() {
        QString num_sample = num_sample_edit->text();
        QString time_step = time_step_edit->text();
        // QString time_freq = time_freq_edit->text();
        QString amplitude = amplitude_edit->text();
        QString env_width = env_width_edit->text();
        QString freq = freq_edit->text();
        QString phase = phase_edit->text();
        // Обработка введенных данных

        // Очистка полей ввода
        num_sample_edit->clear();
        time_step_edit->clear();
        // time_freq_edit->clear();
        amplitude_edit->clear();
        env_width_edit->clear();
        freq_edit->clear();
        phase_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    // QLineEdit *time_freq_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *env_width_edit;
    QLineEdit *freq_edit;
    QLineEdit *phase_edit;

};



} //namespace
