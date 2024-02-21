#include <stdio.h>

#include <fcgiapp.h>
#include <fcgimisc.h>

static FCGX_Request fcgx_req;

int main (int argc, char *argv[]) {
    char *buf;
    char *cli_addr, *cli_port;
    static FCGX_Request *request = &fcgx_req;
    int sock;

    FCGX_Init();
    sock = FCGX_OpenSocket("127.0.0.1:2007", 20);
    if (sock < 0) {
        printf("Failed to create sock\n");
        return -1;
    }

    FCGX_InitRequest(request, sock, 0);

    while (1) {
        FCGX_Accept_r(request);

        cli_addr = FCGX_GetParam("REMOTE_ADDR", request->envp);
        cli_port = FCGX_GetParam("REMOTE_PORT", request->envp);
        printf("Accept %s:%s", cli_addr, cli_port);

        // buf = FCGX_GetParam("REQUEST_METHOD", request->envp);
        // printf("request method: \"%s\"\n", buf);

        FCGX_FPrintF(request->out, "Content-Dispostion:attachment; filename=res.txt\r\n");
        FCGX_FPrintF(request->out, "\r\n");
        FCGX_FPrintF(request->out, "[%s]Response OK\n", buf);

        FCGX_Finish_r(&fcgx_req);
    }

    return 0;
}