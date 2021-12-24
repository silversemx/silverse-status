#ifndef _SILVERSE_ROUTES_MAIN_H_
#define _SILVERSE_ROUTES_MAIN_H_

struct _HttpReceive;
struct _HttpRequest;

// GET /silverse
extern void silverse_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /silverse/version
extern void silverse_version_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET *
extern void silverse_catch_all_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

#endif