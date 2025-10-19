#include "apps.h"
#include "cmd.h"
#include "mode_check.h"
#include "optimize.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main() {
  int null_fd = open("/dev/null", O_WRONLY);
  dup2(null_fd, STDOUT_FILENO);
  dup2(null_fd, STDERR_FILENO);
  close(null_fd);

  init_app_mode();

  show_toast("RiProG PlayBoost: Initialized");
  sleep(10);
  show_toast("RiProG PlayBoost is now active in the background");

  const char *filePath = NULL;
  if (app_mode == MODE_STANDARD) {
    filePath = "/storage/emulated/0/Android/RPB_applist.txt";
  } else if (app_mode == MODE_AXERON) {
    filePath = "/data/local/tmp/AxManager/bin/added_apps.txt";
  } else {
    return 0;
  }

  char apps[MAX_APPS][MAX_NAME];
  int app_count = 0;
  struct stat st;
  time_t last_mtime = 0;
  load_apps(filePath, apps, &app_count);
  if (stat(filePath, &st) == 0)
    last_mtime = st.st_mtime;

  int is_optimizing = 0;

  while (1) {
    if (stat(filePath, &st) == 0 && st.st_mtime != last_mtime) {
      last_mtime = st.st_mtime;
      load_apps(filePath, apps, &app_count);
      show_toast("RiProG PlayBoost: App list updated");
    }

    FILE *fp = popen("cmd activity stack list", "r");
    char buffer[512] = "";
    int app_found = 0;
    char detected_apps[MAX_APPS][MAX_NAME];
    int detected_count = 0;

    if (fp != NULL) {
      while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "visible=true") == NULL)
          continue;
        for (int i = 0; i < app_count; i++) {
          if (strstr(buffer, apps[i]) != NULL) {
            app_found = 1;
            strncpy(detected_apps[detected_count], apps[i], MAX_NAME - 1);
            detected_apps[detected_count][MAX_NAME - 1] = '\0';
            detected_count++;
            break;
          }
        }
      }
      pclose(fp);
    }

    if (app_found) {
      if (!is_optimizing) {
        show_toast("RiProG PlayBoost: App detected, optimizing...");
        sleep(10);
        show_toast("RiProG PlayBoost: Real-time optimization active");
        is_optimizing = 1;
      }
      for (int i = 0; i < detected_count; i++) {
        optimize_app(detected_apps[i]);
      }
    } else {
      if (is_optimizing) {
        show_toast("RiProG PlayBoost: Real-time optimization stopped");
        sleep(10);
        show_toast("RiProG PlayBoost: App closed");
        is_optimizing = 0;
        clear_optimized_set();
      }
    }

    sleep(10);
  }

  return 0;
}