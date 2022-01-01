#ifndef GUI_GUARD
#define GUI_GUARD

#include "Point.h"
#include "fltk.h"
#include "Window.h"
#include "Graph.h"
//#include<vector>
//#include<string>

namespace Graph_lib {
	
typedef void* Address;
typedef void (*Callback)(Address,Address);	// FLTK's required function type for all callbacks

template<class W> W& reference_to(Address pw)
	// treat an address as a reference to a W
{
		return *static_cast<W*>(pw);
}


class Widget {
	// Widget is a handle to a Fl_widget - it is *not* a Fl_widget
	// We try to keep our interface classes at arm's length from FLTK
public:
	Widget(Point xy, int w, int h, const string& s, Callback cb)
		:loc(xy), width(w), height(h), label(s), do_it(cb)
	{ }

	virtual void move(int dx,int dy) { hide(); pw->position(loc.x+=dx, loc.y+=dy); show(); }
	virtual void hide() { pw->hide(); }
	virtual void show() { pw->show(); }
	virtual void attach(Window&) = 0;	// each Widgit define at least one action for a window

	Point loc;
	int width;
	int height;
	string label;
	Callback do_it;

	virtual ~Widget() { }

	/*
	Widget(const Widget& a) :loc(a.loc) { error("attempt to copy Widget by constructor"); }
	Widget& operator=(const Widget& a)
	{
			error("attempt to copy Widget by cassignment");
			return *this;
	}
	*/

protected:
	Window* own;	// every Widget belongs to a Window
	Fl_Widget* pw;
private:
	Widget& operator=(const Widget&) = delete;	// don't copy Widgets
	Widget(const Widget&);
};

class Button : public Widget {
public:
	Button(Point xy, int ww, int hh, const string& s, Callback cb)
	:Widget(xy,ww,hh,s,cb)
	{ 
	}
	void attach(Window& win);
};

}
#endif

