#pragma once

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <iostream>
#include <views/modeling_windows.hpp>
namespace vw {

class ChooseModelWindow : public QDialog
{

public:
    ChooseModelWindow(QWidget *parent = nullptr) : QDialog(parent)
    {
    
    this->setWindowTitle("Выбор модели");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Выберите тип модели:");
    layout->addWidget(titleLabel);

    QPushButton *single_impulse = new QPushButton("Задержанный единочный импульс");
    layout->addWidget(single_impulse);

    QPushButton *single_hop = new QPushButton("Задержанный единичный скачок");
    layout->addWidget(single_hop);

    QPushButton *decreasing_exponent = new QPushButton("Дискретизированная убывающая экспонента");
    layout->addWidget(decreasing_exponent);

    QPushButton *sampled_sine_wave = new QPushButton("Дискретизированная синусоида");
    layout->addWidget(sampled_sine_wave);

    QPushButton *meander = new QPushButton("Меандр");
    layout->addWidget(meander);

    QPushButton *saw = new QPushButton("Пила");
    layout->addWidget(saw);

    QPushButton *exponential_envelope = new QPushButton("Сигнал с экспоненциальной огибающей");
    layout->addWidget(exponential_envelope);

    QPushButton *balance_envelope = new QPushButton("Сигнал с балансной огибающей");
    layout->addWidget(balance_envelope);

    QPushButton *tonal_envelope = new QPushButton("Сигнал с тональной огибающей");
    layout->addWidget(tonal_envelope);

    QPushButton *lfm = new QPushButton("Сигнал с линейной частотной модуляцией");
    layout->addWidget(lfm);

    layout->addSpacing(20);

    QPushButton *submitButton = new QPushButton("Закрыть");
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &ChooseModelWindow::submitOptions);
    connect(single_impulse, &QPushButton::clicked, this, &ChooseModelWindow::handleSingleImpulsClicked);
    connect(single_hop, &QPushButton::clicked, this, &ChooseModelWindow::handleSingleHopClicked);
    connect(decreasing_exponent, &QPushButton::clicked, this, &ChooseModelWindow::handleDecreasingExponentClicked);
    connect(sampled_sine_wave, &QPushButton::clicked, this, &ChooseModelWindow::handleSampledSineWaveClicked);
    connect(meander, &QPushButton::clicked, this, &ChooseModelWindow::handleMeanderClicked);
    connect(saw, &QPushButton::clicked, this, &ChooseModelWindow::handleSawClicked);
    connect(exponential_envelope, &QPushButton::clicked, this, &ChooseModelWindow::handleExponentialEnvelopeClicked);
    connect(balance_envelope, &QPushButton::clicked, this, &ChooseModelWindow::handleBalanceEnvelopeClicked);
    connect(tonal_envelope, &QPushButton::clicked, this, &ChooseModelWindow::handleTonalEnvelopeClicked);
    connect(lfm, &QPushButton::clicked, this, &ChooseModelWindow::handleLFMClicked);

    }

    private slots:
    void submitOptions(){
        accept();
    }

    void handleSingleImpulsClicked() {
        accept();
        SingleImpulse single_impulse;
        single_impulse.exec();
    }
    void handleSingleHopClicked() {
        accept();
        SingleHop single_hop;
        single_hop.exec();
    }
    void handleDecreasingExponentClicked() {
        accept();
        DecreasingExponent decreasing_exponent;
        decreasing_exponent.exec();
    }
    void handleSampledSineWaveClicked() {
        accept();
        SampledSineWave sampled_sine_wave;
        sampled_sine_wave.exec();
    }
    void handleMeanderClicked() {
        accept();
        Meander meander;
        meander.exec();
    }
    void handleSawClicked() {
        accept();
        Saw saw;
        saw.exec();
    }
    void handleExponentialEnvelopeClicked() {
        accept();
        ExponentialEnvelope exponential_envelope_window;
        exponential_envelope_window.exec();
    }
    void handleBalanceEnvelopeClicked() {
        accept();
        BalanceEnvelope balance_envelope;
        balance_envelope.exec();
    }
    void handleTonalEnvelopeClicked() {
        accept();
        TonalEnvelope tonal_envelope;
        tonal_envelope.exec();
    }
    void handleLFMClicked() {
        accept();
        LFM lfm;
        lfm.exec();
    }

};
} // namespace vw


