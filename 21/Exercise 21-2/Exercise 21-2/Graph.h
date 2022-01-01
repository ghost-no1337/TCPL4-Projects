#pragma once
#include "Point.h"
#include "fltk.h"
#include "std_lib_facilities.h"

namespace Graph_lib {
	struct Color {
		enum Color_type {
			red = FL_RED, blue = FL_BLUE, green = FL_GREEN,
			yellow = FL_YELLOW, white = FL_WHITE, black = FL_BLACK,
			magenta = FL_MAGENTA, cyan = FL_CYAN, dark_red = FL_DARK_RED,
			dark_green = FL_DARK_GREEN, dark_yellow = FL_DARK_YELLOW, dark_blue = FL_DARK_BLUE,
			dark_magenta = FL_DARK_MAGENTA, dark_cyan = FL_DARK_CYAN
		};

		enum Transparency : unsigned char { invisible = 0, visible = 255 };

		Color(Color_type cc) :c{ Fl_Color(cc) }, v{ visible } { }
		Color(Color_type cc, Transparency vv) :c{ Fl_Color(cc) }, v{ vv } { }
		Color(int cc) :c{ Fl_Color(cc) }, v{ visible } { }
		Color(Transparency vv) :c{ Fl_Color() }, v{ vv } { }

		int as_int() const { return c; }
		char visibility() const { return v; }
		void set_visibility(Transparency vv) { v = vv; }
	private:
		unsigned char v;
		Fl_Color c;
	};

	struct Line_style {
		enum Line_style_type {
			solid = FL_SOLID,				// -------
			dash = FL_DASH,			    	// - - - -
			dot = FL_DOT,					// ....... 
		};
		Line_style(Line_style_type ss) :s{ ss }, w{ 0 } { }
		Line_style(Line_style_type lst, int ww) :s{ lst }, w{ ww } { }
		Line_style(int ss) :s{ ss }, w{ 0 } { }

		int width() const { return w; }
		int style() const { return s; }
	private:
		int s;
		int w;
	};

	class Font {
	public:
		enum Font_type {
			helvetica = FL_HELVETICA,
			helvetica_bold = FL_HELVETICA_BOLD,
			helvetica_italic = FL_HELVETICA_ITALIC,
			helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
			courier = FL_COURIER,
			courier_bold = FL_COURIER_BOLD,
			courier_italic = FL_COURIER_ITALIC,
			courier_bold_italic = FL_COURIER_BOLD_ITALIC,
			times = FL_TIMES,
			times_bold = FL_TIMES_BOLD,
			times_italic = FL_TIMES_ITALIC,
			times_bold_italic = FL_TIMES_BOLD_ITALIC,
			symbol = FL_SYMBOL,
			screen = FL_SCREEN,
			screen_bold = FL_SCREEN_BOLD,
			zapf_dingbats = FL_ZAPF_DINGBATS
		};

		Font(Font_type ff) :f{ ff } { }
		Font(int ff) :f{ ff } { }

		int as_int() const { return f; }
	private:
		int f;
	};

	class Shape {
	protected:
		Shape() { }
		void add(Point p) { points.push_back(p); }
	public:
		void set_point(int i, Point p) { points[i] = p; }
		void draw() const;
	protected:
		virtual void draw_lines() const;
	public:
		void set_color(Color col) { lcolor = col; }
		Color color() const { return lcolor; }

		void set_style(Line_style sty) { ls = sty; }
		Line_style style() const { return ls; }

		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() const { return fcolor; }

		Point point(int i) const { return points[i]; }
		int number_of_points() const { return int(points.size()); }

		virtual Point e() { return point(0); }
		virtual Point w() { return point(0); }
		virtual Point n() { return point(0); }
		virtual Point s() { return point(0); }
		virtual Point ne() { return point(0); }
		virtual Point nw() { return point(0); }
		virtual Point se() { return point(0); }
		virtual Point sw() { return point(0); }
		virtual Point c() { return point(0); }

		virtual ~Shape() { }

		Shape(const Shape&) = delete;
		Shape& operator=(const Shape&) = delete;
	private:
		vector<Point> points;
		Color lcolor{ fl_color() };
		Line_style ls{ 0 };
		Color fcolor{ Color::invisible };
	};

	struct Fill {
		Fill() :no_fill(true), fcolor(0) { }
		Fill(Color c) :no_fill(false), fcolor(c) { }

		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() { return fcolor; }
	protected:
		bool no_fill;
		Color fcolor;
	};

	struct Line : Shape {
		Line(Point p1, Point p2) { add(p1); add(p2); }
	};

	struct Rectangle : Shape {
		Rectangle(Point x, Point y) 
			:_w{ y.x - x.x }, _h{ y.y - x.y }
		{
			if (_h <= 0 || _w <= 0) 
				error("Bad rectangle: first point is not top left");
			add(x);
		}
		void draw_lines() const;

		int height() const { return _h; }
		int width() const { return _w; }

		Point e() { return Point{ point(0).x + width(), int(point(0).y + 0.5 * height()) }; }
		Point w() { return Point{ point(0).x, int(point(0).y + 0.5 * height()) }; }
		Point n() { return Point{ point(0).x + int(0.5 * width()), point(0).y }; }
		Point s() { return Point{ int(point(0).x + 0.5 * width()), point(0).y + height() }; }
		Point ne() { return Point{ point(0).x + width(), point(0).y }; }
		Point nw() { return point(0); }
		Point se() { return Point{ point(0).x + width(), point(0).y + height() }; }
		Point sw() { return Point{ point(0).x, point(0).y + height() }; }
		Point c() { return Point{ int(point(0).x + 0.5 * width()), int(point(0).y + 0.5 * height()) }; }
	private:
		int _h;
		int _w;
	};

	struct Circle : Shape {
		Circle(Point p, int rr)
			:_r{ rr } 
		{
			add(Point{ p.x - _r, p.y - _r });
		}

		void draw_lines() const;

		Point center() const { return{ point(0).x + _r, point(0).y + _r }; }

		void set_radius(int rr) { _r = rr; }
		int radius() const { return _r; }

		Point e() { return Point{ center().x + radius(), center().y }; }
		Point w() { return Point{ center().x - radius(), center().y }; }
		Point n() { return Point{ center().x, center().y - radius() }; }
		Point s() { return Point{ center().x, center().y + radius() }; }
		Point ne() { return Point{ center().x + radius(), center().y - radius() }; }
		Point nw() { return point(0); }
		Point se() { return Point{ center().x + radius(), center().y + radius() }; }
		Point sw() { return Point{ center().x - radius(), center().y + radius() }; }
		Point c() { return center(); }
	private:
		int _r;
	};

	struct Text : Shape {
		Text(Point x, const string& s) : lab{ s } { add(x); }

		void draw_lines() const;

		void set_label(const string& s) { lab = s; }
		string label() const { return lab; }

		void set_font_size(int s) { fnt_sz = s; }
		int font_size() const { return fnt_sz; }
	private:
		string lab;
		Font fnt{ fl_font() };
		int fnt_sz{ (14 < fl_size()) ? fl_size() : 14 };
	};
}