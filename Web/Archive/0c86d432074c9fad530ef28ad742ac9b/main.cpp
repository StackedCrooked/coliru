#include <stdlib.h>
#include <stdio.h>
#include <uv.h>

struct server_data {
    uv_loop_t *loop;
};

uv_buf_t on_alloc(uv_handle_t *handle, size_t suggested_size) {
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void on_read(uv_stream_t *client, ssize_t read, uv_buf_t buf) {
    if (read == -1) {
        uv_close((uv_handle_t *)client, (uv_close_cb)&free);
        return;
    }

    /* TODO: Read data and do something with it. */
}

void on_connect(uv_stream_t *server, int status) {
    int err;
    uv_tcp_t *client;

    if (status == -1) {
        /* TODO: Log error. */
        return;
    }

    struct server_data *server_data = server->data;

    client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server_data->loop, client);
    err = uv_accept(server, (uv_stream_t *)client);
    if (err) {
        uv_close((uv_handle_t *)client, (uv_close_cb)&free);
        return;
    }
    uv_read_start((uv_stream_t *)client, &on_alloc, &on_read);
}

int main() {
    uv_tcp_t server;
    struct server_data server_data;
    uv_loop_t *loop = uv_default_loop();

    server_data.loop = loop;

    uv_tcp_init(loop, &server);
    server.data = &server_data;
    uv_tcp_bind(&server, uv_ip4_addr("0.0.0.0", 1337));
    uv_listen((uv_stream_t *)&server, 128, &on_connect);

    uv_run(loop);
}
