#include <cerver/http/http.h>
#include <cerver/http/request.h>
#include <cerver/http/response.h>

#include "controllers/service.h"

// GET /silverse
void silverse_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (silverse_works, http_receive);

}

// GET /silverse/version
void silverse_version_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (current_version, http_receive);

}

// GET *
void silverse_catch_all_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	http_response_send (catch_all, http_receive);

}
