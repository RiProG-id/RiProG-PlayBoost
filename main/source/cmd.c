#include "cmd.h"
#include "mode_check.h"
#include <stdlib.h>
#include <unistd.h>

void run_cmd(const char *argv[]) {
  pid_t pid = fork();
  if (pid == 0) {
    execvp(argv[0], (char *const *)argv);
    _exit(127);
  }
}

void show_toast(const char *msg) {
  if (app_mode == MODE_STANDARD) {
    const char *argv[] = {
        "am", "start",     "-n", "com.riprog.toast/.MainActivity",
        "-e", "toasttext", msg,  NULL};
    run_cmd(argv);
  } else if (app_mode == MODE_AXERON) {
    const char *argv[] = {"am", "start", "-n", "com.frb.axmanager/.Toast",
                          "-e", "text",  msg,  NULL};
    run_cmd(argv);
  }
}