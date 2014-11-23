#include "tcp/async/server.hh"

#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>

using namespace std;
using namespace tcp::async;
using namespace tcp::util;

server::server(address const& addr)
    : fd(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0))
{
    if (fd < 0) {
        throw runtime_error(strerror(errno));
    }

    auto sock_addr = addr.get_sockaddr();
    if (bind(fd, (sockaddr*) &sock_addr, sizeof(sock_addr)) < 0) {
        throw runtime_error(strerror(errno));
    }
}

void server::listen(io_service& service, on_accept_cb cb)
{
    ::listen(fd, 50); // TODO: Dirty const, don't call if already
    service.add_event(fd, new accept_event(fd, cb));
}

void server::close()
{
    ::close(fd);
}
