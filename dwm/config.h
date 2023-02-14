/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define ALTTERM "9term"
#define TERMCLASS "St"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "Terminus:pixelsize=14:antialias=true:autohint=true", "Font Awesome 6:pixelsize=14:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "Terminus:pixelsize=14:antialias=true:autohint=true";
static const char col_gray1[]       = "#26233a";
static const char col_gray2[]       = "#191724";
static const char col_gray3[]       = "#e0def4";
static const char col_cyan[]        = "#31748f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray2,  col_gray2 },
	[SchemeSel]  = { col_gray3, col_gray1,  col_gray2 },
	[SchemeHid]  = { col_cyan,  col_gray2,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spcalc", "-f", "Terminus:pixelsize=24:antialias=true:autohint=true", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = { TERMINAL, "-n", "sptune", "-g", "120x34", "-e", "ncmpcpp", NULL };
const char *spcmd4[] = { TERMINAL, "-n", "sppmix", "-g", "120x34", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
	{"sptune",      spcmd3},
	{"sppmix",      spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

/* grid of tags */
#define DRAWCLASSICTAGS             1 << 0
#define DRAWTAGGRID                 1 << 1

#define SWITCHTAG_UP                1 << 0
#define SWITCHTAG_DOWN              1 << 1
#define SWITCHTAG_LEFT              1 << 2
#define SWITCHTAG_RIGHT             1 << 3
#define SWITCHTAG_TOGGLETAG         1 << 4
#define SWITCHTAG_TAG               1 << 5
#define SWITCHTAG_VIEW              1 << 6
#define SWITCHTAG_TOGGLEVIEW        1 << 7

static const unsigned int drawtagmask = DRAWTAGGRID; /* | DRAWCLASSICTAGS to show classic row of tags */
static const int tagrows = 2;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance  title           tags mask     isfloating   monitor */
	{ "St",           NULL,     NULL,           0,            0,           -1 },
	{ TERMCLASS,      "bg",     NULL,           1 << 7,       0,           -1 },
	{ TERMCLASS,      "spterm", NULL,           SPTAG(0),     1,           -1 },
	{ TERMCLASS,      "spcalc", NULL,           SPTAG(1),     1,           -1 },
	{ TERMCLASS,      "sptune", NULL,           SPTAG(2),     1,           -1 },
	{ TERMCLASS,      "sppmix", NULL,           SPTAG(3),     1,           -1 },
	{ NULL,           NULL,     "Event Tester", 0,            0,           -1 }, /* xev */
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
 	{ "[]=",      tile },    /* first entry is default */
	{ "[D]",      deck },
 	{ "[M]",      monocle },
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
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-F", "-c", "-l", "20", "-g", "5", "-p", "Run:", "-m", dmenumon, "-fn", dmenufont, "-nb", "#191724", "-nf", "#e0def4", "-sb", "#eb6f92", "-sf", "#e0def4", "-nhb", "#191724", "-nhf", "#e0def4", "-shb", "#eb6f92", "-shf", "#31748f", NULL };
static const char *termcmd[]    = { TERMINAL, NULL };
static const char *alttermcmd[] = { "9", "9term", "rc", NULL };
static const char *tabtermcmd[] = { "tabbed", "-r 2", TERMINAL, "-w", "''", NULL };

/* enable media keys */
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key                         function        argument */

	/* { MODKEY|ShiftMask,             XK_ ,                       spawn,          {.v = } }, */
	{ MODKEY,                       XK_F1,                      setlayout,      {.v = &layouts[0]}  },
	/* { MODKEY|ShiftMask,             XK_F1,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F2,                      setlayout,      {.v = &layouts[1]}  },
	/* { MODKEY|ShiftMask,             XK_F2,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F3,                      setlayout,      {.v = &layouts[2]}  },
	/* { MODKEY|ShiftMask,             XK_F3,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F4,                      setlayout,      {.v = &layouts[3]}  },
	/* { MODKEY|ShiftMask,             XK_F4,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F5,                      setlayout,      {.v = &layouts[4]}  },
	/* { MODKEY|ShiftMask,             XK_F5,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F6,                      setlayout,      {.v = &layouts[5]}  },
	/* { MODKEY|ShiftMask,             XK_F6,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F7,                      setlayout,      {.v = &layouts[6]}  },
	/* { MODKEY|ShiftMask,             XK_F7,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F8,                      setlayout,      {.v = &layouts[7]}  },
	/* { MODKEY|ShiftMask,             XK_F8,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F9,                      setlayout,      {.v = &layouts[8]}  },
	/* { MODKEY|ShiftMask,             XK_F9,                      spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F10,                     setlayout,      {.v = &layouts[9]}  },
	/* { MODKEY|ShiftMask,             XK_F10,                     spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F11,                     setlayout,      {.v = &layouts[10]} },
	/* { MODKEY|ShiftMask,             XK_F11,                     spawn,          {.v = }  }, */
	{ MODKEY,                       XK_F12,                     setlayout,      {.v = &layouts[11]}  },
	/* { MODKEY|ShiftMask,             XK_F12,                     spawn,          {.v = }  }, */
	{ MODKEY,                       XK_Home,                    setlayout,      {.v = &layouts[12]}  },
	/* { MODKEY|ShiftMask,             XK_Home,                    spawn,          {.v = }  }, */
	{ MODKEY,                       XK_End,                     setlayout,      {0} },
	/* { MODKEY|ShiftMask,             XK_End,                     spawn,          {.v = }  }, */
	{ 0,                            XK_Print,                   spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,                   spawn,          {.v = (const char*[]){ "maimpick", NULL } } },
	/* { MODKEY,                       XK_equal,                   spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_equal,                   spawn,          {.v = } }, */
	/* { MODKEY,                       XK_minus,                   spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_minus,                   spawn,          {.v = } }, */
	{ MODKEY,                       XK_BackSpace,               spawn,          {.v = (const char*[]){ "sysact", NULL } } },
	/* { MODKEY|ShiftMask,             XK_BackSpace,               spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_grave,                   togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_grave,                   setlayout,      {.v = &layouts[13]}  },
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
	{ ControlMask|Mod1Mask,         XK_9,                       spawn,          {.v = alttermcmd } },

	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,                     view,           {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_Tab,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,                       quitprompt,     {0} },
	{ MODKEY,                       XK_w,                       spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,                       XK_r,                       spawn,          {.v = (const char*[]){ TERMINAL, "-e", "lfub", "-command", "set hidden", NULL } } },
	{ MODKEY|ShiftMask,             XK_r,                       setcfact,       {.f =  0.00} },
	{ ControlMask|Mod1Mask,         XK_t,                       spawn,          {.v = termcmd } },
	/* { MODKEY,                       XK_i,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_i,                       incnmaster,     {.i = +1 } },
	/* { MODKEY,                       XK_o,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_o,                       incnmaster,     {.i = -1 } },
	/* { MODKEY,                       XK_bracketleft,             spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_bracketleft,             spawn,          {.v = } }, */
	/* { MODKEY,                       XK_bracketright,            spawn,          {.v = } }, */
	/* { MODKEY|ShiftMask,             XK_bracketright,            spawn,          {.v = } }, */
	{ MODKEY,                       XK_backslash,               spawn,          SHCMD("killall highlight-pointer || highlight-pointer -t 5 -c '#ea9d34' -p '#56949f' -o 5 -r 25 --show-cursor --auto-hide-highlight &") },
	/* { MODKEY|ShiftMask,             XK_backslash,               spawn,          SHCMD("") }, */


	/* { MODKEY,                       XK_a,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_a,                       spawn,          {.v = (const char*[]){ "acme9", "-n", "0", NULL } } },
	/* { MODKEY,                       XK_s,                       spawn,          {.v = } }, */
	{ MODKEY|ShiftMask,             XK_s,                       spawn,          {.v = (const char*[]){ "9", "sam", NULL } } },
	{ MODKEY,                       XK_f,                       togglefullscr,  {0} },
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
	{ MODKEY|ShiftMask,             XK_Return,                  togglescratch,  {.ui = 0 } },
	{ ControlMask|Mod1Mask,         XK_Return,                  spawn,          {.v = tabtermcmd } },

	{ MODKEY,                       XK_z,                       show,           {0} },
	{ MODKEY|ShiftMask,             XK_z,                       showall,        {0} },
	{ MODKEY,                       XK_x,                       hide,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                       killclient,     {0} },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_m,                       togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_m,                       togglescratch,  {.ui = 3 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,             XK_space,                   zoom,           {0} },
	{ MODKEY,                       XK_space,                   focusmaster,    {0} },

    { MODKEY,                       XK_Up,                      switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_VIEW } },
    { MODKEY,                       XK_Down,                    switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_VIEW } },
    { MODKEY,                       XK_Right,                   switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_VIEW } },
    { MODKEY,                       XK_Left,                    switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_VIEW } },

    { MODKEY|ShiftMask,             XK_Up,                      switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,             XK_Down,                    switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,             XK_Right,                   switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY|ShiftMask,             XK_Left,                    switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },

	{ 0,                            XF86XK_AudioMute,           spawn,          SHCMD("pulsemixer --toggle-mute") },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("pulsemixer --change-volume -5") },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pulsemixer --change-volume +5") },
	{ 0,                            XF86XK_AudioPrev,           spawn,          {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ ShiftMask,                    XF86XK_AudioPrev,           spawn,          {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0,                            XF86XK_AudioPlay,           spawn,          {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ ShiftMask,                    XF86XK_AudioPlay,           spawn,          {.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0,                            XF86XK_AudioNext,           spawn,          {.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ ShiftMask,                    XF86XK_AudioNext,           spawn,          {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },

	{ 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = (const char*[]){ "xbacklight", "-dec", "5", NULL } } },
	{ 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = (const char*[]){ "xbacklight", "-inc", "5", NULL } } },

	{ 0,                            XF86XK_Calculator,          togglescratch,  {.ui = 1} },
	{ ShiftMask,                    XF86XK_Calculator,          spawn,          {.v = (const char*[]){ ALTTERM, "ivy", "-prompt", "%> ", NULL } } },


	{ MODKEY|ControlMask,           XK_u,            incrgaps,       {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_u,            incrgaps,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,            incrigaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_i,            incrigaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_o,            incrogaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_o,            incrogaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_6,            incrihgaps,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_6,            incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_7,            incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_7,            incrivgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_8,            incrohgaps,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_8,            incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_9,            incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_9,            incrovgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_0,            togglegaps,     {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_0,            defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

