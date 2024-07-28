#ifndef UTILS_H
#define UTILS_H

// see what exactly the string has
void debug_print(char *s);
// remove non-ascii thingies
void clean_string(char *s);
// printif but returns the string instead of printing
char *string_printf(const char *format, ...);

#endif
