#include "Graph.h"

namespace Graph_lib {
	void Shape::draw_lines() const
	{
		if (color().visibility() && 1 < points.size())
			for (unsigned int i = 1; i < points.size(); ++i)
				fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}

	void Shape::draw() const
	{
		Fl_Color oldc = fl_color();
		fl_color(lcolor.as_int());
		fl_line_style(ls.style(), ls.width());
		draw_lines();
		fl_color(oldc);
		fl_line_style(0);
	}

	void Text::draw_lines() const
	{
		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(), fnt_sz);
		fl_draw(lab.c_str(), point(0).x, point(0).y);
		fl_font(ofnt, osz);
	}

	void Rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x, point(0).y, _w, _h);
			fl_color(color().as_int());
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, _w, _h);
		}
	}

	void Circle::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, _r + _r - 1, _r + _r - 1, 0, 360);
			fl_color(color().as_int());
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, _r + _r, _r + _r, 0, 360);
		}
	}
}