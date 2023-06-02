#ifndef _VIEWS_NAV_BAR_HPP_
#define _VIEWS_NAV_BAR_HPP_

#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QToolButton>
#include <QMdiArea>
#include <QLabel>

namespace vw {

////////////////////////////////////////////////////////////////
// \brief Object that manages the navigation bar.
////////////////////////////////////////////////////////////////
class NavBar : public QToolBar {
 protected:
	using Self = NavBar;
	using Base = QToolBar;
	QMdiArea* workspace_;
	std::list<QWidget*> elements_;
	//std::list<QAction*> actions_;

 public:
	NavBar();
	// Default constructor
	NavBar(QMdiArea* workspace);
	// Destructor
    ~NavBar() override;

	// Adds button to the navigation bar
    void addButton(const std::wstring& label, std::function<void()>&& func = []{});
    // Removes everything in the navigation bar
	void clear();

 private slots:
    void fileClicked();
	void signalInfoClicked();
};


} // namespace vw 

#endif // _VIEWS_NAV_BAR_HPP_