#include <stdio.h>

#include <fcgiapp.h>
#include <fcgi_stdio.h>
#include <fcgimisc.h>

static FCGX_Request fcgx_req;

int main (int argc, char *argv[]) {
    char *buf;
    int sock;

    FCGX_Init();
    sock = FCGX_OpenSocket("127.0.0.1:2007", 20);
    if (sock < 0) {
        printf("Failed to create sock\n");
        return -1;
    }

    FCGX_InitRequest(&fcgx_req, sock, 0);

    while (1) {
        printf("server running ...\n");

        FCGX_Accept_r(&fcgx_req);

        buf = get_param("REMOTE_ADDR");
        printf("remote addr: \"%s\"\n", buf);

        buf = get_param("REQUEST_METHOD");
        printf("request method: \"%s\"\n", buf);

        pfprint("Content-Dispostion:attachment; filename=res.txt\r\n");
        pfprint("\r\n");
        pfprint("reponse OK\n");

        FCGX_Finish_r(&fcgx_req);
    }

    return 0;
}