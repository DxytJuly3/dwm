/* See LICENSE file for copyright and license details. */

/* appearance */

 static int showsystray						= 1;         /* 是否显示托盘栏 */
static const int newclientathead			= 0;         /* 定义新窗口在栈顶还是栈底 */
static const unsigned int borderpx			= 2;         /* 窗口边框大小 */
static const unsigned int systraypinning	= 1;         /* 托盘跟随的显示器 0代表不指定显示器 */
static const unsigned int systrayspacing	= 1;         /* 托盘间距 */
static const unsigned int systrayspadding	= 5;         /* 托盘和状态栏的间隙 */
static int gappi							= 7;        /* 窗口与窗口 缝隙大小 */
static int gappo							= 7;        /* 窗口与边缘 缝隙大小 */
static const int _gappo						= 12;        /* 窗口与窗口 缝隙大小 不可变 用于恢复时的默认值 */
static const int _gappi						= 12;        /* 窗口与边缘 缝隙大小 不可变 用于恢复时的默认值 */
static const int vertpad					= 5;         /* vertical padding of bar */
static const int sidepad					= 5;         /* horizontal padding of bar */
static const int overviewgappi				= 24;        /* overview时 窗口与边缘 缝隙大小 */
static const int overviewgappo				= 60;        /* overview时 窗口与窗口 缝隙大小 */
static const int showbar					= 1;         /* 是否显示状态栏 */
static const int topbar						= 0;         /* 指定状态栏位置 0底部 1顶部 */
static const float mfact					= 0.6;       /* 主工作区 大小比例 */
static const int   nmaster					= 1;         /* 主工作区 窗口数量 */
static const unsigned int snap				= 7;        /* 边缘依附宽度 */
static const unsigned int baralpha			= 0xa0;      /* 状态栏透明度 */
static const unsigned int borderalpha		= 0x9d;      /* 边框透明度 */
static const int user_bh					= 8;         /* 2 is the default spacing around the bar's font */
static const char *fonts[]					= {
	"Fira Code:size=15:type=Bold",
	"PingFangMedium:size=15:type=Bold:antialias=true:autohint=true"
	"SauceCodePro NF Bold:size=15:type=Bold:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Fira Code:size=15:type=Bold";
static const char col_gray1[]       = "#282A36";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#F1FA8C";
static const char col_gray4[]       = "#444444";
static const char col_cyan[]        = "#BD93F9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { " ", " ", "󰊯 ", " ", " ", " ", " ", "󰘐 ", " " };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			     instance			   title			 tags mask     isfloating		CenterThisWindow?     monitor */
    /** 优先级高 越在上面优先度越高 */
    /** 普通优先度 */
    { "st",                  NULL,                 NULL,             0,            0,				1,					  -1 },
    { "chrome",              NULL,                 NULL,             1 << 2,       0,				1,					  -1 }, // chrome     
    { NULL,                  "qq",                 NULL,             1 << 3,       0,				1,					  -1 }, // qq        
    { "typora",              NULL,                 NULL,             1 << 5,       1,				1,					  -1 }, // typora          
	{ "Gimp",				 NULL,				   NULL,		     0,            1,				0,                    -1 },
	{ "dev",				 NULL,				   NULL,			 1 << 8,       1,				1,                    -1 },
	{ "code",				 NULL,				   NULL,			 1 << 7,       1,				1,                    -1 },
	{ "studio",				 NULL,				   NULL,			 1 << 6,       0,				1,                    -1 },
};

