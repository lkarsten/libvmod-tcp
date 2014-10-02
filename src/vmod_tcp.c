#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

void vmod_dump_info(const struct vrt_ctx *ctx) {
	char * foo;
	int retval;

	struct tcp_info tcpinfo;
	int tcp_info_length = sizeof(struct tcp_info);
	retval = getsockopt(ctx->req->sp->fd, SOL_TCP, TCP_INFO, (void*)&tcpinfo, &tcp_info_length);
	if (retval != 0) {
		VSLb(ctx->vsl, SLT_VCL_Error, "getsockopt() == %i", retval);
		return;
	}
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi rto=%i ato=%i snd_mss=%i rcv_mss=%i",
	    tcpinfo.tcpi_rto, tcpinfo.tcpi_ato, tcpinfo.tcpi_snd_mss,
	    tcpinfo.tcpi_rcv_mss);

	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi rtt=%i rttvar=%i advmss=%i pmtu=%i",
	    tcpinfo.tcpi_rtt, tcpinfo.tcpi_rttvar, tcpinfo.tcpi_advmss,
	    tcpinfo.tcpi_pmtu);
}
