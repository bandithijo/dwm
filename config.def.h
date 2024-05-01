/* See LICENSE file for copyright and license details. */

#include "exitdwm.c"
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 14;       /* gaps between windows */
static const int vertpad            = 14;       /* vertical padding of bar */
static const int sidepad            = 250;      /* horizontal padding of bar */
static const unsigned int snap      = 5;        /* snap pixel */
static const int user_bh            = 5;        /* 2 is the default spacing around the bar's font */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const int nmaxmaster         = 6;        /* maximum number of clients allowed in master area */
static const char *fonts[]          = {
	"JetBrainsMono Nerd Font Bandit:style=Medium:pixelsize=15",
	"Twitter Color Emoji:pixelsize=15:antialias=true:autohint=true",
};
static const char dmenufont[]       = "JetBrainsMono Nerd Font Bandit:style=Medium:pixelsize=15";
static const char col_gray1[]       = "#1e1e1e";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005f87";
static const char col_red[]         = "#FF0000";
static const char col_orange[]      = "#FF8800";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeScratchSel]  = { col_gray4, col_cyan,  col_red  },
	[SchemeScratchNorm] = { col_gray4, col_cyan,  col_orange },
};

/* autostart */
static const char *const autostart[] = {
	"dwmstatus", NULL,
	"dunst", "-config", "~/.config/dunst/dunstrc", NULL,
	"xcompmgr", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] =     { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
static const int taglayouts[] = {  0,   2,   0,   0,   2,   0,   2,   2,   0,   0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                      instance                title                      tags mask   iscentered   isfloating   monitor		scratch key */
	/* Non FLoating */
	{ "Gimp-2.10",                NULL,                   NULL,                      0,          1,           0,           -1,          0 },
	{ "firefox",                  NULL,                   NULL,                      2,          1,           0,           -1,          0 },
	{ "Google-chrome",            NULL,                   NULL,                      2,          1,           0,           -1,          0 },
	{ "TelegramDesktop",          NULL,                   NULL,                      1 << 7,     1,           0,           -1,          0 },
	{ "discord",                  NULL,                   NULL,                      1 << 7,     1,           0,           -1,          0 },
	{ "Slack",                    NULL,                   NULL,                      1 << 7,     1,           0,           -1,          0 },
	{ "calibre",                  NULL,                   NULL,                      0,          1,           0,           -1,          0 },
	{ "Evince",                   NULL,                   NULL,                      0,          1,           0,           -1,          0 },
	{ "DBeaver",                  NULL,                   NULL,                      1 << 4,     1,           0,           -1,          0 },
	{ "St",                       NULL,                   "st",                      0,          1,           0,           -1,          0 },
	{ "St",                       NULL,                   "Ranger",                  0,          1,           0,           -1,          0 },
	{ "St",                       NULL,                   "Neomutt",                 1 << 6,     1,           0,           -1,          0 },
	{ "St",                       NULL,                   "Newsboat",                1 << 6,     1,           0,           -1,          0 },
	{ "St",                       NULL,                   "WeeChat",                 1 << 6,     1,           0,           -1,          0 },
	/* class                      instance                title                      tags mask   iscentered   isfloating   monitor		scratch key */
	/* FLoating */
	{ "St",                       NULL,                   "st^",                     0,          1,           1,           -1,          0 },
	{ "St",                       NULL,                   "st^:",                    0,          0,           1,           -1,          0 },
	{ "Xdg-desktop-portal-gtk",   NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "gnome-system-monitor",     NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "gnome-calculator",         NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "gnome-calendar",           NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "snapshot",                 NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "org.gnome.Nautilus",       NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "org.gnome.Characters",     NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "io.github.celluloid_player.Celluloid", NULL,       NULL,                      0,          1,           1,           -1,          0 },
	{ "mpv",                      NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Arandr",                   NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Gcolor2",                  NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Gcolor3",                  NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "SimpleScreenRecorder",     NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Barrier",                  NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Pavucontrol",              NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "vokoscreen",               NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Blueman-manager",          NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "GParted",                  NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Crow Translate",           NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Dragon-drag-and-drop",     NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Dragon",                   NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Soundconverter",           "Soundconverter",       "Soundconverter",          0,          1,           1,           -1,          0 },
	{ "System-config-printer.py", NULL,                   NULL,                      0,          1,           1,           -1,          0 },
	{ "Nm-connection-editor",     NULL,                   "Network Connections",     0,          1,           1,           -1,          0 },
	{ "Thunar",                   "thunar",               "File Operation Progress", 0,          1,           1,           -1,          0 },
	{ "Java",                     "java",                 "Dbeaver",                 1 << 4,     1,           1,           -1,          0 },
	/* class                      instance                title                      tags mask   iscentered   isfloating   monitor		scratch key */
	/* Scratchpad */
	{ NULL,                       NULL,                   "scratchpad",              0,          0,           1,           -1,          's' },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      col },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "j4-dmenu-desktop", "--dmenu=dmenu -i -p ' Apps:'", "--no-generic", "--use-xdg-de", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-display-drun", " Apps", "-theme-str", "window {width: 25%; height: 14.6%;}", "-i", "-sort", "-location", "0", NULL };
static const char *termcmd[]  = { "st", NULL };
/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", "st", "-t", "scratchpad", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_minus,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_minus,  removescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ControlMask,           XK_minus,  setscratch,     {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_r,      resetlayout,    {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,		    XK_l,	   movekeyboard_x, {.i = 20}},
	{ MODKEY|ControlMask,		    XK_h,	   movekeyboard_x, {.i = -20}},
	{ MODKEY|ControlMask,		    XK_j,	   movekeyboard_y, {.i = 20}},
	{ MODKEY|ControlMask,		    XK_k,	   movekeyboard_y, {.i = -20}},
	{ MODKEY|ShiftMask,             XK_Up,     movethrow,      {.ui = DIR_N }},
	{ MODKEY|ShiftMask,             XK_Down,   movethrow,      {.ui = DIR_S }},
	{ MODKEY|ShiftMask,             XK_Left,   movethrow,      {.ui = DIR_W }},
	{ MODKEY|ShiftMask,             XK_Right,  movethrow,      {.ui = DIR_E }},
	{ MODKEY|ShiftMask,             XK_m,      movethrow,      {.ui = DIR_C }},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      exitdwm,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

