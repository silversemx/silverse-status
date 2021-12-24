#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/http/response.h>

#include <cerver/utils/utils.h>

#include "version.h"

#define VERSION_BUFFER_SIZE		64

HttpResponse *silverse_works = NULL;
HttpResponse *current_version = NULL;

HttpResponse *catch_all = NULL;

unsigned int silverse_service_init (void) {

	unsigned int retval = 1;

	silverse_works = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Silverse status works!"
	);

	char version[VERSION_BUFFER_SIZE] = { 0 };
	(void) snprintf (
		version, VERSION_BUFFER_SIZE - 1,
		"%s - %s",
		SILVERSE_VERSION_NAME, SILVERSE_VERSION_DATE
	);

	current_version = http_response_json_key_value (
		HTTP_STATUS_OK, "version", version
	);

	catch_all = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Silverse status service!"
	);

	if (
		silverse_works && current_version
		&& catch_all
	) retval = 0;

	return retval;

}

void silverse_service_end (void) {

	http_response_delete (silverse_works);
	http_response_delete (current_version);

	http_response_delete (catch_all);

}
