/**
 * This file contains
 * ANSI C espace
 * sequences for
 * color
 */

#ifndef LOCK_COLOR
#  define LOCK_COLOR

#  define ESC "\x1b["

#  define _RESET ESC "0m"

// -- style -- //
#  define BOLD ESC "1m"
#  define LIGHT ESC "2m"
#  define ITALICS ESC "3m"
#  define UNDERLINE ESC "4m"
#  define INVERT ESC "7m"

// -- color -- //
#  define GREY_FG ESC "30m"
#  define RED_FG ESC "31m"
#  define GREEN_FG ESC "32m"
#  define YELLOW_FG ESC "33m"
#  define BLUE_FG ESC "34m"
#  define PURPLE_FG ESC "35m"
#  define CYAN_FG ESC "36m"
#  define LGREY_FG ESC "37m"

#  define GREY_BG ESC "40m"
#  define RED_BG ESC "41m"
#  define GREEN_BG ESC "42m"
#  define YELLOW_BG ESC "43m"
#  define BLUE_BG ESC "44m"
#  define PURPLE_BG ESC "45m"
#  define CYAN_BG ESC "46m"
#  define LGREY_BG ESC "47m"

#  define LIGHT_GREY_FG ESC "90m"
#  define LIGHT_RED_FG ESC "91m"
#  define LIGHT_GREEN_FG ESC "92m"
#  define LIGHT_YELLOW_FG ESC "93m"
#  define LIGHT_BLUE_FG ESC "94m"
#  define LIGHT_PURPLE_FG ESC "95m"
#  define LIGHT_CYAN_FG ESC "96m"
#  define LIGHT_LGREY_FG ESC "97m"

#  define LIGHT_GREY_BG ESC "100m"
#  define LIGHT_RED_BG ESC "101m"
#  define LIGHT_GREEN_BG ESC "102m"
#  define LIGHT_YELLOW_BG ESC "103m"
#  define LIGHT_BLUE_BG ESC "104m"
#  define LIGHT_PURPLE_BG ESC "105m"
#  define LIGHT_CYAN_BG ESC "106m"
#  define LIGHT_LGREY_BG ESC "107m"

#endif
