#include "GUI.h"
#include "std_lib_facilities.h"
#include <sstream>

using namespace Graph_lib;


void Button::attach(Window& win)
	{
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
		own = &win;
	}