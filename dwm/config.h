/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define ALTTERM "9term"
#define TERMCLASS "St"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int scalepreview       = 4;        /* preview scaling (display w and h / scalepreview) */
static const int previewbar         = 1;        /* show the bar in the preview window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static       int tag_preview        = 0;        /* 1 means enable, 0 is off */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;

#define ICONSIZE (bh - 4) /* adaptively preserve 2 pixels each side */
#define ICONSPACING 5 /* space (pixels) between icon and title */
static const char *fonts[]          = { "Terminus:pixelsize=14:antialias=true:autohint=true", "Font Awesome 6:pixelsize=14:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "Terminus:pixelsize=14:antialias=true:autohint=true";

// theme
#include "themes/rosepine.h"

static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { white,   gray1,  black },
    [SchemeSel]        = { white,   black,  black  },
    [SchemeHid]        = { blue,    black,  blue  },
};

static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x36", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spcalc", "-f", "Terminus:pixelsize=24:antialias=true:autohint=true", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = { TERMINAL, "-n", "sptune", "-g", "120x36", "-e", "ncmpcpp", NULL };
const char *spcmd4[] = { TERMINAL, "-n", "sppmix", "-g", "120x36", "-e", "alsamixer", NULL };
const char *spcmd5[] = { TERMINAL, "-n", "spstat", "-g", "120x36", "-e", "htop", NULL };
const char *spcmd6[] = { TERMINAL, "-n", "spfile", "-g", "120x36", "-e", "lfub", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
	{"sptune",      spcmd3},
	{"sppmix",      spcmd4},
	{"spstat",      spcmd5},
	{"spfile",      spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance     title           tags mask     isfloating   isterminal  noswallow  monitor */
	{ "St",           NULL,        NULL,           0,            0,           1,          0,        -1 },
	{ "tabbed",       "tabbed",    NULL,           0,            1,           0,          0,        -1 },
	{ "9term",        "9term",     NULL,           0,            1,           1,          0,        -1 },
	/* { "librewolf",    "Navigator", NULL,           0,            1,           0,          0,        -1 }, */
	{ "Magnus",       "magnus",    NULL,           0,            1,           0,          0,        -1 },
	{ "mpv",          "gl",        NULL,           0,            1,           0,          0,        -1 },
	{ TERMCLASS,      "floatterm", NULL,           0,            1,           1,          0,        -1 },
	{ TERMCLASS,      "bg",        NULL,           1 << 7,       0,           1,          0,        -1 },
	{ TERMCLASS,      "spterm",    NULL,           SPTAG(0),     1,           1,          0,        -1 },
	{ TERMCLASS,      "spcalc",    NULL,           SPTAG(1),     1,           1,          0,        -1 },
	{ TERMCLASS,      "sptune",    NULL,           SPTAG(2),     1,           1,          0,        -1 },
	{ TERMCLASS,      "sppmix",    NULL,           SPTAG(3),     1,           1,          0,        -1 },
	{ TERMCLASS,      "spstat",    NULL,           SPTAG(4),     1,           1,          0,        -1 },
	{ TERMCLASS,      "spfile",    NULL,           SPTAG(5),     1,           1,          0,        -1 },
	{ "Xmag",         "xmag",      NULL,           0,            1,           0,          0,        -1 },
	{ "XCalc",        "xcalc",     NULL,           0,            1,           0,          0,        -1 },
	{ "XTerm",        "xterm",     NULL,           0,            1,           1,          0,        -1 },
	{ NULL,           NULL,        "Event Tester", 0,            0,           0,          1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
 	/* symbol     arrange function */
 	{ "[M]",      monocle }, /* first entry is default */
 	{ "[]=",      tile },
	{ "[D]",      deck },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      previewtag,     {.ui = TAG } },     \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run","-F", "-c", "-l", "20", "-g", "5", "-p", "Run:", "-m", dmenumon, "-fn", dmenufont, "-nb", "#191724", "-nf", "#e0def4", "-sb", "#31748f", "-sf", "#e0def4", "-nhb", "#191724", "-nhf", "#31748f", "-shb", "#31748f", "-shf", "#eb6f92", NULL };
static const char *termcmd[]      = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char *tabtermcmd[]   = { "tabbed", "-c", "-r 2", TERMINAL, "-w", "''", NULL };
static const char *rclickcmd[]    = { "rclick.sh", NULL }; /* desktop right-click menu */

/* enable media keys */
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key                         function        argument */

	/* { MODKEY|ShiftMask,             XK_ ,                       spawn,          {.v = } }, */
	{ MODKEY,                       XK_F1,                      setlayout,      {.v = &layouts[1]}  },
	{ Mod1Mask,                     XK_F1,                      spawn,          {.v = rclickcmd }   },
	/* { MODKEY|ShiftMask,             XK_F1,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F2,                      setlayout,      {.v = &layouts[2]}  },
	{ Mod1Mask,                     XK_F2,                      spawn,          {.v = dmenucmd }    },
	/* { MODKEY|ShiftMask,             XK_F2,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F3,                      setlayout,      {.v = &layouts[3]}  },
	{ Mod1Mask,                     XK_F3,                      layoutmenu,     {0} },
	/* { MODKEY|ShiftMask,             XK_F3,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F4,                      setlayout,      {.v = &layouts[4]}  },
	{ Mod1Mask,                     XK_F4,                      killclient,     {0} },
	/* { MODKEY|ShiftMask,             XK_F4,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F5,                      setlayout,      {.v = &layouts[5]}  },
	/* { MODKEY|ShiftMask,             XK_F5,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F6,                      setlayout,      {.v = &layouts[6]}  },
	/* { MODKEY|ShiftMask,             XK_F6,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F7,                      setlayout,      {.v = &layouts[7]}  },
	/* { MODKEY|ShiftMask,             XK_F7,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F8,                      setlayout,      {.v = &layouts[8]}  },
	/* { MODKEY|ShiftMask,             XK_F8,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F9,                      setlayout,      {.v = &layouts[9]}  },
	/* { MODKEY|ShiftMask,             XK_F9,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F10,                     setlayout,      {.v = &layouts[10]} },
	/* { MODKEY|ShiftMask,             XK_F10,                     spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F11,                     setlayout,      {.v = &layouts[11]} },
	/* { MODKEY|ShiftMask,             XK_F11,                     spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F12,                     setlayout,      {.v = &layouts[12]} },
	/* { MODKEY|ShiftMask,             XK_F12,                     spawn,          {.v = }  }, */

	{ MODKEY,                       XK_Home,                    setlayout,      {.v = &layouts[0]}  },
	/* { MODKEY|ShiftMask,             XK_Home,                    spawn,          {.v = }  }, */
	{ MODKEY,                       XK_End,                     setlayout,      {0} },
	/* { MODKEY|ShiftMask,             XK_End,                     spawn,          {.v = }  }, */

	{ 0,                            XK_Print,                   spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,                   spawn,          {.v = (const char*[]){ "maimpick", NULL } } },

	{ MODKEY,                       XK_grave,                   togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_grave,                   setlayout,      {.v = &layouts[13]} },

	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
	TAGKEYS(                        XK_0,                                       9)

	{ MODKEY,                       XK_minus,                   incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_equal,                   incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,                   defaultgaps,    {0} },

	{ MODKEY,                       XK_BackSpace,               spawn,          {.v = (const char*[]){ "sysact", NULL } } },
	/* { MODKEY|ShiftMask,             XK_BackSpace,               spawn,          SHCMD("") }, */

	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,                     view,           {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_Tab,                     tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,                       quitprompt,     {0} },
	{ MODKEY,                       XK_w,                       spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ControlMask,           XK_w,                       incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_w,                       incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_w,                       incrogaps,      {.i = -1 } },
	{ MODKEY,                       XK_r,                       togglescratch,  {.ui = 5 } },
	{ MODKEY|ShiftMask,             XK_r,                       togglescratch,  {.ui = 4 } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = tabtermcmd } },
	/* { MODKEY,                       XK_i,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_i,                       incnmaster,     {.i = +1 } },
	/* { MODKEY,                       XK_o,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_o,                       incnmaster,     {.i = -1 } },

	/* { MODKEY,                       XK_bracketleft,             spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_bracketleft,             spawn,          {.v = } }, */
	/* { MODKEY,                       XK_bracketright,            spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_bracketright,            spawn,          {.v = } }, */

	/* { MODKEY,                       XK_backslash,               spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_backslash,               spawn,          SHCMD("") }, */


	/* { MODKEY,                       XK_a,                       spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_a,                       spawn,          {.v = } }, */
	{ MODKEY|ControlMask,           XK_a,                       incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_a,                       incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_a,                       incrigaps,      {.i = +1 } },
	{ MODKEY,                       XK_s,                       togglesticky,   {0} },
	/* { MODKEY|ShiftMask,             XK_s,                       spawn,          {.v = } }, */
	{ MODKEY|ControlMask,           XK_s,                       incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_s,                       incrihgaps,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_s,                       incrogaps,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_d,                       incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_d,                       incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_d,                       incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_f,                       togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_g,                       togglegaps,     {0} },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,                       setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_j,                       focusstackvis,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,                       focusstackhid,  {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,                       focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,                       setcfact,       {.f = -0.25} },


	{ MODKEY,                       XK_semicolon,               spawn,          {.v = dmenucmd } },
	/* { MODKEY|ShiftMask,             XK_semicolon,               spawn,          {.v = } }, */
	/* { MODKEY,                       XK_apostrophe,              spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_apostrophe,              spawn,          {.v = } }, */

	{ MODKEY,                       XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,              XK_Return,                  togglescratch,  {.ui = 0 } },

	{ MODKEY,                       XK_z,                       showall,        {0} },
	{ MODKEY,                       XK_x,                       hide,           {0} },
	{ MODKEY|ShiftMask,             XK_x,                       show,           {0} },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_m,                       togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_m,                       togglescratch,  {.ui = 3 } },

	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,             XK_space,                   zoom,           {0} },
	{ MODKEY,                       XK_space,                   focusmaster,           {0} },

	{ 0,                            XF86XK_AudioMute,           spawn,          SHCMD("amixer -q sset Master toggle") },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("amixer -q sset Master 5%-") },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("amixer -q sset Master 5%+") },
	{ 0,                            XF86XK_AudioPrev,           spawn,          {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ ShiftMask,                    XF86XK_AudioPrev,           spawn,          {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0,                            XF86XK_AudioPlay,           spawn,          {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ ShiftMask,                    XF86XK_AudioPlay,           spawn,          {.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0,                            XF86XK_AudioNext,           spawn,          {.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ ShiftMask,                    XF86XK_AudioNext,           spawn,          {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },

	{ 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = (const char*[]){ "xbacklight", "-dec", "5", NULL } } },
	{ 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = (const char*[]){ "xbacklight", "-inc", "5", NULL } } },

	{ 0,                            XF86XK_Calculator,          spawn,          {.v = (const char*[]){ "xcalc", NULL } } },
	{ ShiftMask,                    XF86XK_Calculator,          spawn,          {.v = (const char*[]){ ALTTERM, "ivy", "-prompt", "%> ", NULL } } },

	{ MODKEY|ControlMask,           XK_Up,                      movekeyboard_y, {.i = -20}},
	{ MODKEY|ControlMask,           XK_Left,                    movekeyboard_x, {.i = -20}},
	{ MODKEY|ControlMask,           XK_Down,                    movekeyboard_y, {.i = 20}},
	{ MODKEY|ControlMask,           XK_Right,                   movekeyboard_x, {.i = 20}},
};

/* button definitions */
#define Button6 6
#define Button7 7
#define Button8 8
#define Button9 9

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkRootWin,           0,                Button3,        spawn,          {.v = rclickcmd } },

	/* zoom */
	{ ClkClientWin,         MODKEY,           Button2,        spawn,          SHCMD("highlighter") },
	{ ClkClientWin,         MODKEY|ShiftMask, Button2,        spawn,          SHCMD("killall magnus || magnus") },

	{ ClkLtSymbol,          0,                Button1,        layoutmenu,     {0} },

	{ ClkWinTitle,          0,                Button1,        togglewin,      {0} },
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        dragmfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,        dragcfact,      {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};

