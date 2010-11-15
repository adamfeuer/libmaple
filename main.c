// lwip main.c - main loop

#include "libmaple.h"
#include "wirish.h"
#include "spi.h"
#include "gpio.h"
#include "wirish/time.h"

#include "port/witypes.h"
#include "port/g2100.h"
#include "port/g2100if.h"

#include "lwip/init.h"
#include "lwip/debug.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/sys.h"
#include "lwip/stats.h"

#include "lwip/ip_addr.h"
#include "lwip/ip.h"
#include "lwip/ip_frag.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "netif/etharp.h"

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

#define CLOCKTICKS_PER_MS 1

#define INT_PIN    2
#define CS_PIN     10

// Wireless configuration parameters ----------------------------------------
//unsigned char local_ip[] = {192,168,0,103};	// IP address of WiShield
//unsigned char gateway_ip[] = {192,168,0,1};	// router or gateway IP address
//unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const char ssid[] = {"Forest"};		// max 32 bytes
unsigned char security_type = 0;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const char security_passphrase[] = {"12345678"};	// max 64 characters
// WEP 128-bit keys
// sample HEX keys
const char wep_keys[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 1
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 2
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00	// Key 3
};


// setup the wireless mode
// infrastructure - connect to AP
unsigned char wireless_mode = WIRELESS_MODE_INFRA;

unsigned char ssid_len;
unsigned char security_passphrase_len;

// lwip
struct netif netif;

// (manual) host IP configuration
struct ip_addr ipaddr, netmask, gw;



//---------------------------------------------------------------------------

void setup() {
	 /* startup defaults (may be overridden by one or more opts) */
     zg_init();
	 pinMode(INT_PIN, INPUT_PULLUP);
	 attachInterrupt(INT_PIN, zg_isr, FALLING);

	 pinMode(CS_PIN, OUTPUT);
	 pinMode(CS_PIN, HIGH);

	 while(zg_get_conn_state() != 1) {
	     zg_drv_process();
	 }

	//	   lwip_init();
	//
	//	   netif_add(&netif, &ipaddr, &netmask, &gw, NULL, g2100if_init, g2100if_input);
	//	   netif_set_default(&netif);
	//	   netif_set_up(&netif);
//	 IP4_ADDR(&gw, 192,168,0,1);
//	 IP4_ADDR(&ipaddr, 192,168,0,2);
//	 IP4_ADDR(&netmask, 255,255,255,0);
}

// This is the webpage that is served up by the webserver
const char webpage[]= {"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789</body></html>"};


const char buf[] = "Hello world!";

void loop() {

	   unsigned long last_time, last_arp_time;
	   last_time = 0;
	   last_arp_time = 0;

	   //delay(1000);

	   /*
	   struct pbuf *p;

	   if(poll_driver(netif) == PACKET_READY) {
	     p = get_packet(netif);
	     ip_input(p, netif);
	   }

	   */

//	   if (millis() - last_arp_time >= ARP_TMR_INTERVAL * CLOCKTICKS_PER_MS) {
//	       etharp_tmr();
//	       last_arp_time = millis();
//	   }
//	   if(millis() - last_time >= TCP_TMR_INTERVAL * CLOCKTICKS_PER_MS) {
//	     tcp_tmr();
//	     last_time = millis();
//	   }

      //zg_drv_process();
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated object that need libmaple may fail.
__attribute__(( constructor )) void premain() {
   init();
}


int main(void) {
   setup();

   while (1) {
      loop();
   }
   return 0;
}

