#ifndef CML_UTILS_H
#define CML_UTILS_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


#include <sys/types.h>
#include <stddef.h>


typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t i128;


typedef u_int8_t u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;
typedef __uint128_t u128;


typedef double f64;


#include <time.h>
#ifndef CML_TIME
#define CML_TIME time
#endif

#include <string.h>
#ifndef CML_STRNCPY
#define CML_STRNCPY strncpy
#endif

#ifndef CML_STRERROR
#define CML_STRERROR strerror
#endif

#include <stdio.h>
#ifndef CML_PUTS
#define CML_PUTS puts
#endif

#ifndef CML_PRINTF
#define CML_PRINTF printf
#endif

#ifndef CML_MEMSET
#define CML_MEMSET memset
#endif

#include <stdlib.h>
#ifndef CML_MALLOC
#define CML_MALLOC malloc
#endif

#ifndef CML_CALLOC
#define CML_CALLOC calloc
#endif

#ifndef CML_FREE
#define CML_FREE free
#endif

#include <stdbool.h>

#ifndef CML_QSORT 
#define CML_QSORT qsort
#endif

/*
    DATA STRUCTURE FOR HOLDING ERROR VALUES
        1) _errno    =>  holds the error value in errno in single threaded programs or the error value return by
                      a threadfunction in a multithreaded program

        2) ret       =>  zero on success,-1 otherwise
        3) retptr    =>  for functions that return a pointer result(eg. mmap()). null on error,and _errno is set effectively
*/


typedef struct CML_Ret
{
    u64 _errno;
    i64 ret;
    void *retptr;
}CML_Ret;






/*****************************************************POLICY*********************************************** */
/*
                ERROR HANDLING WORKS LIKE A STACK. THE RESOURCES ARE ALLOCATED IN THE RESPECTIVE SUBROUTINES 
                WITHOUT HAVING TO WORRY ABOUT DEALLOCATION.

                DEALLOCATION HAPPENS IN A LIFO MANNER. THE Nth RESOURCE GETS DEALLOCATED FOLLOWED BY THE (N-1)th RESOURCE UPTO THE 1st RESOURCE THAT WAS ALLOCATED

                EACH ALLOCATION CORRESPONDS TO A DEALLOCATION LABEL

                THAT WAY NO DANGLING RESOURCES OCCUR WHICH MAY LEAD TO RESOURCES' LEAK
*/




/*****************************************************MECHANISM********************************************* */

/*
    MACRO TO DEFER RETURN STATEMENTS
    MAKES IT EASIER TO PERFORM CLEANUPS BY ABSTRACTING AWAY ALL THE REPITITIVE CODE
    CLEANUP IS PERFORMED IN THE RESPECTIVE JUMP LABEL

    INPUT       : JUMP LABEL AND ERROR CODE(ERRNO)
    OUTPUT      : NO OUTPUT
    SIDEEFFECT  : ASSIGNS A PREDECLARED VARIABLE NAMED "status" THE 
                  VALUE IN "code" AND THEN JUMPS TO A PREDECLARED LABEL NAMED THE VALUE OF "label"

    ASSUMPTIONS : THE CODE VALUE IS AN INTEGRAL VALUE
                  THE VALUE OF LABEL IS AN EXISTING LOCAL LABEL
*/

#define CML_RETURN_DEFER(label,code) status = (code);   goto label

#define CML_RETURN_DEFER_NO_ERRNO(label) goto label;

#include <errno.h>


#define CML_CHECK_NULL(val)                 (val)  == NULL
#define CML_CHECK_EQUAL(val1,val2)          (val1) == (val2)
#define CML_CHECK_NOT_EQUAL(val1,val2)      (val1) != (val2)



#define CML_CHECK_ERROR(val)             CML_CHECK_EQUAL((val).ret,-1)
#define CML_PRINT_ERROR(val)             CML_PUTS(CML_STRERROR((val)._errno))
#define CML_STORE_ERROR(buf,val,size)    CML_STRNCPY((buf),CML_STRERROR((val)._errno),(size))



#define CML_RESET_ERRNO(val)             errno = (val)





