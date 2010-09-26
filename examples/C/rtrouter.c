//
//  Cross-connected XREP sockets addressing each other
//
#include "zhelpers.h"

int main () {
    void *context = zmq_init (1);

    void *worker = zmq_socket (context, ZMQ_XREP);
    zmq_setsockopt (worker, ZMQ_IDENTITY, "WORKER", 6);
    zmq_bind (worker, "ipc://rtrouter.ipc");

    void *server = zmq_socket (context, ZMQ_XREP);
    zmq_setsockopt (server, ZMQ_IDENTITY, "CLIENT", 6);
    zmq_connect (server, "ipc://rtrouter.ipc");

    sleep (1);
    s_sendmore (server, "WORKER");
    s_sendmore (server, "");
    s_send     (server, "send to worker");
    s_dump     (worker);

    s_sendmore (worker, "CLIENT");
    s_sendmore (worker, "");
    s_send     (worker, "send to front-end");
    s_dump     (server);

    zmq_term (context);
    return 0;
}
