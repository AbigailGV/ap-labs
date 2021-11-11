#include <stdio.h>
#include "logger.h"
#include <stdarg.h>
#include <syslog.h>
#include <stdlib.h>
#include <string.h>

#define RESET 0
#define HIDDEN 7
#define ITALICS 2
#define BOLD 1
#define FAINT 2
#define UNDERLINE 3
#define STRIKETHROUGH 8
#define REVERSE 8

// colors for the prompt
#define BLACK 0
#define WHITE 7
#define RED 1
#define GREEN 2
#define MAGENTA 5
#define BLUE 4
#define CYAN 6
#define YELLOW 3
#define DEFAULT 9

void restartColor()
{
    printf("%c[0m\033[K", 0x1B);
}

int printStdOut(const char *format, va_list arguments)
{
    vprintf(format, arguments);
    restartColor();
    return 0;
}

int (*logger_func)(const char *format, va_list) = printStdOut;

void textcolor(int at, int fg, int bg)
{
    char command[13];

    sprintf(command, "%c[%d;%d;%dm", 0x1B, at, fg + 30, bg + 40);
    printf("%s", command);
}
int printSysLog(const char *format, va_list arguments)
{
    vsyslog(LOG_INFO, format, arguments);
    restartColor();
    return 0;
}

int initLogger(char *log_Type)
{
    printf("Initializing Logger on: %s\n", log_Type);

    if (strcmp(log_Type, "stdout") == 0)
    {
        logger_func = printStdOut;
    }
    else if (strcmp(log_Type, "syslog") == 0)
    {
        logger_func = printSysLog;
    }
    else
    {
        printf("Invalid logger");
    }
    return 0;
}

int infof(const char *format, ...)
{
    textcolor(BOLD, MAGENTA, DEFAULT);
    va_list arguments;
    va_start(arguments, format);
    logger_func(format, arguments);
    va_end(arguments);
    return 0;
}

int warnf(const char *format, ...)
{
    textcolor(BOLD, YELLOW, DEFAULT);
    va_list arguments;
    va_start(arguments, format);
    logger_func(format, arguments);
    va_end(arguments);
    return 0;
}

int errorf(const char *format, ...)
{
    textcolor(BOLD, RED, DEFAULT);
    va_list arguments;
    va_start(arguments, format);
    logger_func(format, arguments);
    va_end(arguments);
    return 0;
}

int panicf(const char *format, ...)
{
    textcolor(BOLD, CYAN, DEFAULT);
    va_list arguments;
    va_start(arguments, format);
    logger_func(format, arguments);
    va_end(arguments);
    return 0;
}