/*
 *  
 *      AUTHOR  : ARIEL ODUOR
 *      WHAT    : A MULTI-PURPOSE LIBRARY WITH AN EYE FOR COMPUTER
 *                   SECURITY AND SECURITY TESTING
 *      PURPOSE : PROVIDE A STANDARD FOR SECURITY TESTING WHILE AT THE SAME
 *            IOR_DSA IS DEFINED THEN WE USE CML DEFINED DATA STRUCTURES AND ALGORITHMS 
 *      WITH NO RELIANCE ON THE LANGUAGE DEFINED STANDARD LIBRARY ELSE WE USE THE STANDARD
 *      LIBRARY'S DSA
 * 
 *      A USER OF THE LIBRARY CAN CHOOSE TO USE THEIR OWN DATA STRUCTURES BY DEFININING THE
 *      MACRO CML_DSA AND THEN PROVIDING THEIR OWN IMPLEMENTATION SUPPORTING THE SAME 
 *      OPERATIONS =>  BREAKING THAT ASSUMPTION BREAKS THE ENTIRE LIBRARY
 * 
*/



#define CML_OS_LINUX_64

#if defined(CML_OS_LINUX_64)
#define CML_OS_LINUX
#else 
#if defined(CML_OS_LINUX_32)
#define CML_OS_LINUX
#endif
#endif





/*
 *
 *      ALL CML DEFINED DATA TYPES ARE NAMED IN CAPS,PRECEDED BY PREFIX 
 *      "CML_" AND END WITH SUFFIX "_t"
 * 
 *      ALL CML DEFINED SUBROUTINES ARE PRECEDED BY PREFIX "CML" AND
 *      FOLLOW THE FOLLOWING CONVENTIONS::
 *              1) A SYSTEM CALL IS FOLLOWED BY A "sys_" eg. 
 *                  "CML_sys_open" DENOTES THE "open" SYSTEM CALL
 *              2) A STDLIB CALL IS FOLLOWED BY A "lib_" eg. 
 *                  "CML_lib_fopen" DENOTES THE "fopen" STDLIB CALL
 *              3) A CUSTOM SUBROUTINE IS FOLLOWED BY THE NAME OF THE FILE 
 *                  CONTAINING THE CUSTOM SUBROUTINE "CML_<filename>_"
 *                   eg. "CML_users_login" DENOTES A "login" FUNCTION
 *                      IN THE "users.hpp" HEADER FILE
 *              4) THE FIRST PARAMETER OF EVERY SUBROUTINE IS A POINTER TO
 *                  A USER ALLOCATED "CML_ERROR_t" STRUCTURE WHICH 
 *                   STORES THE ERROR CODE AND ERROR MESSAGE IF ANY(ERROR 
 *                    HANDLING)
 * 
 *
*/





#define CML_ARRAY_LEN(array) sizeof((array))/sizeof((array)[0])




#define ANSI_RESET_ALL          "\x1b[0m%s"

#define ANSI_COLOR_BLACK        "\x1b[30m%s"
#define ANSI_COLOR_RED          "\x1b[31m%s"
#define ANSI_COLOR_GREEN        "\x1b[32m%s"
#define ANSI_COLOR_YELLOW       "\x1b[33m%s"
#define ANSI_COLOR_BLUE         "\x1b[34m%s"
#define ANSI_COLOR_MAGENTA      "\x1b[35m%s"
#define ANSI_COLOR_CYAN         "\x1b[36m%s"
#define ANSI_COLOR_WHITE        "\x1b[37m%s"

#define ANSI_COLOR_BOLD_BLACK        "\x1b[1;30m%s"
#define ANSI_COLOR_BOLD_RED          "\x1b[1;31m%s"
#define ANSI_COLOR_BOLD_GREEN        "\x1b[1;32m%s"
#define ANSI_COLOR_BOLD_YELLOW       "\x1b[1;33m%s"
#define ANSI_COLOR_BOLD_BLUE         "\x1b[1;34m%s"
#define ANSI_COLOR_BOLD_MAGENTA      "\x1b[1;35m%s"
#define ANSI_COLOR_BOLD_CYAN         "\x1b[1;36m%s"
#define ANSI_COLOR_BOLD_WHITE        "\x1b[1;37m%s"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m%s"
#define ANSI_BACKGROUND_RED     "\x1b[41m%s"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m%s"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m%s"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m%s"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m%s"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m%s"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m%s"

