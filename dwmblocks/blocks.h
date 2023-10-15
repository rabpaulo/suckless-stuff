//Modify this file to change what commands output to your statusbar, and recompile using the make command.

static const Block blocks[] = {
    /*Icon*/	/*Command*/			/*Update Interval*/	/*Update Signal*/
    {"", "~/.local/bin/sb/cmus.sh", 		2,	0},
    {"", "~/.local/bin/sb/keeblayout.sh", 	1,	0},
    {"", "~/.local/bin/sb/micebattery.sh", 	5,	0},
    {"", "~/.local/bin/sb/cpu.sh", 		2,	0},
    {"", "~/.local/bin/sb/memory.sh", 		2,	0},
    {"", "~/.local/bin/sb/disk.sh", 		10,	0},
    {"", "~/.local/bin/sb/ethernet.sh", 	30,	0},
    {"", "~/.local/bin/sb/weather.sh", 		300,	5},
    {"", "date '+%R %a, %d %b'",		2,	0}
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
