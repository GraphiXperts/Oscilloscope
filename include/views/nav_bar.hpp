#ifndef _VIEWS_NAV_BAR_HPP_
#define _VIEWS_NAV_BAR_HPP_

#include <QHBoxLayout>
#include <list>
#include <string>
#include <functional>

namespace vw {

////////////////////////////////////////////////////////////////
// \brief Object that manages the navigation bar.
////////////////////////////////////////////////////////////////
class NavBar : public QHBoxLayout {
 protected:
    using Self = NavBar;
    using Base = QHBoxLayout;

	std::list<QWidget*> elements_;

 public:
	// Default constructor
	NavBar();
	// Constructor with parent
	explicit NavBar(QBoxLayout* parent);
	// Destructor
    ~NavBar() override;

	// Adds button to the navigation bar
    void addButton(const std::wstring& label, std::function<void()>&& func = []{});
    // Removes everything in the navigation bar
	void clear();
};


} // namespace vw 

#endif // _VIEWS_NAV_BAR_HPP_