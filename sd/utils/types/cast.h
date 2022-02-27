/**
 * This file contains macros
 * for type casting
 */

#ifndef LOCK_CAST
#  define LOCK_CAST

#  define CAST_i8 *(char*)
#  define CAST_u8 *(unsigned char*)
#  define CAST_i8p (char*)
#  define CAST_u8p (unsigned char*)

#  define CAST_i16 *(short*)
#  define CAST_u16 *(unsigned short*)
#  define CAST_i16p (short*)
#  define CAST_u16p (unsigned short*)

#  define CAST_i32 *(int*)
#  define CAST_u32 *(unsigned int*)
#  define CAST_i32p (int*)
#  define CAST_u32p (unsigned int*)

#  define CAST_f32 *(float*)
#  define CAST_f32p (float*)

#  define CAST_i64 *(long*)
#  define CAST_u64 *(unsigned long*)
#  define CAST_i64p (long*)
#  define CAST_u64p (unsigned long*)

#  define CAST_d64 *(double*)
#  define CAST_d64p (double*)

#  define CAST_addr (void*)

#endif