/* layout(s) */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask 
#define LiLower XF86XK_MonBrightnessDown
#define LiRaise XF86XK_MonBrightnessUp
#define AuMute  XF86XK_AudioMute
#define AuLower XF86XK_AudioLowerVolume
#define AuRaise XF86XK_AudioRaiseVolume
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static const char *lightdown[] = { "/home/july/App/newDWM/dwm/diyscript/lightdown.sh", NULL };
static const char *lightup[] = { "/home/july/App/newDWM/dwm/diyscript/lightup.sh", NULL };
static const char *voldown[] = { "/home/july/App/newDWM/dwm/diyscript/voldown.sh", NULL };
static const char *volup[] = { "/home/july/App/newDWM/dwm/diyscript/volup.sh", NULL };
static const char *voltoggle[] = { "/home/july/App/newDWM/dwm/diyscript/voltoggle.sh", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *flameshotcmd[] = { "/home/july/App/newDWM/dwm/diyscript/flameshot.sh", NULL }; 

static const Key keys[] = {
    /* modifier                     key             function            argument */
    { 0,                            LiLower,        spawn,              {.v = lightdown} },                 // 静音
    { 0,                            LiRaise,        spawn,              {.v = lightup} },                 // 静音
    { 0,                            AuMute,         spawn,              {.v = voltoggle} },                 // 静音
    { 0,                            AuLower,        spawn,              {.v = voldown} },                  // 音量减 2%
    { 0,                            AuRaise,        spawn,              {.v = volup} },                    // 音量加 2%
	{ Mod1Mask|ControlMask,			XK_x,			spawn,				{.v = flameshotcmd} },
	{ Mod1Mask,						XK_i,			focusstack,			{.i = -1} },						/* Alt up           |  本tag内切换聚焦窗口 */
    { Mod1Mask,						XK_k,			focusstack,			{.i = +1} },						/* Alt down         |  本tag内切换聚焦窗口 */
    { Mod1Mask,						XK_j,			viewtoleft,			{0} },								/* Alt left         |  聚焦到左边的tag */
    { Mod1Mask,						XK_l,			viewtoright,		{0} },								/* Alt right        |  聚焦到右边的tag */
    { MODKEY,                       XK_p,           spawn,              {.v = dmenucmd } },                 // super + p                | 打开 dmenu
    { MODKEY,                       XK_Return,      spawn,              {.v = termcmd } },                  // super + enter            | 打开 terminal
    { MODKEY,                       XK_b,           togglebar,          {0} },                              // super + b                | 状态栏打开\关闭
    { MODKEY,                       XK_j,           focusstack,         {.i = +1 } },                       // super + j                | 切换为前一个 client
    { MODKEY,                       XK_k,           focusstack,         {.i = -1 } },                       // super + k                | 切换为后一个 client
    { MODKEY,                       XK_i,           incnmaster,         {.i = +1 } },                       // super + i                | 工作区设置为上下分布
    { MODKEY,                       XK_d,           incnmaster,         {.i = -1 } },                       // super + d                | 工作区设置为左右分布
    { MODKEY,                       XK_h,           setmfact,           {.f = -0.02} },                     // super + h                | 工作区中心线向左移动 0.02
    { MODKEY,                       XK_l,           setmfact,           {.f = +0.02} },                     // super + h                | 工作区中心线向右移动 0.02
    { MODKEY|ShiftMask,             XK_Return,      zoom,               {0} },                              // super + Shift + enter    | 当前聚焦窗口设置为主窗口
    { MODKEY,                       XK_Tab,         view,               {0} },                              // super + Tab              | 切换到上一个tag
    { MODKEY,                       XK_q,           killclient,         {0} },                              // super + q                | 关闭当前窗口
    { MODKEY,                       XK_t,           setlayout,          {.v = &layouts[0]} },               // super + t                | 切换为 列表窗口布局
    { MODKEY,                       XK_m,           setlayout,          {.v = &layouts[1]} },               // super + m                | 切换为 窗口铺满布局
    { MODKEY,                       XK_space,       setlayout,          {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating,     {0} },
    { MODKEY,                       XK_0,           view,               {.ui = ~0 } },                      // super + 0                | 预览所有tags窗口
    { MODKEY|ShiftMask,             XK_0,           tag,                {.ui = ~0 } },
    { MODKEY|ControlMask,           XK_F12,         quit,               {0} },                              // super + ctrl + F12       | 退出 dwm
	/* key tag cmd */
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },                          // super+左键窗口   |  拖拽窗口
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },                          // super+右键窗口   |  改变窗口大小
    { ClkTagBar,            0,              Button1,        view,           {0} },                          // 左键tag          |  切换tag
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },                          // 右键tag          |  选中tag
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },                          // super+左键tag    |  将当前聚焦窗口切换到tag
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },                          // super+右键tag    |  将当前聚焦窗口同步到tag
};


#define INPUT_FOCUS 1
