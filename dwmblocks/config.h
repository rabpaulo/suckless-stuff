//Modify this file to change what commands output to your statusbar, and recompile using the make command.

static const Block blocks[] = {
    /*Icon*/	/*Command*/			/*Update Interval*/	/*Update Signal*/
    {"", "~/.local/bin/sb/cmus.sh", 		2,	0},
    {"🧠 ", "free -h | awk '/^Mem/ {print $3}' | sed 's/Gi/G/g'",	 	10,	0},
    {"💽 ", "~/.local/bin/sb/disk",	 	60,	0},
    {"⌨ ", "~/.local/bin/sb/keyboardlayout ", 	1,	0},
    {"", "~/.local/bin/sb/buds", 		30,	0},
    {"📅 ", "date '+%R %a, %d %b'",		2,	0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
