#ifndef MODE_CHECK_H
#define MODE_CHECK_H

enum { MODE_UNDEFINED, MODE_STANDARD, MODE_AXERON };

extern int app_mode;

void init_app_mode(void);

#endif