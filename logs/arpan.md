2015-08-14
----------

Submitted the project title as __Modifying the Linux kernel network stack for security__.


2015-08-15
----------

Started reading RFC 793 - Transmission Control Protocol.


2015-08-18
----------

- Completed reading RFC 3286 - An Introduction to the Stream Control Transmission Protocol (SCTP).
- Wrote multi-streaming SCTP client and server in Linux using lksctp-tools.


2015-08-21
----------

- Read chapter 1 of _Understanding Linux Network Internals_.
- Tools to help browse kernel code:
  - cscope
  - ctags

2015-08-24
----------

- Started chapter 2 of _Understanding Linux Network Internals_.
- Studied the code for `struct sk_buff`.
- Interesting members:
  - pkt_type: types defined in `include/uapi/linux/if_packet.h` 

        /* Packet types */

        #define PACKET_HOST	    	0		/* To us		*/
        #define PACKET_BROADCAST	1		/* To all		*/
        #define PACKET_MULTICAST	2		/* To group		*/
        #define PACKET_OTHERHOST	3		/* To someone else 	*/
        #define PACKET_OUTGOING 	4		/* Outgoing of any type */
        #define PACKET_LOOPBACK 	5		/* MC/BRD frame looped back */
        #define PACKET_USER	    	6		/* To user space	*/
        #define PACKET_KERNEL		7		/* To kernel space	*/

        /* Unused, PACKET_FASTROUTE and PACKET_LOOPBACK are invisible to user space */
        #define PACKET_FASTROUTE	6		/* Fastrouted frame	*/

    I guess Wireshark's promiscuous mode somehow changes the kernel's policy to
    discard the PACKET_OTHERHOST packets and capture them.

2015-09-30
----------

- Talked to Anil sir about future action plan.
- Installed iperf v3.1b3
