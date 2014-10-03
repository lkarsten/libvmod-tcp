========
vmod_tcp
========

------------------
Varnish TCP module
------------------

:Author: Lasse Karstensen
:Date: 2014-10-03
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import tcp;

DESCRIPTION
===========

The TCP vmod is a set of functions that accesses and changes attributes
on the (client) TCP connection.

It allows you to access TCP_INFO data, and also change the congestion control
algorithm used.

The VMOD is Linux-specific and requires a recent kernel to be useful. (>=3.13)

The interface/functions provided by this vmod are not stable, expect changes.

FUNCTIONS
=========

dump_info
---------

Prototype
        ::

                dump_info()
Return value
	VOID
Description
	Write the contents of the TCP_INFO data structure into varnishlog.
Example
        ::

                tcp.dump_info();

congestion_algorithm
--------------------

Prototype
        ::

                congestion_algorithm(STRING S)
Return value
	INT
Description
	Set the client socket congestion control algorithm to S. Returns 0 on success, and -1 on error.
Example
        ::

                set req.http.x-tcp = tcp.congestion_algorithm("cubic");


INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure

Make targets:

* make - builds the vmod
* make install - installs vmod
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::
        
        import tcp;

        sub vcl_recv {
                tcp.dump_info();
                set req.http.x-tcp = tcp.congestion_algorithm("reno");
        }

Example varnishlog output from dump_info()::
        
        -   VCL_Log        tcpi: snd_mss=1448 rcv_mss=536 lost=0 retrans=0
        -   VCL_Log        tcpi2: pmtu=1500 rtt=152000 rttvar=76000 snd_cwnd=10 advmss=1448 reordering=3
        -   VCL_Log        getsockopt() returned: cubic


COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-tcp project. See LICENSE for details.

* Copyright (c) 2011-2014 Varnish Software
