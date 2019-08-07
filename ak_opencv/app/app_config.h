#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <stdint.h>
#include <string>

#include "app.h"
#include "app_data.h"

using namespace std;

class app_config {
public:
	app_config();
	void initializer(char*);
	void set_config_path_file(char*);
	void get_config_path_file(char*);
	int parser_config_file(void*);
	int write_config_data(void*);

private:
	char m_config_path[256];
};

#endif //__APP_CONFIG_H__
