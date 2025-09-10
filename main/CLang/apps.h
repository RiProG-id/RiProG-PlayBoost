#ifndef APPS_H
#define APPS_H

#define MAX_APPS 128
#define MAX_NAME 64

void load_apps(const char *filePath, char apps[MAX_APPS][MAX_NAME],
               int *app_count);

#endif