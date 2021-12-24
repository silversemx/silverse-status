#ifndef _SILVERSE_VERSION_H_
#define _SILVERSE_VERSION_H_

#define SILVERSE_VERSION			"0.1"
#define SILVERSE_VERSION_NAME		"Version 0.1"
#define SILVERSE_VERSION_DATE		"17/07/2021"
#define SILVERSE_VERSION_TIME		"17:03 CST"
#define SILVERSE_VERSION_AUTHOR		"Erick Salas"

// print full silverse version information
extern void silverse_version_print_full (void);

// print the version id
extern void silverse_version_print_version_id (void);

// print the version name
extern void silverse_version_print_version_name (void);

#endif