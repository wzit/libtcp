#ifndef CLIENT_HH
#define CLIENT_HH

#include "tcp/util/address.hh"
#include "tcp/util/async_value.hh"
#include "tcp/util/nothing.hh"
#include "tcp/async/io_service.hh"
#include "tcp/async/io_event.hh"

#include <functional>

namespace tcp
{
    namespace async
    {
        struct client
        {
            client();
            ~client();

            client(client const&) = delete;
            client(client&&);

            void operator=(client&&);

            void connect(io_service&, util::address const&, on_connect_cb);
            void read(io_service&, size_t count, on_read_cb);
            void write(io_service&, util::buffer, on_write_cb);

            int get_fd() const { return fd; }

        private:
            int fd;
            client(int fd)
                    : fd(fd)
            {}

            friend struct accept_event;
        };
    }
}

#endif
