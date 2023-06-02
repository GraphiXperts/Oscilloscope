#include <QPushButton>
#include <QObject>
#include <views/nav_bar.hpp>

namespace vw {

////////////////////////////////////////////////////////////////
/// NavBar implementation
////////////////////////////////////////////////////////////////

NavBar::NavBar() {
	this->setContentsMargins(5, 5, 5, 5);
    this->setSpacing(5);
    this->setAlignment(Qt::AlignLeft);
}

NavBar::NavBar(QBoxLayout* parent) { 
	parent->addLayout(this); 
	this->setContentsMargins(5, 5, 5, 5);
    this->setSpacing(5);
    this->setAlignment(Qt::AlignLeft);
}

NavBar::~NavBar() = default;

void NavBar::addButton(const std::wstring& title,
                       std::function<void()>&& func) {
    QPushButton* button = new QPushButton(QString::fromStdWString(title));

	button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setFixedSize(button->sizeHint());

    QObject::connect(button, &QPushButton::clicked, func);

    this->addWidget(button);
    elements_.push_back(button);
}

void NavBar::clear() {
	for(auto el : elements_)
        delete el;
    elements_.clear();
}

}  // namespace vw