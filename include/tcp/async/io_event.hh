#ifndef IO_EVENT_HH
#define IO_EVENT_HH

#include "tcp/util/buffer.hh"
#include "tcp/util/address.hh"

#include <cstdint>
#include <functional>

namespace tcp
{
    namespace async
    {
        typedef std::function <void(int fd)> on_accept_cb;
        typedef std::function <void()> on_connect_cb;
        typedef std::function <void(util::buffer)> on_read_cb;
        typedef std::function <void()> on_write_cb;

        struct io_event
        {
            virtual bool handle() = 0;

            virtual uint32_t events_flag() = 0;

            virtual ~io_event() = default;
        };

        struct read_event : io_event
        {
            read_event(int fd,
                    size_t,
                    on_read_cb);

            bool handle() override;

            uint32_t events_flag() override;

        private:
            int fd;
            util::buffer buf;
            on_read_cb on_read;
        };

        struct write_event : io_event
        {
            write_event(int fd,
                    util::buffer b,
                    on_write_cb);

            bool handle() override;

            uint32_t events_flag() override;

        private:
            int fd;
            util::buffer buf;
            on_write_cb on_write;
        };

        struct accept_event : io_event
        {
            accept_event(int fd,
                    on_accept_cb);

            bool handle() override;

            uint32_t events_flag() override;

        private:
            int fd;
            on_accept_cb on_accept;
        };

        struct connect_event : io_event
        {
            connect_event(int fd,
                    util::address addr,
                    on_connect_cb);

            bool handle() override;

            uint32_t events_flag() override;

        private:
            int fd;
            util::address addr;
            on_connect_cb on_connect;
        };
    }
}

#endif
