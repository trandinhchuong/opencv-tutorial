#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

#include "app.h"
#include "app_dbg.h"
#include "app_config.h"

string config_folder;
string config_file_path;

app_config::app_config() {

}

void app_config::initializer(char * file_name) {
	struct stat st;

	string config_folder = static_cast<string>(APP_ROOT_PATH_DISK) + static_cast<string>("/config");

	/* create app root path */
	if (stat(config_folder.data(), &st) == -1) {
		mkdir(config_folder.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	string config_file_path = config_folder + static_cast<string>((const char*)file_name);

	strcpy(m_config_path, config_file_path.data());
}

void app_config::set_config_path_file(char* path) {
	strcpy(m_config_path, (const char*)path);
}

void app_config::get_config_path_file(char* path) {
	strcpy(path, (const char*)m_config_path);
}

int app_config::parser_config_file(void* cfg) {
	(void)cfg;
	return 0;
}

int app_config::write_config_data(void* cfg) {
	(void)cfg;
	return 0;
}
