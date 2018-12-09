// terminal.cpp

#include "terminal.h"
#include <iostream>

Terminal::~Terminal() {}

Terminal::Terminal(int w, int h) {
	this->w = w;
	this->h = h;
	font_size = 12;
}

void Terminal::set_font_size(short s) { font_size = s; }
int Terminal::get_font_size(char* text) { return gfx_textpixelheight(text, font); }
int Terminal::get_width(char* text) { return gfx_textpixelwidth(text, font); }

void Terminal::print(char* text) {
	int row = prep_term(text);
	gfx_text(0, row, text);
}

string Terminal::prompt(char* msg) {
	string entry;
	int row = prep_term(msg);
	int col = get_width(msg);
	int pt = get_font_size(msg);
	gfx_color(255,255,255);
	gfx_text(0,row,msg);
	do {
		int e = (gfx_event_waiting() == 2) ? (int)gfx_wait() : -1;
		if (e == -1) continue;
		// if (isalpha(e) || isdigit(e)) {
		/* cout << (char)e << endl; */
		/* } else cout << e << endl; */
		if (e == 13) break;
		if(isalpha(e) || isdigit(e)) entry += (char)e;
		else if (e == 8) entry.pop_back();

		gfx_color(tbgR,tbgG,tbgB);
		gfx_fill_rectangle(0,row-pt, w, pt+tween);
		gfx_color(255,255,255);
		gfx_text(0,row,msg);
		gfx_text(col, row, entry.c_str());
	} while (true);
	return entry;
}

int Terminal::prep_term(char* text) {
	int pt = get_font_size(text);
	static int printY = pt;
	gfx_color(255,255,255);
	if (printY > h) {
		terminal_clear();
		printY = pt;
	}
	printY += get_font_size(text) + tween;
	return printY - get_font_size(text) - tween;
}

void Terminal::terminal_clear() {
	gfx_color(tbgR, tbgG, tbgB);
	gfx_fill_rectangle(0,0, w, h);
}
