#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#define TCP_CA_NAME_MAX 16

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf) {
	return (0);
}

/*
 * Based on the information found here:
 *   http://linuxgazette.net/136/pfeiffer.html
*/
void vmod_dump_info(const struct vrt_ctx *ctx) {
	int retval;

	struct tcp_info tcpinfo;
	socklen_t tcp_info_length = sizeof(struct tcp_info);
	retval = getsockopt(ctx->req->sp->fd, SOL_TCP, TCP_INFO,
	    (void*)&tcpinfo,&tcp_info_length);
	if (retval != 0) {
		VSLb(ctx->vsl, SLT_VCL_Error, "getsockopt() == %i", retval);
		return;
	}

	VSLb(ctx->vsl, SLT_VCL_Log,
	    "tcpi: snd_mss=%i rcv_mss=%i lost=%i retrans=%i",
	    tcpinfo.tcpi_snd_mss, tcpinfo.tcpi_rcv_mss,
	    tcpinfo.tcpi_lost, tcpinfo.tcpi_retrans);

	VSLb(ctx->vsl, SLT_VCL_Log,
	    "tcpi2: pmtu=%i rtt=%i rttvar=%i snd_cwnd=%i advmss=%i reordering=%i",
	    tcpinfo.tcpi_pmtu, tcpinfo.tcpi_rtt, tcpinfo.tcpi_rttvar,
	    tcpinfo.tcpi_snd_cwnd, tcpinfo.tcpi_advmss, tcpinfo.tcpi_reordering);

}

// http://sgros.blogspot.com/2012/12/controlling-which-congestion-control.html
// https://fasterdata.es.net/host-tuning/linux/

VCL_INT vmod_congestion_algorithm(const struct vrt_ctx *ctx, VCL_STRING new) {
	char strategy[TCP_CA_NAME_MAX];
	strncpy(strategy, new, (TCP_CA_NAME_MAX - 1));
	socklen_t l = strlen(strategy);
	if (setsockopt(ctx->req->sp->fd, IPPROTO_TCP, TCP_CONGESTION, strategy, l) < 0) {
		VSLb(ctx->vsl, SLT_VCL_Error,
		    "TCP_CONGESTION setsockopt() for \"%s\" failed.", strategy);
		return(-1);
	}

#ifndef NDEBUG
	l = TCP_CA_NAME_MAX;
	if (getsockopt(ctx->req->sp->fd, IPPROTO_TCP, TCP_CONGESTION,
	    strategy, &l) < 0) {
		VSLb(ctx->vsl, SLT_VCL_Error, "getsockopt() failed.");
	} else {
		VSLb(ctx->vsl, SLT_VCL_Log, "getsockopt() returned: %s", strategy);
	}
#endif
	return(0);
}

/*
 * net.ipv4.tcp_allowed_congestion_control = cubic reno
 * net.ipv4.tcp_available_congestion_control = cubic reno
 * net.ipv4.tcp_congestion_control = cubic
 *
 * */
