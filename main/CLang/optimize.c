#include "optimize.h"
#include "cmd.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void optimize_app(const char *app) {
  static char optimized_pids[1024][16];
  static int optimized_count = 0;

  char cmd[128];
  snprintf(cmd, sizeof(cmd), "pgrep -f %s", app);
  FILE *pid_fp = popen(cmd, "r");
  if (!pid_fp)
    return;

  char pid[16];
  while (fgets(pid, sizeof(pid), pid_fp) != NULL) {
    pid[strcspn(pid, "\n")] = 0;
    if (!isdigit((unsigned char)pid[0]))
      continue;

    char task_path[128];
    snprintf(task_path, sizeof(task_path), "/proc/%s/task/", pid);
    DIR *task_dir = opendir(task_path);
    if (!task_dir)
      continue;

    struct dirent *task_entry;
    while ((task_entry = readdir(task_dir)) != NULL) {
      if (task_entry->d_type != DT_DIR)
        continue;
      if (!isdigit((unsigned char)task_entry->d_name[0]))
        continue;

      int already = 0;
      for (int i = 0; i < optimized_count; i++) {
        if (strcmp(optimized_pids[i], task_entry->d_name) == 0) {
          already = 1;
          break;
        }
      }
      if (already)
        continue;

      if (optimized_count < 1024) {
        strncpy(optimized_pids[optimized_count], task_entry->d_name,
                sizeof(optimized_pids[optimized_count]) - 1);
        optimized_pids[optimized_count]
                      [sizeof(optimized_pids[optimized_count]) - 1] = '\0';
        optimized_count++;
      }

      const char *renice_argv[] = {"renice",           "-n", "-5", "-p",
                                   task_entry->d_name, NULL};
      run_cmd(renice_argv);

      const char *ionice_argv[] = {
          "ionice", "-c", "2", "-n", "2", "-p", task_entry->d_name, NULL};
      run_cmd(ionice_argv);

      const char *chrt_argv[] = {"chrt", "-r", "-p", "70", task_entry->d_name,
                                 NULL};
      run_cmd(chrt_argv);

      usleep(50000);
    }
    closedir(task_dir);
  }
  pclose(pid_fp);
}