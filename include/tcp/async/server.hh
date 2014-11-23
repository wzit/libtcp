#ifndef SERVER_HH
#define SERVER_HH

#include "tcp/util/address.hh"
#include "tcp/util/async_value.hh"
#include "tcp/util/job.hh"
#include "tcp/async/io_service.hh"
#include "tcp/async/io_event.hh"

#include <functional>

namespace tcp
{
    namespace async
    {
        struct server
        {
            server(util::address const&);
            void listen(io_service&, on_accept_cb);
            void close();

        private:
            int fd;
        };
    }
}

#endif