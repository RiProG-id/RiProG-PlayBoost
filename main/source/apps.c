#include "apps.h"
#include <stdio.h>
#include <string.h>

void load_apps(const char *filePath, char apps[MAX_APPS][MAX_NAME],
               int *app_count) {
  *app_count = 0;
  FILE *file = fopen(filePath, "r");
  if (file != NULL) {
    char line[MAX_NAME];
    while (fgets(line, sizeof(line), file) != NULL && *app_count < MAX_APPS) {
      line[strcspn(line, "\n")] = '\0';
      if (strlen(line) == 0)
        continue;
      strncpy(apps[*app_count], line, sizeof(apps[*app_count]) - 1);
      apps[*app_count][sizeof(apps[*app_count]) - 1] = '\0';
      (*app_count)++;
    }
    fclose(file);
  }
}