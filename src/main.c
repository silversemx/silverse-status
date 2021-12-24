#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <signal.h>

#include <cerver/cerver.h>
#include <cerver/version.h>

#include <cerver/http/http.h>
#include <cerver/http/route.h>

#include <cerver/utils/log.h>
#include <cerver/utils/utils.h>

#include "silverse.h"
#include "version.h"

#include "routes/service.h"

static Cerver *test_api = NULL;

void end (int dummy) {
	
	if (test_api) {
		cerver_stats_print (test_api, false, false);
		cerver_log_msg ("\nHTTP Cerver stats:\n");
		http_cerver_all_stats_print ((HttpCerver *) test_api->cerver_data);
		cerver_log_line_break ();
		cerver_teardown (test_api);
	}

	(void) silverse_end ();

	cerver_end ();

	exit (0);

}

static void silverse_set_silverse_routes (HttpCerver *http_cerver) {

	/* register top level route */
	// GET /silverse
	HttpRoute *main_route = http_route_create (REQUEST_METHOD_GET, "silverse", silverse_handler);
	http_cerver_route_register (http_cerver, main_route);

	/* register silverse children routes */
	// GET silverse/version
	HttpRoute *version_route = http_route_create (REQUEST_METHOD_GET, "version", silverse_version_handler);
	http_route_child_add (main_route, version_route);

}

static void start (void) {

	test_api = cerver_create (
		CERVER_TYPE_WEB,
		"test-api",
		PORT,
		PROTOCOL_TCP,
		false,
		CERVER_CONNECTION_QUEUE
	);

	if (test_api) {
		/*** cerver configuration ***/
		cerver_set_receive_buffer_size (test_api, CERVER_RECEIVE_BUFFER_SIZE);
		cerver_set_thpool_n_threads (test_api, CERVER_TH_THREADS);
		cerver_set_handler_type (test_api, CERVER_HANDLER_TYPE_THREADS);

		/*** web cerver configuration ***/
		HttpCerver *http_cerver = (HttpCerver *) test_api->cerver_data;

		http_cerver_set_uploads_path (http_cerver, "/var/uploads");
		http_cerver_set_uploads_delete_when_done (http_cerver, true);

		silverse_set_silverse_routes (http_cerver);

		// add a catch all route
		http_cerver_set_catch_all_route (http_cerver, silverse_catch_all_handler);

		// admin configuration
		http_cerver_enable_admin_routes (http_cerver, true);
		http_cerver_register_admin_file_system (http_cerver, "/var/uploads");
		http_cerver_register_admin_file_system (http_cerver, "/home/silverse/uploads");

		if (cerver_start (test_api)) {
			cerver_log_error (
				"Failed to start %s!",
				test_api->info->name
			);

			cerver_delete (test_api);
		}
	}

	else {
		cerver_log_error ("Failed to create cerver!");

		cerver_delete (test_api);
	}

}

int main (int argc, char const **argv) {

	srand (time (NULL));

	// register to the quit signal
	(void) signal (SIGINT, end);
	(void) signal (SIGTERM, end);

	// to prevent SIGPIPE when writting to socket
	(void) signal (SIGPIPE, SIG_IGN);

	cerver_init ();

	cerver_version_print_full ();

	silverse_version_print_full ();

	if (!silverse_init ()) {
		start ();
	}

	else {
		cerver_log_error ("Failed to init silverse!");
	}

	(void) silverse_end ();

	cerver_end ();

	return 0;

}
