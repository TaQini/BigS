// GAME
#define KEY_ESCAPE	0x1B
#define KEY_SPACE	0x20
#define MAP_WIDHT  	24
#define MAP_HEIGHT 	24

#define INIT_LENGTH 4
#define INIT_LIFE	5

#define TIME_BASE   300
#define TIME_MIN    150
#define TIME_UPUNIT 50
 
// DIRECTOR
#define DIR_UP         0  
#define DIR_DOWN       1  
#define DIR_LEFT       2  
#define DIR_RIGHT      3  

// COLOR
#define WHITE	1.0f,1.0f,1.0f
#define BLACK   0.0f,0.0f,0.0f

#define YELLOW 	1.0f,1.0f,0.0f
#define BLUE	0.0f,0.0f,1.0f
#define RED		1.0f,0.0f,0.0f
#define ORANGE	1.0f,0.5f,0.0f

#define GREEN		0.0f,1.0f,0.0f
#define DARK_GREEN	0.0f,0.7f,0.0f
#define DARK_GREY	0.2f,0.2f,0.2f

// NUMBER
#define C00 "   ___  "
#define C01 "  / _ \\ "
#define C02 " | | | |"
#define C03 " | | | |"
#define C04 " | |_| |"
#define C05 "  \\___/ "

#define C10 "   __   "
#define C11 "  /_ |  "
#define C12 "   | |  "
#define C13 "   | |  "
#define C14 "   | |  "
#define C15 "   |_|  "

#define C20 "   ___  "
#define C21 "  |__ \\ "
#define C22 "     ) |"
#define C23 "    / / "
#define C24 "   / /_ "
#define C25 "  |____|"

#define C30 "  ____  "
#define C31 " |___ \\ "
#define C32 "   __) |"
#define C33 "  |__ < "
#define C34 "  ___) |"
#define C35 " |____/ "

#define C40 " _  _   "
#define C41 "| || |  "
#define C42 "| || |_ "
#define C43 "|__   _|"
#define C44 "   | |  "
#define C45 "   |_|  "

#define C50 "  _____ "
#define C51 " | ____|"
#define C52 " | |__  "
#define C53 " |___ \\ "
#define C54 "  ___) |"
#define C55 " |____/ "

#define C60 "    __  "
#define C61 "   / /  "
#define C62 "  / /_  "
#define C63 " | '_ \\ "
#define C64 " | (_) |"
#define C65 "  \\___/ "

#define C70 " ______ "
#define C71 "|____  |"
#define C72 "    / / "
#define C73 "   / /  "
#define C74 "  / /   "
#define C75 " /_/    "

#define C80 "   ___  "
#define C81 "  / _ \\ "
#define C82 " | (_) |"
#define C83 "  > _ < "
#define C84 " | (_) |"
#define C85 "  \\___/ "

#define C90 "   ___  "
#define C91 "  / _ \\ "
#define C92 " | (_) |"
#define C93 "  \\__  |"
#define C94 "    / / "
#define C95 "   /_/  "

// MESSAGE
#define YELLOW_BEAN 	"Score +1"
#define BLUE_NORMAL 	"Score +3, Length -1"
#define BLUE_EXTRAL 	"Score +3, Length -2, Life +1"
#define BLUE_CANTCUT 	"Life +2"
#define RED_CASE_1		"Score +5, Life +3"
#define RED_CASE_2		"Life +10"
#define RED_CASE_3		"Length -%d"
#define RED_CANTCUT 	"Score +5, Life +5"
#define RARE_BEAN		"Length Back to 2! Life +10!"
#define CRASH_SELF		"Crash yourself :)  -1s"
#define CRASH_WALL		"Crash the wall!  -1s"
#define GAMEBOX_INFO	"Life: %d   Score: %d"
#define SPEED_UP 		"SPEED UP !!"
#define SPEED_MAX		"MAX SPEED !!"
#define SPEED_CRAZY		"CRAZY MODE !!"
#define	GAMEOVER_INFO	"GAME OVER !!  Final SCORE: %d"
#define BYEBYE			"BYE BYE !!"
#define PAUSE_INFO		"Press SPACE to continue"
#define NULL_MSG		"    "
#define SUPER_MODE		"Spuer MODE opened !!"