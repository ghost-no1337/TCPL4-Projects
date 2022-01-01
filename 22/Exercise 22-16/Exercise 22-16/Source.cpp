#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "Matrix11.h"
#include <FL/fl_ask.H>
using namespace Graph_lib;
using namespace Numeric_lib;

class Reversi : public Window {
public:
	Reversi(Point xy, int w, int h, const string& title);
private:
	enum Chess {
		empty, dark, light // so that static_cast<int>() returns the player number
	};

	enum Pos {
		nw, n, ne, e, se, s, sw, w
	};

	class Next_chess {
	public:
		Next_chess(Pos pos)
			:p{ pos } { }
		pair<int, int> operator()(const pair<int, int>&);
	private:
		Pos p;
	};

	Matrix<Chess, 2> chess_board{ 8, 8 };
	Chess current_player{ dark };

	Vector_ref<Rectangle> chess_board_gui;
	Vector_ref<Circle> chess_gui;

	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Button computer_button;
	Button giveup_button;
	Out_box player;
	Out_box lightno;
	Out_box darkno;

	bool computer_playing{ false };

	void next();
	void quit();

	void computer_play() { computer_playing = true; computer_button.hide(); }
	void final();

	bool check_rule(int x, int y, bool change);
	bool check_possibility(bool change);
	void give_up();
	void computer_turn();
	void update_gui();
	void change_player();

	static void cb_next(Address, Address);
	static void cb_quit(Address, Address);
	static void cb_giveup(Address, Address);
	static void cb_computer(Address, Address);
};

Reversi::Reversi(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	next_button{ Point{ x_max() - 150, 0 }, 70, 20, "Next", cb_next },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit },
	next_x{ Point{ x_max() - 310, 0 }, 50, 20, "next x:" },
	next_y{ Point{ x_max() - 210, 0 }, 50, 20, "next y:" },
	computer_button{ Point{ x_max() - 70, 30 }, 70, 20, "Computer", cb_computer },
	giveup_button{ Point{ x_max() - 70, 50 }, 70, 20, "Give up!", cb_giveup },
	player{ Point{ x_max() - 70, 70 }, 70, 20, "player:" },
	lightno{ Point{ x_max() - 70, 90 }, 70, 20, "light:" },
	darkno{ Point{ x_max() - 70, 110 }, 70, 20, "dark:" }
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(computer_button);
	attach(giveup_button);
	attach(player);
	player.put(static_cast<int>(current_player));
	attach(lightno);
	attach(darkno);
	lightno.put(0);
	darkno.put(0);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			chess_board[i][j] = empty;

	chess_board[3][3] = light;
	chess_board[3][4] = dark;
	chess_board[4][3] = dark;
	chess_board[4][4] = light;

	for (int i = 50; i <= 8 * 50; i += 50)
		for (int j = 50; j <= 8 * 50; j += 50) {
			chess_board_gui.push_back(new Rectangle{ Point{i, j}, Point{i + 50, j + 50} });
			attach(chess_board_gui[chess_board_gui.size() - 1]);
		}

	for (int i = 50 + 25; i <= 8 * 50 + 25; i += 50)
		for (int j = 50 + 25; j <= 8 * 50 + 25; j += 50) {
			chess_gui.push_back(new Circle{ Point{ i, j }, 25 });
			attach(chess_gui[chess_gui.size() - 1]);
			chess_gui[chess_gui.size() - 1].set_color(Color::invisible);
		}

	update_gui();
}

pair<int, int> Reversi::Next_chess::operator()(const pair<int, int>& a)
{
	switch (p)
	{
	case Reversi::nw:
		return make_pair(a.first - 1, a.second - 1);
	case Reversi::n:
		return make_pair(a.first - 1, a.second);
	case Reversi::ne:
		return make_pair(a.first - 1, a.second + 1);
	case Reversi::e:
		return make_pair(a.first, a.second + 1);
	case Reversi::se:
		return make_pair(a.first + 1, a.second + 1);
	case Reversi::s:
		return make_pair(a.first + 1, a.second);
	case Reversi::sw:
		return make_pair(a.first + 1, a.second - 1);
	case Reversi::w:
		return make_pair(a.first, a.second - 1);
	}
}

