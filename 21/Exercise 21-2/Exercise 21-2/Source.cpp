// Files in this project:
// "Simple_window.h"
// "Graph.h"

#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"
using namespace Graph_lib;

int main()
{
	Simple_window w{ Point{ 100, 100 }, 600, 400, "My Garph lib" };

	Rectangle house{ Point{ 100, 200 }, Point{ 400, 400 } };
	house.set_color(Color::dark_green);
	house.set_fill_color(Color::dark_green);
	w.draw(house);

	Rectangle roof{ Point{ 150, 150 }, Point{ 350, 200 } };
	roof.set_color(Color::dark_blue);
	roof.set_fill_color(Color::dark_blue);
	w.draw(roof);

	Rectangle door{ Point{ 150, 275 }, Point{ 200, 400 } };
	door.set_color(Color::yellow);
	door.set_fill_color(Color::yellow);
	w.draw(door);

	Rectangle window1{ Point{ 250, 285 }, Point{ 300, 335 } };
	window1.set_color(Color::cyan);
	window1.set_fill_color(Color::cyan);
	w.draw(window1);

	Rectangle window2{ Point{ 325, 285 }, Point{ 375, 335 } };
	window2.set_color(Color::cyan);
	window2.set_fill_color(Color::cyan);
	w.draw(window2);

	Rectangle chimney{ Point{ 300, 75 }, Point{ 350, 150 } };
	chimney.set_color(Color::dark_yellow);
	chimney.set_fill_color(Color::dark_yellow);
	w.draw(chimney);

	Circle smoke{ Point{ 400, 25 }, 15 };
	smoke.set_color(Color::white);
	smoke.set_fill_color(Color::white);
	w.draw(smoke);

	w.wait_for_button();
	return 0;
}