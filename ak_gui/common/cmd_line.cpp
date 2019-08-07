/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   13/08/2016
 ******************************************************************************
**/

#include <string.h>
#include "cmd_line.h"

uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command){
	uint8_t     cmd[MAX_CMD_SIZE];
	uint8_t*    p_command = command;
	uint8_t     cmd_index = 0;
	uint8_t     indexCheck = 0;

	if (cmd_table == (cmd_line_t*)0) {
		return CMD_TBL_NOT_FOUND;
	}

	/* get cmd */
	while (*p_command) {
		if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
			cmd[cmd_index] = 0;
			break;
		}
		else {
			cmd[cmd_index++] = *(p_command++);
			if (cmd_index >= MAX_CMD_SIZE) {
				return CMD_TOO_LONG;
			}
		}
	}

	/* find respective command in command table */
	while(cmd_table[indexCheck].cmd){

		if (strcmp((const char*)cmd_table[indexCheck].cmd, (const char*)cmd) == 0) {

			/* perform respective function */
			cmd_table[indexCheck].func(command);

			/* return success */
			return CMD_SUCCESS;
		}

		indexCheck++;
	}

	return CMD_NOT_FOUND;  /* command not found */
}

