#include "optimize.h"
#include "cmd.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct TidNode {
  char tid[16];
  struct TidNode *next;
} TidNode;

static TidNode *optimized_set = NULL;

static int tid_exists(const char *tid) {
  TidNode *cur = optimized_set;
  while (cur) {
    if (strcmp(cur->tid, tid) == 0)
      return 1;
    cur = cur->next;
  }
  return 0;
}

static void add_tid(const char *tid) {
  if (tid_exists(tid))
    return;
  TidNode *node = malloc(sizeof(TidNode));
  if (!node)
    return;
  strncpy(node->tid, tid, sizeof(node->tid) - 1);
  node->tid[sizeof(node->tid) - 1] = '\0';
  node->next = optimized_set;
  optimized_set = node;
}

void clear_optimized_set(void) {
  TidNode *cur = optimized_set;
  while (cur) {
    TidNode *next = cur->next;
    free(cur);
    cur = next;
  }
  optimized_set = NULL;
}

void optimize_app(const char *app) {
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
      if (strcmp(task_entry->d_name, pid) == 0)
        continue;
      if (tid_exists(task_entry->d_name))
        continue;

      add_tid(task_entry->d_name);

      const char *taskset_argv[] = {"taskset", "-p", "0xffffffff",
                                    task_entry->d_name, NULL};
      run_cmd(taskset_argv);

      sleep(1);
    }
    closedir(task_dir);
  }
  pclose(pid_fp);
}