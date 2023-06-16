#pragma once

#include <QDebug>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

namespace vw {

class SingleImpulse: public QDialog
{
public:
    SingleImpulse(QWidget *parent = nullptr)
        : QDialog(parent) {
        
        setWindowTitle("Задержанный единичный импульс");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *delay_impulse = new QLabel("Задержка импульса");
        delay_impulse_edit = new QLineEdit;
        formLayout->addRow(delay_impulse, delay_impulse_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &SingleImpulse::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString delay_impulse = delay_impulse_edit->text();
            QString time_step = time_step_edit->text();

            num_sample_edit->clear();
            delay_impulse_edit->clear();
            time_step_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *delay_impulse_edit;
};

class SingleHop: public QDialog
{
public:
    SingleHop(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Задержанный единичный скачок");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *delay_impulse = new QLabel("Задержка импульса");
        delay_impulse_edit = new QLineEdit;
        formLayout->addRow(delay_impulse, delay_impulse_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &SingleHop::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString delay_impulse = delay_impulse_edit->text();
            QString time_step = time_step_edit->text();

            num_sample_edit->clear();
            time_step_edit->clear();
            delay_impulse_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *delay_impulse_edit;
    QLineEdit *time_step_edit;
};

class DecreasingExponent: public QDialog
{
public:
    DecreasingExponent(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Дискретизированная убывающая экспонента");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &DecreasingExponent::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString amplitude = amplitude_edit->text();
            QString time_step = time_step_edit->text();

            num_sample_edit->clear();
            time_step_edit->clear();
            amplitude_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *amplitude_edit;
};


class SampledSineWave: public QDialog
{
public:
    SampledSineWave(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Дискретизированная синусоида");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);

        QLabel *circle_freq = new QLabel("Круговая частота");
        circle_freq_edit = new QLineEdit;
        formLayout->addRow(circle_freq, circle_freq_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &SampledSineWave::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString time_step = time_step_edit->text();
            QString amplitude = amplitude_edit->text();
            QString circle_freq = circle_freq_edit->text();

            num_sample_edit->clear();
            time_step_edit->clear();
            amplitude_edit->clear();
            circle_freq_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *numtime_freq_end_editlitude_edit;
    QLineEdit *circle_freq_edit;
};

class Meander: public QDialog
{
public:
    Meander(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Меаднр");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *period = new QLabel("Период");
        period_edit = new QLineEdit;
        formLayout->addRow(period, period_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &Meander::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString time_step = time_step_edit->text();
            QString period = period_edit->text();

            num_sample_edit->clear();
            time_step_edit->clear();
            period_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *period_edit;
};

class Saw: public QDialog
{
public:
    Saw(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Пила");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *period = new QLabel("Период");
        period_edit = new QLineEdit;
        formLayout->addRow(period, period_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &Saw::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString period = period_edit->text();

            num_sample_edit->clear();
            period_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *period_edit;
};


class ExponentialEnvelope: public QDialog
{
public:
    ExponentialEnvelope(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Cигнал с экспоненциальной огибающей");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *time_freq = new QLabel("Частота");
        time_freq_edit = new QLineEdit;
        formLayout->addRow(time_freq, time_freq_edit);

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
        QString time_freq = time_freq_edit->text();
        QString amplitude = amplitude_edit->text();
        QString env_width = env_width_edit->text();
        QString freq = freq_edit->text();
        QString phase = phase_edit->text();
        // Обработка введенных данных

        // Очистка полей ввода
        num_sample_edit->clear();
        time_step_edit->clear();
        time_freq_edit->clear();
        amplitude_edit->clear();
        env_width_edit->clear();
        freq_edit->clear();
        phase_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *time_freq_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *env_width_edit;
    QLineEdit *freq_edit;
    QLineEdit *phase_edit;

};

class BalanceEnvelope: public QDialog
{
public:
    BalanceEnvelope(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Cигнал с балансной огибающей");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *time_freq = new QLabel("Частота");
        time_freq_edit = new QLineEdit;
        formLayout->addRow(time_freq, time_freq_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);
        
        QLabel *env_freq = new QLabel("Частота огибающей,");
        env_freq_edit = new QLineEdit;
        formLayout->addRow(env_freq, env_freq_edit);

        QLabel *freq = new QLabel("Частота несущей");
        freq_edit = new QLineEdit;
        formLayout->addRow(freq, freq_edit);

        QLabel *phase = new QLabel("Начальная фаза несущей");
        phase_edit = new QLineEdit;
        formLayout->addRow(phase, phase_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &BalanceEnvelope::handleButtonClick);
        
    }

private slots:
    void handleButtonClick() {
        QString num_sample = num_sample_edit->text();
        QString time_step = time_step_edit->text();
        QString time_freq = time_freq_edit->text();
        QString amplitude = amplitude_edit->text();
        QString env_freq = env_freq_edit->text();
        QString freq = freq_edit->text();
        QString phase = phase_edit->text();
        // Обработка введенных данных

        // Очистка полей ввода
        num_sample_edit->clear();
        time_step_edit->clear();
        time_freq_edit->clear();
        amplitude_edit->clear();
        env_freq_edit->clear();
        freq_edit->clear();
        phase_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *time_freq_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *env_freq_edit;
    QLineEdit *freq_edit;
    QLineEdit *phase_edit;

};

class TonalEnvelope: public QDialog
{
public:
    TonalEnvelope(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Сигнал с тональной огибающей");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *time_freq = new QLabel("Частота");
        time_freq_edit = new QLineEdit;
        formLayout->addRow(time_freq, time_freq_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);

        QLabel *mod_depth = new QLabel("Индекс глубины модуляции ");
        mod_depth_edit = new QLineEdit;
        formLayout->addRow(mod_depth, mod_depth_edit);

        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &TonalEnvelope::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString time_step = time_step_edit->text();
            QString time_freq = time_freq_edit->text();
            QString amplitude = amplitude_edit->text();
            QString mod_depth = mod_depth_edit->text();

            num_sample_edit->clear();
            time_step_edit->clear();
            time_freq_edit->clear();
            amplitude_edit->clear();
            mod_depth_edit->clear();
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *time_freq_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *mod_depth_edit;
};

class LFM: public QDialog
{
public:
    LFM(QWidget *parent = nullptr)
        : QDialog(parent) {

        setWindowTitle("Сигнал с линейной частотной модуляцией");
        resize(600, 300);

        // Создание формы для ввода данных
        QFormLayout *formLayout = new QFormLayout(this);

        QLabel *num_samples = new QLabel("Колличество отсчётов");
        num_sample_edit = new QLineEdit;
        formLayout->addRow(num_samples, num_sample_edit);

        QLabel *time_step = new QLabel("Временной шаг");
        time_step_edit = new QLineEdit;
        formLayout->addRow(time_step, time_step_edit);

        QLabel *time_freq_start = new QLabel("Частота в начальный момент времени");
        time_freq_start_edit = new QLineEdit;
        formLayout->addRow(time_freq_start, time_freq_start_edit);

        QLabel *time_freq_end = new QLabel("Частота в конечный момент времени");
        time_freq_end_edit = new QLineEdit;
        formLayout->addRow(time_freq_end, time_freq_end_edit);

        QLabel *amplitude = new QLabel("Амплитуда");
        amplitude_edit = new QLineEdit;
        formLayout->addRow(amplitude, amplitude_edit);

        QLabel *phase_start = new QLabel("Начальная фаза");
        phase_start_edit = new QLineEdit;
        formLayout->addRow(phase_start, phase_start_edit);


        QPushButton *submitButton = new QPushButton("Отправить");
        formLayout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &LFM::handleButtonClick);
        }

    private slots:
        void handleButtonClick() {
            QString num_sample = num_sample_edit->text();
            QString time_step = time_step_edit->text();
            QString time_freq_start = time_freq_start_edit->text();
            QString time_freq_end = time_freq_end_edit->text();
            QString amplitude = amplitude_edit->text();
            QString phase_start = phase_start_edit->text();
        

            num_sample_edit->clear();
            time_step_edit->clear();
            time_freq_start_edit->clear();
            time_freq_end_edit->clear();
            amplitude_edit->clear();
            phase_start_edit->clear();
            
    }

private:
    QLineEdit *num_sample_edit;
    QLineEdit *time_step_edit;
    QLineEdit *time_freq_start_edit;
    QLineEdit *time_freq_end_edit;
    QLineEdit *amplitude_edit;
    QLineEdit *phase_start_edit;
    
};

} //namespace
