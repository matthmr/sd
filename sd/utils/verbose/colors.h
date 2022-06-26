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
#  define __RESET__ __ESC__ "0m"

// -- style -- //
#  define __BOLD__ "1m"
#  define __LIGHT__ "2m"
#  define __ITALICS__ "3m"
#  define __UNDERLINE__ "4m"
#  define __INVERT__ "7m"
#  define BOLD(x) __ESC__ __BOLD__ x
#  define LIGHT(x) __ESC__ __LIGHT__ x
#  define ITALICS(x) __ESC__ __ITALICS__ x
#  define UNDERLINE(x) __ESC__ __UNDERLINE__ x
#  define INVERT(x) __ESC__ __INVERT__ x
#  define RESET(x) __RESET__ x

#  define STYLE(x,y) __ESC__ "0;" x y

// -- color -- //
//   -- foreground -- //
#  define GREY_FG(x) __ESC__ "30m" x
#  define RED_FG(x) __ESC__ "31m" x
#  define GREEN_FG(x) __ESC__ "32m" x
#  define YELLOW_FG(x) __ESC__ "33m" x
#  define BLUE_FG(x) __ESC__ "34m" x
#  define PURPLE_FG(x) __ESC__ "35m" x
#  define CYAN_FG(x) __ESC__ "36m" x
#  define LGREY_FG(x) __ESC__ "37m" x

#  define LIGHT_GREY_FG(x) __ESC__ "90m" x
#  define LIGHT_RED_FG(x) __ESC__ "91m" x
#  define LIGHT_GREEN_FG(x) __ESC__ "92m" x
#  define LIGHT_YELLOW_FG(x) __ESC__ "93m" x
#  define LIGHT_BLUE_FG(x) __ESC__ "94m" x 
#  define LIGHT_PURPLE_FG(x) __ESC__ "95m" x
#  define LIGHT_CYAN_FG(x) __ESC__ "96m" x
#  define LIGHT_LGREY_FG(x) __ESC__ "97m" x

//   -- background -- //
#  define GREY_BG(x) __ESC__ "40m" x
#  define RED_BG(x) __ESC__ "41m" x
#  define GREEN_BG(x) __ESC__ "42m" x
#  define YELLOW_BG(x) __ESC__ "43m" x
#  define BLUE_BG(x) __ESC__ "44m" x
#  define PURPLE_BG(x) __ESC__ "45m" x
#  define CYAN_BG(x) __ESC__ "46m" x
#  define LGREY_BG(x) __ESC__ "47m" x

#  define LIGHT_GREY_BG(x) __ESC__ "100m" x
#  define LIGHT_RED_BG(x) __ESC__ "101m" x
#  define LIGHT_GREEN_BG(x) __ESC__ "102m" x
#  define LIGHT_YELLOW_BG(x) __ESC__ "103m" x
#  define LIGHT_BLUE_BG(x) __ESC__ "104m" x
#  define LIGHT_PURPLE_BG(x) __ESC__ "105m" x
#  define LIGHT_CYAN_BG(x) __ESC__ "106m" x
#  define LIGHT_LGREY_BG(x) __ESC__ "107m" x

#endif
