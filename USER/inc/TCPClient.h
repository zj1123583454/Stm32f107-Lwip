#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "stm32f10x.h"
#include "memp.h"
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "netconf.h"
struct tcp_pcb *tcp_echoclient_connect(void);

err_t tcp_echoclient_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

enum echoclient_states
{
  ES_NOT_CONNECTED = 0,
  ES_CONNECTED,
  ES_RECEIVED,
  ES_CLOSING,
};
enum Lunry_Tcp_States
{
	TCP_Closed=0,
	TCP_Connected,
};
struct echoclient
{
  enum echoclient_states state; /* connection status */
  struct tcp_pcb *pcb;          /* pointer on the current tcp_pcb */
  struct pbuf *p_tx;            /* pointer on pbuf to be transmitted */
};
void tcp_echoclient_connection_close(struct tcp_pcb *tpcb, struct echoclient * es);