#define ANSI_BACKGROUND_BOLD_BLACK   "\x1b[1;40m%s"
#define ANSI_BACKGROUND_BOLD_RED     "\x1b[1;41m%s"
#define ANSI_BACKGROUND_BOLD_GREEN   "\x1b[1;42m%s"
#define ANSI_BACKGROUND_BOLD_YELLOW  "\x1b[1;43m%s"
#define ANSI_BACKGROUND_BOLD_BLUE    "\x1b[1;44m%s"
#define ANSI_BACKGROUND_BOLD_MAGENTA "\x1b[1;45m%s"
#define ANSI_BACKGROUND_BOLD_CYAN    "\x1b[1;46m%s"
#define ANSI_BACKGROUND_BOLD_WHITE   "\x1b[1;47m%s"

#define ANSI_COLOR_ITALIC_BLACK        "\x1b[3;30m%s"
#define ANSI_COLOR_ITALIC_RED          "\x1b[3;31m%s"
#define ANSI_COLOR_ITALIC_GREEN        "\x1b[3;32m%s"
#define ANSI_COLOR_ITALIC_YELLOW       "\x1b[3;33m%s"
#define ANSI_COLOR_ITALIC_BLUE         "\x1b[3;34m%s"
#define ANSI_COLOR_ITALIC_MAGENTA      "\x1b[3;35m%s"
#define ANSI_COLOR_ITALIC_CYAN         "\x1b[3;36m%s"
#define ANSI_COLOR_ITALIC_WHITE        "\x1b[3;37m%s"

#define ANSI_COLOR_UNDERLINE_BLACK        "\x1b[4;30m%s"
#define ANSI_COLOR_UNDERLINE_RED          "\x1b[4;31m%s"
#define ANSI_COLOR_UNDERLINE_GREEN        "\x1b[4;32m%s"
#define ANSI_COLOR_UNDERLINE_YELLOW       "\x1b[4;33m%s"
#define ANSI_COLOR_UNDERLINE_BLUE         "\x1b[4;34m%s"
#define ANSI_COLOR_UNDERLINE_MAGENTA      "\x1b[4;35m%s"
#define ANSI_COLOR_UNDERLINE_CYAN         "\x1b[4;36m%s"
#define ANSI_COLOR_UNDERLINE_WHITE        "\x1b[4;37m%s"

#define ANSI_STYLE_BOLD         "\x1b[1m%s"
#define ANSI_STYLE_ITALIC       "\x1b[3m%s"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m%s"


void print_reset();


void print_black(const char *str);
void print_red(const char *str);
void print_green(const char *str);
void print_yellow(const char *str);
void print_blue(const char *str);
void print_magenta(const char *str);
void print_cyan(const char *str);
void print_white(const char *str);


void print_bold_black(const char *str);
void print_bold_red(const char *str);
void print_bold_green(const char *str);
void print_bold_yellow(const char *str);
void print_bold_blue(const char *str);
void print_bold_magenta(const char *str);
void print_bold_cyan(const char *str);
void print_bold_white(const char *str);


void print_italic_black(const char *str);
void print_italic_red(const char *str);
void print_italic_green(const char *str);
void print_italic_yellow(const char *str);
void print_italic_blue(const char *str);
void print_italic_magenta(const char *str);
void print_italic_cyan(const char *str);
void print_italic_white(const char *str);


void print_underline_black(const char *str);
void print_underline_red(const char *str);
void print_underline_green(const char *str);
void print_underline_yellow(const char *str);
void print_underline_blue(const char *str);
void print_underline_magenta(const char *str);
void print_underline_cyan(const char *str);
void print_underline_white(const char *str);


void print_background_black(const char *str);
void print_background_red(const char *str);
void print_background_green(const char *str);
void print_background_yellow(const char *str);
void print_background_blue(const char *str);
void print_background_magenta(const char *str);
void print_background_cyan(const char *str);
void print_background_white(const char *str);


void print_background_bold_black(const char *str);
void print_background_bold_red(const char *str);
void print_background_bold_green(const char *str);
void print_background_bold_yellow(const char *str);
void print_background_bold_blue(const char *str);
void print_background_bold_magenta(const char *str);
void print_background_bold_cyan(const char *str);
void print_background_bold_white(const char *str);


void print_bold(const char *str);
void print_italic(const char *str);
void print_underline(const char *str);


typedef enum CML_TermColor
{
    TERM_COLOR_BLACK,
    TERM_COLOR_RED,
    TERM_COLOR_GREEN,
    TERM_COLOR_YELLOW,
    TERM_COLOR_BLUE,
    TERM_COLOR_MAGENTA,
    TERM_COLOR_CYAN,
    TERM_COLOR_WHITE
}CML_TermColor;



#endif
