#include "GUI.h"
using namespace Graph_lib;

#define draw attach

struct Simple_window : Window {
	Simple_window(Point xy, int w, int h, const string& title, Point init = Point{ 0, 0 })
		: Window{ xy, w, h, title },
		button_pushed{ false },
		next_button{ Point{ x_max() - 70, 0 }, 70, 20, "Next", cb_next },
		current_point{ init }
	{
		attach(next_button);
	}

	void wait_for_button()
	{
		while (!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}

	Point current() { return current_point; }
	void current(Point p) { current_point = p; }
private:
	Point current_point;
	
	Button next_button;
	bool button_pushed;

	static void cb_next(Address, Address addr)
	{
		static_cast<Simple_window*>(addr)->next();
	}

	void next() { button_pushed = true; }
};