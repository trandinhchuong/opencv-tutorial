#ifndef __APP_DATA_H__
#define __APP_DATA_H__
#include <stdint.h>
#include <string>

#include "sys_boot.h"

using namespace std;

/******************************************************************************
* interface type
*******************************************************************************/
/** RF24 interface for modules
*/
#define IF_TYPE_RF24_MIN					(0)
#define IF_TYPE_RF24_GW						(0)
#define IF_TYPE_RF24_AC						(1)
#define IF_TYPE_RF24_MAX					(99)

/******************************************************************************
* Data type of RF24Network
*******************************************************************************/
#define RF24_DATA_COMMON_MSG_TYPE			(1)
#define RF24_DATA_PURE_MSG_TYPE				(2)
#define RF24_DATA_REMOTE_CMD_TYPE			(3)

/** APP interface, communication via socket interface
 *
 */
#define IF_TYPE_APP_START					(100)
#define IF_TYPE_APP_GMNG					(100)
#define IF_TYPE_APP_GW						(101)
#define IF_TYPE_APP_GI						(102)

/** CPU SERIAL interface, communication via uart serial interface
 *
 */
#define IF_TYPE_UART_GW_MIN					(120)
#define IF_TYPE_UART_GW						(120)
#define IF_TYPE_UART_AC						(121)
#define IF_TYPE_UART_GW_MAX					(140)

#define ENABLE_LAUNCHER						(0x01)
#define DISABLE_LAUNCHER					(0x00)

typedef struct {
	uint32_t id;
	char* socket_path;
	char* location_path;
	uint8_t enable_launcher;
	__pid_t pid;
} if_app_t;

extern if_app_t if_app_list[];
extern uint32_t if_app_list_size;

/******************************************************************************
* Common define
*******************************************************************************/
enum app_data_error_code_e {
	APP_ERROR_CODE_TIMEOUT	= 0x01,
	APP_ERROR_CODE_BUSY		= 0x02,
	APP_ERROR_CODE_STATE	= 0x03,
};

/******************************************************************************
* Commom data structure for transceiver data
*******************************************************************************/
#define CONFIGURE_PARAMETER_BUFFER_SIZE		256
#define RF24_ENCRYPT_DECRYPT_KEY_SIZE		16
extern uint8_t rf24_encrypt_decrypt_key[];

#define FIRMWARE_PSK				0x1A2B3C4D
#define FIRMWARE_LOK				0x1234ABCD

#endif //__APP_DATA_H__
