This is a running log of changes applied to vmod-tcp.

vmod-tcp v0.9 (unreleased)
--------------------------

* Support for socket pacing on Linux added via tcp.set_socket_pace().


vmod-tcp v0.8 (2015-11-30)
--------------------------

First real release of vmod-tcp. This release works with Varnish Cache 4.0.

This release sums up the functionality previously only available in git,
meaning:

* Adjust congestion control algorithm for ongoing TCP connection.
* Extract estimated connection round trip time (RTT.)
* (Partial) extract TCP_INFO fields into varnishlog. (post-processing needed)

