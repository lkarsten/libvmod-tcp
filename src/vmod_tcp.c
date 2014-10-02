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
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_rto: %i", tcpinfo.tcpi_rto);
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_ato: %i", tcpinfo.tcpi_ato);

	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_snd_mss: %i", tcpinfo.tcpi_snd_mss);
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_rcv_mss: %i", tcpinfo.tcpi_rcv_mss);

	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_rtt: %i", tcpinfo.tcpi_rtt);
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_rttvar: %i", tcpinfo.tcpi_rttvar);
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_advmss: %i", tcpinfo.tcpi_advmss);
	VSLb(ctx->vsl, SLT_VCL_Log, "tcpi_pmtu: %i", tcpinfo.tcpi_pmtu);

}
