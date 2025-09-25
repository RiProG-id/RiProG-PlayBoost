#include "mode_check.h"
#include <stdio.h>
#include <string.h>

int app_mode = MODE_UNDEFINED;

void init_app_mode(void) {
  FILE *fp = popen("getprop debug.riprog.RPB", "r");
  if (!fp)
    return;

  char prop_value[32] = "";
  if (fgets(prop_value, sizeof(prop_value), fp) != NULL) {
    prop_value[strcspn(prop_value, "\n")] = 0;
  }
  pclose(fp);

  if (strcmp(prop_value, "standard") == 0) {
    app_mode = MODE_STANDARD;
  } else if (strcmp(prop_value, "axeron") == 0) {
    app_mode = MODE_AXERON;
  } else {
    app_mode = MODE_UNDEFINED;
  }
}