/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"xos4 Terminus:size=8"
};
static const char dmenufont[]       = "xos4 Terminus:size=8";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#ffffff", "#222222", "#444444" },
	[SchemeSel] =  { "#ffffff", "#005577",  "#005577" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "mplayer2", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL }    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#222222", "-nf", "#ffffff", "-sb", "#005577", "-sf", "#ffffff", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *filescmd[]  = { "st", "-e", "rover", NULL };
static const char *alttermcmd[]  = { "st", "-e", "tmux", NULL };
static const char *browsecmd[]  = { "firefox", NULL };
static const char *altbrowsecmd[]  = { "chromium", NULL };
static const char *altaltbrowsecmd[]  = { "firefox", "-P", "po", "--no-remote", NULL };
static const char *editorcmd[]  = { "gvim", NULL };
static const char *moncmd[]  = { "st", "-e", "htop", NULL };
static const char *mixcmd[]  = { "st", "-e", "alsamixer", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *steamcmd[]  = { "steam-runtime", NULL };
static const char *keycmd[]  = { "kgpg", "-k", NULL };
static const char *filebrowsercmd[]  = { "st", "-e", "nnn", NULL };
static const char *altfilebrowsercmd[]  = { "thunar", NULL };
static const char *mailcmd[]  = { "tutanota", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = alttermcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = browsecmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = altbrowsecmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = altaltbrowsecmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = mailcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = editorcmd } },
	{ MODKEY,                       XK_z,      spawn,          {.v = moncmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = mixcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = steamcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = keycmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = filebrowsercmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = altfilebrowsercmd } },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_u,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_y,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_y,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_u,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
//	{ MODKEY,                       XK_Return, zoom,           {0} },
//	{ MODKEY,                       XK_Tab,    view,           {0} },
//	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
//	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
//	{ ClkTagBar,            0,              Button1,        view,           {0} },
//	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
//	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
//	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

