#ifndef _VIEWS_NAV_BAR_HPP_
#define _VIEWS_NAV_BAR_HPP_

#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMessageBox>


namespace vw {

////////////////////////////////////////////////////////////////
// \brief Object that manages the navigation bar.
////////////////////////////////////////////////////////////////
class NavBar : public QToolBar {
 protected:
	using Self = NavBar;
	using Base = QToolBar;

	std::list<QWidget*> elements_;
	//std::list<QAction*> actions_;

 public:
	// Default constructor
	NavBar(QWidget* parent = nullptr);
	// Destructor
    ~NavBar() override;

	// Adds button to the navigation bar
    void addButton(const std::wstring& label, std::function<void()>&& func = []{});
    // Removes everything in the navigation bar
	void clear();

 private slots:
    void fileClicked();

};


} // namespace vw 

#endif // _VIEWS_NAV_BAR_HPP_