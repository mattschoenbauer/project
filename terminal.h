// terminal.h

#ifndef TERMINAL_H
#define TERMINAL_H

#include <X11/Xlib.h>
#include "gfx3.h"
using namespace std;

class Terminal {
	public:
		~Terminal();
		Terminal(int w, int h);
		void print(char* text);
		void set_font_size(short);
		void terminal_clear();
		int get_font_size(char* text);
	private:
		char* font = "-misc-fixed-medium-r-semicondensed--12-110-75-75-c-60-iso8859-1";
		short font_size;
		int w, h;
		const int tbgR = 0, tbgG = 0, tbgB = 0;
};

#endif