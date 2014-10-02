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
		VSL(SLT_VCL_Error, 0, "getsockopt() == %i", retval);
		return;
	}
	VSL(SLT_VCL_Log, 0, "tcpi_rto: %i", tcpinfo.tcpi_rto);
	VSL(SLT_VCL_Log, 0, "tcpi_ato: %i", tcpinfo.tcpi_ato);
	VSL(SLT_VCL_Log, 0, "tcpi_snd_mss: %i", tcpinfo.tcpi_snd_mss);
	VSL(SLT_VCL_Log, 0, "tcpi_rcv_mss: %i", tcpinfo.tcpi_rcv_mss);

	VSL(SLT_VCL_Log, 0, "tcpi_rtt: %i", tcpinfo.tcpi_rtt);
	VSL(SLT_VCL_Log, 0, "tcpi_rttvar: %i", tcpinfo.tcpi_rttvar);
	VSL(SLT_VCL_Log, 0, "tcpi_advmss: %i", tcpinfo.tcpi_advmss);
	VSL(SLT_VCL_Log, 0, "tcpi_pmtu: %i", tcpinfo.tcpi_pmtu);

}
