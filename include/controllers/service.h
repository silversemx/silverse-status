#ifndef _SILVERSE_MAIN_H_
#define _SILVERSE_MAIN_H_

struct _HttpResponse;

extern struct _HttpResponse *silverse_works;
extern struct _HttpResponse *current_version;

extern struct _HttpResponse *catch_all;

extern unsigned int silverse_service_init (void);

extern void silverse_service_end (void);

#endif