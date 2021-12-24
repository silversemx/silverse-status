#include <cerver/utils/log.h>

#include "version.h"

// print full test version information
void silverse_version_print_full (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nSilverse Status Service Version: %s", SILVERSE_VERSION_NAME
	);

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"Release Date & time: %s - %s", SILVERSE_VERSION_DATE, SILVERSE_VERSION_TIME
	);

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"Author: %s\n", SILVERSE_VERSION_AUTHOR
	);

}

// print the version id
void silverse_version_print_version_id (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nSilverse Status Service Version ID: %s\n", SILVERSE_VERSION
	);

}

// print the version name
void silverse_version_print_version_name (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nSilverse Status Service Version: %s\n", SILVERSE_VERSION_NAME
	);

}
