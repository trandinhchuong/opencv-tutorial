#include <sys/types.h>
#include <sys/stat.h>

#include "ak.h"

#include "app.h"
#include "app_dbg.h"
#include "sys_boot.h"

#include "task_list.h"
void task_init() {
	struct stat st;
	/* create app root path on DISK */
	if (stat(APP_ROOT_PATH_DISK, &st) == -1) {
		mkdir(APP_ROOT_PATH_DISK, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	/* create app root path on RAM */
	if (stat(APP_ROOT_PATH_RAM, &st) == -1) {
		mkdir(APP_ROOT_PATH_RAM, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
}
