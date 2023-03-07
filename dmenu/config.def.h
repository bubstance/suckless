/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static const int vertpad = 5;               /* vertical padding of bar */
static const int sidepad = 5;               /* horizontal padding of bar */
static int colorprompt = 0;                 /* -p  option; if 1, prompt uses SchemeSel, otherwise SchemeNorm */
static int fuzzy = 1;                       /* -F  option; if 0, dmenu doesn't use fuzzy matching     */
static int centered = 0;                    /* -c option; centers dmenu on screen */
static int min_width = 1000;                /* minimum width when centered */
static const int user_bh = 10;              /* add an defined amount of pixels to the bar height */

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"Terminus:pixelsize=18:antialias=true:autohint=true"
	"Symbols Nerd Font:pixelsize=20:antialias=true:autohint=true"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#e0def4", "#191724" },
	[SchemeSel] = { "#e0def4", "#31748f" },
	[SchemeSelHighlight] = { "#eb6f92", "#31748f" },
	[SchemeNormHighlight] = { "#31748f", "#191724" },
	[SchemeOut] = { "#e0def4", "#eb6f92" },
	[SchemeCaret] = { "#e0def4", "#191724" },
};
/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines      = 0;
static unsigned int columns    = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static unsigned int border_width = 0;