bool Reversi::check_rule(int x, int y, bool change)
{
	bool legal{ false };

	if (chess_board[x - 1][y - 1])
		return legal;

	const int x_orig = x - 1, y_orig = y - 1;
	for (Pos p{}; p <= w; p = static_cast<Pos>(static_cast<int>(p) + 1)) {
		x = x_orig;
		y = y_orig;
		Next_chess next{ p };
		vector<pair<int, int>> changes;
		while (true) {
			int x_ = x, y_ = y;
			x = next(make_pair(x_, y_)).first;
			y = next(make_pair(x_, y_)).second;

			if (x >= 0 && x < 8 && y >= 0 && y < 8)
				if (chess_board[x][y] == empty)
					break;
				else if (chess_board[x][y] == current_player) {
					if (changes.size() == 0)
						break;
					else {
						if (change)
							for (auto x : changes)
								chess_board[x.first][x.second] = current_player;
						legal = true;
						break;
					}
				}
				else
					changes.push_back(make_pair(x, y));
			else
				break;
		}
	}

	return legal;
}

bool Reversi::check_possibility(bool change)
{
	for (int i = 1; i < 8; i++)
		for (int j = 1; j < 8; j++)
			if (check_rule(i, j, change)) {
				if (change)
					chess_board[i - 1][j - 1] = current_player;
				return true;
			}
	return false;
}

void Reversi::final()
{
	const Chess orig_current = current_player;
	current_player = light;
	bool posl = check_possibility(false);
	current_player = dark;
	bool posd = check_possibility(false);
	current_player = orig_current;

	if (!posl && !posd) {
		next_button.hide();
		giveup_button.hide();

		int lno = 0, dno = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				switch (chess_board[i][j]) {
				case light:
					++lno;
					break;
				case dark:
					++dno;
					break;
				case empty:
					break;
				}

		ostringstream oss;
		if (lno == dno)
			fl_message("Game is over! Fair.");
		else if (lno > dno)
			oss << "Game is over! Player " << static_cast<int>(light) << " wins.";
		else
			oss << "Game is over! Player " << static_cast<int>(dark) << " wins.";
		fl_message(oss.str().c_str());
	}
}

void Reversi::give_up()
{
	if (check_possibility(false))
		fl_alert("You cannot give up right now!");
	else {
		change_player();
		if (computer_playing) {
			computer_turn();
			update_gui();
			final();
			redraw();
		}
	}
}

void Reversi::computer_turn()
{
	if(check_possibility(true))
		change_player();
	else {
		change_player();
		fl_message("Computer has given up! Your turn!");
	}
}

void Reversi::update_gui()
{
	int lno = 0, dno = 0;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			switch (chess_board[i][j]) {
			case light:
				chess_gui[j * 8 + i].set_fill_color(Color::white);
				++lno;
				break;
			case dark:
				chess_gui[j * 8 + i].set_fill_color(Color::black);
				++dno;
				break;
			case empty:
				break;
			}
	lightno.put(lno);
	darkno.put(dno);
}

void Reversi::change_player()
{
	switch (current_player) {
	case light:
		current_player = dark;
		player.put(static_cast<int>(current_player));
		break;
	case dark:
		current_player = light;
		player.put(static_cast<int>(current_player));
		break;
	}
}

void Reversi::next()
try {
	int x = next_x.get_int();
	int y = next_y.get_int();
	if (x <= 0 || x > 8 || y <= 0 || y > 8)
		error("int out of range");

	if (check_rule(x, y, true))
		chess_board[x - 1][y - 1] = current_player;
	else
		error("bad position: illegal position");

	computer_button.hide();

	change_player();
	if (computer_playing)
		computer_turn();
	update_gui();
	final();
	redraw();
}
catch (exception& e) {
	ostringstream oerr;
	oerr << "ERROR: " << e.what();
	fl_alert(oerr.str().c_str());
	redraw();
}

void Reversi::cb_quit(Address, Address pw)
{
	reference_to<Reversi>(pw).quit();
}

void Reversi::quit()
{
	hide();
}

void Reversi::cb_next(Address, Address pw)
{
	reference_to<Reversi>(pw).next();
}

void Reversi::cb_giveup(Address, Address pw)
{
	reference_to<Reversi>(pw).give_up();
}

void Reversi::cb_computer(Address, Address pw)
{
	reference_to<Reversi>(pw).computer_play();
}

int main()
try {
	Reversi win{ Point{ 100, 100 }, 600, 600, "Reversi" };
	return gui_main();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}