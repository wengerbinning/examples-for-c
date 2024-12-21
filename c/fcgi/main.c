#include <stdio.h>

#include <fcgiapp.h>
#include <fcgimisc.h>


static FCGX_Request fcgx_req;




int main (int argc, char *argv[]) {
    char *buf;
    char *caddr, *cport;
    int sock;
    FCGX_Request *req = &fcgx_req;

    FCGX_Init();
    if ((sock = FCGX_OpenSocket("127.0.0.1:2007", 20)) < 0) {
        printf("Failed to create sock\n");
        return -1;
    }

    FCGX_InitRequest(req, sock, 0);

    while (1) {
        FCGX_Accept_r(request);

        caddr = FCGX_GetParam("REMOTE_ADDR", req->envp);
        cport = FCGX_GetParam("REMOTE_PORT", req->envp);
        printf("Accept %s:%s", caddr, cport);

        buf = FCGX_GetParam("REQUEST_METHOD", req->envp);
        printf("request method: \"%s\"\n", buf);

        FCGX_FPrintF(request->out, "Content-Dispostion:attachment; filename=res.txt\r\n");
        FCGX_FPrintF(request->out, "\r\n");
        FCGX_FPrintF(request->out, "[%s]Response OK\n", buf);

        FCGX_Finish_r(req);
    }

    return 0;
}