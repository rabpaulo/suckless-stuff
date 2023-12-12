/* See LICENSE file for copyright and license details. */

/* appearance */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 2;       /* snap pixel */

static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */

static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const char *fonts[]          = { "mono:size=8:antilias=true:autohint=true",  "NotoColorEmoji:pixelsize=10:autohint=true"};

static const char background[]   = "#222222";
static const char titlecolor[]   = "#bbbbbb";
static const char activecolor[]  = "#bbbbbb";
static const char foreground[]   = "#005577";
static const char border[]       = "#444444";
static const char inacborder[]   = "#000000";

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { titlecolor, background, inacborder }, /* unfocused window */
	[SchemeSel]  = { activecolor, foreground, border  }, /* focused window */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "KeePassXC",	NULL,	NULL,           0,         1,          0,           0,        -1 },
	{ "Gimp",	NULL,	NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",	NULL,	NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",     	NULL,	NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      	NULL,	"Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "St",     	"pulsemixer",    NULL,   0,     	1,           1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */

	{ "[]=",      tile },    
	{ "H[]",      deck },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[@]",      spiral },	/* first entry is default */
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */


	{ 0,			XK_F6,		spawn,		SHCMD("cmus-remote -r") }, // Previous song
	{ 0,			XK_F8,		spawn,		SHCMD("cmus-remote -n") }, // Next song
	{ 0,			XK_F11,		spawn,		SHCMD("cmus-remote -v +10%") }, 
	{ 0,			XK_F10,		spawn,		SHCMD("cmus-remote -v -10%") },
	{ 0,			XK_F9,		spawn,		SHCMD("volumecmus") }, 
	{ 0,			XK_F7,		spawn,		{.v = (const char*[]){ "cmusmediacontrol", NULL } } },	

	{ MODKEY,			XK_F5,		spawn,		SHCMD("setsid -f st -n pulsemixer -g 120x40 -e pulsemixer") }, 

	{ MODKEY,			XK_F12,		spawn,		SHCMD("slock") }, 
	{ MODKEY|ShiftMask,		XK_a,		spawn,		{.v = (const char*[]){ "record", NULL } } },	
	{ MODKEY|ShiftMask,		XK_b,		spawn,		{.v = (const char*[]){ "bookmarks", NULL } } },	
	{ MODKEY|ShiftMask,		XK_r,		spawn,		{.v = (const char*[]){ "mouseacell.sh", NULL } } },	
	{ MODKEY,			XK_s,		spawn,		{.v = (const char*[]){ "screenshots.sh", NULL } } },	
	{ MODKEY,                       XK_d,      	spawn,          {.v = dmenucmd } },
	{ MODKEY,	             	XK_Return, 	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,     	togglebar,      {0} },
	{ MODKEY,                       XK_j,     	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,     	focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,     	setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,     	setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,     	movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,     	movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,     	setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,     	setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,     	setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return,	setlayout,           {0} },
	{ MODKEY,                       XK_Tab,   	view,           {0} },
	{ MODKEY,             		XK_q,     	killclient,     {0} },
	{ MODKEY,                       XK_t,     	setlayout,      {.v = &layouts[0]} },
	{ MODKEY,          		XK_y,     	setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,     	setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,	       	XK_space, 	zoom,      {0} },
	{ MODKEY,             		XK_space, 	togglefloating, {0} },

	{ MODKEY|ShiftMask,                       XK_Down,    	 moveresize,     {.v = "0x 50y 0w 0h" } },
	{ MODKEY|ShiftMask,                       XK_Up,     	 moveresize,     {.v = "0x -50y 0w 0h" } },
	{ MODKEY|ShiftMask,                       XK_Right,  	 moveresize,     {.v = "50x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,                       XK_Left,   	 moveresize,     {.v = "-50x 0y 0w 0h" } },

	{ MODKEY,             XK_Down,   	 moveresize,     {.v = "0x 0y 0w 60h" } },
	{ MODKEY,             XK_Up,     	 moveresize,     {.v = "0x 0y 0w -60h" } },
	{ MODKEY,             XK_Right,  	 moveresize,     {.v = "0x 0y 60w 0h" } },
	{ MODKEY,             XK_Left,   	 moveresize,     {.v = "0x 0y -60w 0h" } },

	{ MODKEY|ControlMask,           XK_Up,     	 moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   	 moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   	 moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  	 moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     	 moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   	 moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   	 moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  	 moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,     	 view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,     	 tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma, 	 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,	 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma, 	 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	 tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	{ MODKEY|ShiftMask,             XK_q,      	 quit,         		{0} },
	{ MODKEY|ShiftMask,		XK_u,		 togglegaps,		{0} },

	{ MODKEY|ShiftMask,             XK_minus,     	 incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,     	 incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus, 	 incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrogaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrihgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrivgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,   		XK_minus,  	 defaultgaps,    {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

