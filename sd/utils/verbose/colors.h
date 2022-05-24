/**
 * @file colors.h
 *
 * @brief ANSI escape sequences
 *
 * This file contains ANSI C
 * espace sequences for color
 */

#ifndef LOCK_COLOR
#  define LOCK_COLOR ///< lock: standard lock

#  define __ESC__ "\x1b["
#  define __RESET__ ESC "0m"

// -- style -- //
#  define BOLD(x) ESC "1m" (x) __RESET__
#  define LIGHT(x) ESC "2m" (x) __RESET__
#  define ITALICS(x) ESC "3m" (x) __RESET__
#  define UNDERLINE(x) ESC "4m" (x) __RESET__
#  define INVERT(x) ESC "7m" (x) __RESET__

// -- color -- //
//   -- foreground -- //
#  define GREY_FG(x) ESC "30m" (x) __RESET__
#  define RED_FG(x) ESC "31m" (x) __RESET__
#  define GREEN_FG(x) ESC "32m" (x) __RESET__
#  define YELLOW_FG(x) ESC "33m" (x) __RESET__
#  define BLUE_FG(x) ESC "34m" (x) __RESET__
#  define PURPLE_FG(x) ESC "35m" (x) __RESET__
#  define CYAN_FG(x) ESC "36m" (x) __RESET__
#  define LGREY_FG(x) ESC "37m" (x) __RESET__

#  define LIGHT_GREY_FG(x) ESC "90m" (x) __RESET__
#  define LIGHT_RED_FG(x) ESC "91m" (x) __RESET__
#  define LIGHT_GREEN_FG(x) ESC "92m" (x) __RESET__
#  define LIGHT_YELLOW_FG(x) ESC "93m" (x) __RESET__
#  define LIGHT_BLUE_FG(x) ESC "94m" (x) __RESET__
#  define LIGHT_PURPLE_FG(x) ESC "95m" (x) __RESET__
#  define LIGHT_CYAN_FG(x) ESC "96m" (x) __RESET__
#  define LIGHT_LGREY_FG(x) ESC "97m" (x) __RESET__

//   -- background -- //
#  define GREY_BG(x) ESC "40m" (x) __RESET__
#  define RED_BG(x) ESC "41m" (x) __RESET__
#  define GREEN_BG(x) ESC "42m" (x) __RESET__
#  define YELLOW_BG(x) ESC "43m" (x) __RESET__
#  define BLUE_BG(x) ESC "44m" (x) __RESET__
#  define PURPLE_BG(x) ESC "45m" (x) __RESET__
#  define CYAN_BG(x) ESC "46m" (x) __RESET__
#  define LGREY_BG(x) ESC "47m" (x) __RESET__

#  define LIGHT_GREY_BG(x) ESC "100m" (x) __RESET__
#  define LIGHT_RED_BG(x) ESC "101m" (x) __RESET__
#  define LIGHT_GREEN_BG(x) ESC "102m" (x) __RESET__
#  define LIGHT_YELLOW_BG(x) ESC "103m" (x) __RESET__
#  define LIGHT_BLUE_BG(x) ESC "104m" (x) __RESET__
#  define LIGHT_PURPLE_BG(x) ESC "105m" (x) __RESET__
#  define LIGHT_CYAN_BG(x) ESC "106m" (x) __RESET__
#  define LIGHT_LGREY_BG(x) ESC "107m" (x) __RESET__

#endif
