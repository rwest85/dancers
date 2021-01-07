# Asynchronous design notes

## Goal

All operations are assumed asynchronous.

We assume that the driver program is running an epoll() or similar event loop (libev, libuv...) and we don't want to depend on the details.

*Therefore*, we will abstract out a set of routines that we ask the driver to call.

dancers_init
dancers_start

dancers_io
dancers_timer

dancers_stop
dancers_destroy

## Step 1

First step: assume libuv

### Needs

- timer, to trigger timeouts
- udp listener, to receive responses (v4/v6)
- send udp packets (v4/v6)
- open tcp connections and maintain them
- open tls connections and maintain them

