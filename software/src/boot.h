#ifndef boot_h
#define boot_h

typedef struct _cmd_t
{
  char *cmd;
  void
  (*func) (int *_result);
  struct _cmd_t *next;
  int index;
} cmd_t;

void Init_boot_command (int _config);

void Add_boot_command (const char * name,void (*func) (int *_result));

void Exec_boot_command();

#endif
