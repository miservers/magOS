/* 
**  mod_my_check.c -- Apache sample my_check module
**  [Autogenerated via ``apxs -n my_check -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_my_check.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /my_check in as follows:
**
**    #   apache2.conf
**    LoadModule my_check_module modules/mod_my_check.so
**    <Location /my_check>
**    SetHandler my_check
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /my_check and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/my_check 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_my_check.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

/* Static Config*/
typedef struct {
    int         enabled;      /* Enable or disable our module */
    const char *path;         /* Some path to...something */
    int         typeOfAction; /* 1 means action A, 2 means action B and so on */
} my_check_config;

static my_check_config config;


/* The sample content handler */
static int my_check_handler(request_rec *r)
{
    if (strcmp(r->handler, "my_check")) {
        return DECLINED;
    }
    r->content_type = "text/plain";      

   ap_rprintf(r, "Enabled: %u\n", config.enabled);
   ap_rprintf(r, "Path: %s\n", config.path);
   ap_rprintf(r, "TypeOfAction: %x\n", config.typeOfAction);
 
   if (!r->header_only)
        ap_rputs("My CHECK : Hello, world!\n", r);
   return OK;
}

static void my_check_register_hooks(apr_pool_t *p)
{
	config.enabled = 1;
    config.path = "/fo/bar";
    config.typeOfAction = 0x00;
    
    ap_hook_handler(my_check_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA my_check_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    my_check_register_hooks  /* register hooks                      */
};

