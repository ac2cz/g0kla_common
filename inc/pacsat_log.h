/*
 * pacsat_log.h
 *
 *  Created on: Jun 2, 2024
 *      Author: g0kla
 *
 * Binary log format based on the historical pacsat Activity Logs
 */

#ifndef PACSAT_LOG_H_
#define PACSAT_LOG_H_

#include <stdint.h>
#include "common_config.h"

#define FILE_TMP ".tmp"


enum LOG_LEVEL {
	NO_LOG,
	ERR_LOG,
	WARN_LOG,
	INFO_LOG
};

enum LOG_NAME {
	LOG_NAME
	,WOD_NAME
	,ERR_NAME
	,NumberOfLogNames
};


/* If this is updated then LOG TEXT should be updated in pacsat_log.c */
enum LOG_EVENT {
	/* Initial event numbers are historical to match the PACSAT ALOG events */
     ALOG_STARTUP = 1		/* startup */
	,ALOG_ERR              /* 1 - Error is passed in serial_no */
	,ALOG_PROGRAM_EXIT       /* 1 - Exit code is in serial no */
	,ALOG_COMMAND            /* 2F - command sent from the ground with ground station call and params */
	,ALOG_DISKSPACE 		/* 1F  free disk space */
	,ALOG_FS_STARTUP
	,ALOG_FS_SHUTDOWN
	,ALOG_LOG_LEVEL  // 1 serial no is the level
	,ALOG_NUMBER_OF_EVENTS
};

/* Errors that we want to report in the log.  We should avoid repeating errors that could fill the log.
 * Those should be counted and downlinked in the error telemetry.  e.g. number of I2C failures.*/
enum LOG_ERRORS {
	ERR_UNKNOWN
	,ERR_REMOVING_FILE
	,ERR_COULD_NOT_STORE_WOD
	,ERR_SENDING_PKT
	,ERR_SETTING_TIME
	,ERR_MAX_TNC_RETRIES
	,ERR_PACSAT_FAILURE
	,ERR_DIREWOLF_FAILURE
	,ERR_PTT_FAILURE = 10
	,ERR_TNC_FAILURE
	,ERR_CHECKING_DISK_SPACE
	,ERR_NUMBER_OF_ERRORS
	,ERR_MAX_FILE_IO_ERRORS
	// FS ERRORS
	,ERR_FS_DIR_LOAD_FAILURE = 25
	,ERR_FS_TNC_FAILURE
};


/* Every entry has an ALOG Header*/
struct ALOG_1 {
	uint8_t event;		/* event code */
	uint8_t len;		/* length of entry */
	uint32_t tstamp;		/* time stamp */
	uint16_t serial_no;		/* serial number or other data for this event */
	uint8_t rxchan;		/* rx channel */
} __attribute__ ((__packed__));


struct ALOG_1F {
	uint8_t event;		/* event code */
	uint8_t len;		/* length of entry */
	uint32_t tstamp;		/* time stamp */
	uint16_t serial_no;		/* serial number */
	uint8_t rxchan;		/* rx channel */
	uint32_t var1;
	uint32_t var2;
	uint32_t var3;
	uint32_t var4;
	uint32_t var5;
	uint32_t var6;

} __attribute__ ((__packed__));

struct ALOG_2 {
	uint8_t event;		/* event code */
	uint8_t len;		/* length of entry */
	uint32_t tstamp;		/* time stamp */
	uint16_t serial_no;		/* serial number */
	uint8_t rxchan;		/* rx channel */
	uint8_t call[6];		/* callsign */
	uint8_t ssid;		/* ssid */
} __attribute__ ((__packed__));

struct ALOG_2F {
	uint8_t event;		/* event code */
	uint8_t len;		/* length of entry */
	uint32_t tstamp;		/* time stamp */
	uint16_t serial_no;		/* serial number */
	uint8_t rxchan;		/* rx channel */
	uint8_t call[6];		/* callsign */
	uint8_t ssid;		/* ssid */
	uint32_t var1;
	uint32_t var2;
	uint32_t var3;
	uint32_t var4;
	uint32_t var5;
	uint32_t var6;
} __attribute__ ((__packed__));

int log_init(char *prefix, char *folder, char *filename);
long get_file_size(const char *filename);
char * get_log_name_str(enum LOG_NAME name);
void log_set_level(enum LOG_LEVEL level);
void log_make_tmp_filename(char *filename, char *tmp_filename);
long log_err(char *filename, uint8_t error_code);
long log_alog1(int level, char *filename, enum LOG_EVENT event_code, uint16_t var);
long log_alog1f(int level, char *filename, enum LOG_EVENT event_code,
		uint32_t var1,uint32_t var2,uint32_t var3,uint32_t var4,uint32_t var5,uint32_t var6);
long log_alog2(int level, char *filename, enum LOG_EVENT event_code, char * callsign, uint8_t ssid, uint16_t var);
long log_alog2f(int level, char *filename, enum LOG_EVENT event_code, char * callsign, uint8_t ssid,
		uint32_t var1,uint32_t var2,uint32_t var3,uint32_t var4,uint32_t var5,uint32_t var6);
long log_append(char *filename, uint8_t * data, int len);
int log_add_to_directory(char *filename);

void log_debug_print(char * filename);

#endif /* PACSAT_LOG_H_ */
