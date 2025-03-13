#include <Arduino.h>
#include "macros.h"
#include "simple_tft.h"
#include "boot.h"

static cmd_t *cmd_tbl_list, *cmd_tbl;
static int idx;
static int config;

void Init_boot_command (int _config)
{
  // init the command table
  cmd_tbl_list = NULL;
  idx = 0;
  config = _config;
}

void Add_boot_command (const char * name ,void (*func) (int *_result))
{
    // alloc memory for command struct
    cmd_tbl = (cmd_t *)malloc(sizeof(cmd_t));

    // alloc memory for command name
    char *cmd_name = (char *)malloc(strlen(name)+1);

    // copy command name
    strcpy(cmd_name, name);

    // terminate the command name
    cmd_name[strlen(name)] = '\0';

    // fill out structure
    cmd_tbl->cmd = cmd_name;
    cmd_tbl->func = func;
    cmd_tbl->next = cmd_tbl_list;
    cmd_tbl_list = cmd_tbl;
    cmd_tbl->index = idx;
    idx++;
}
void Exec_boot_command()
{
    cmd_t *cmd_entry;
    int _result;
    uint8_t argc, i = 0;
    char *argv[30];

    for(int i=0;i<idx;i++)
    {
        for (cmd_entry = cmd_tbl; cmd_entry != NULL; cmd_entry = cmd_entry->next)
        {
            if (cmd_entry->index == i)
            {
                char _msg[32];
                sprintf(_msg,"%s %d/%d",cmd_entry->cmd,cmd_entry->index+1,idx);
                bootln(_msg);
                cmd_entry->func (&_result);
                if (config)
                {
                    display_progress(cmd_entry->index+1, idx);
                }
                else
                {
                    display_boot_pass_fail(cmd_entry->cmd, _result);
                }
                
            }
        }
    }
}