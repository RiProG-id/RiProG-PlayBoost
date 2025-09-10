#include "optimize.h"
#include "cmd.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void optimize_app(const char *app) {
  char cmd[128];
  snprintf(cmd, sizeof(cmd), "pgrep -f %s", app);
  FILE *pid_fp = popen(cmd, "r");
  if (!pid_fp)
    return;

  char pid[16];
  while (fgets(pid, sizeof(pid), pid_fp) != NULL) {
    pid[strcspn(pid, "\n")] = 0;
    char task_path[128];
    snprintf(task_path, sizeof(task_path), "/proc/%s/task/", pid);
    DIR *task_dir = opendir(task_path);
    if (task_dir) {
      struct dirent *task_entry;
      while ((task_entry = readdir(task_dir)) != NULL) {
        if (task_entry->d_type == DT_DIR &&
            strcmp(task_entry->d_name, ".") != 0 &&
            strcmp(task_entry->d_name, "..") != 0) {
          const char *renice_argv[] = {"renice",           "-n", "-20", "-p",
                                       task_entry->d_name, NULL};
          run_cmd(renice_argv);
          const char *ionice_argv[] = {
              "ionice", "-c", "1", "-n", "0", "-p", task_entry->d_name, NULL};
          run_cmd(ionice_argv);
          const char *chrt_argv[] = {
              "chrt", "-f", "-p", "99", task_entry->d_name, NULL};
          run_cmd(chrt_argv);
          usleep(200000);
        }
      }
      closedir(task_dir);
    }
  }

  pclose(pid_fp);
}