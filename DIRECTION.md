# btech-project

Final year BTech project @ NITC

## SSN and TSN

TSNs for each fragment of a fragmented user message **MUST** be strictly
sequential.

SSN
- Each chunk of a message has the same SSN.
- is used to determine the order of delivery of messages to the upper layer.

## To-do List

- Read about AQM.

- Understand SCTP code (especially heartbeat sending mechnism)

- Configure OpenFlow switch in mininet with a controller.

- Study how application buffer management is handled.

- Understand SCTP and build a step by step flow diagram of the SCTP packet from
  user space to the wire thorough descriptions of each source file.

- Understand TCP Flow Control

- Read send buffer advertisement RFC


## Bulletin Board

- The latest iperf stable version doesn't support SCTP. So we'll have to
  install from [source](https://github.com/esnet/iperf).

- Read [./code/txq_patch/README.md](./code/txq_patch/README.md)

- Always do a `git pull` before doing a `git push`

- v4.2 has some [sctp fixes](https://lkml.org/lkml/2015/8/30/96), so we should
  use that.

I think we should all use this version -- as the source code won't change https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.1.7.tar.xz

No need to recompile the kernel or reboot everytime we change sctp. It's a module.

Generic Socket Structure : struct sock;

sock is type cast to make the sctp socket structure.

struct sctp_association has the output queue stored in it.(struct out_q)
sctp_sock has no info about queued chunks.
chunks are queued in out_q
Crashed the kernel/sctpsrvr could not respond to signals!
Because we forcefully removed the sctp module while it was used by sctpsrvr.
Modified protocol.c/sctp_outq_tail to print the type(chunk -> chunk_hdr -> type) and length of data chunks in buffer(out_qlen).
Future direction -> out_qlen...what does it do?


Sir suggested a new tool tc, which can be used to limit network bandwidth. Looking into it.

Killing the firewall systemctl stop firewalld.services , causes SCTP to run properly.

Think I found what happens on checking for send buffer space.
sctp_wait_for_sndbuf(asoc, &timeo, msg_len) --> put kernel thread to sleep --> the skb destructor calls the waking up function of there is enough space, skb destructor
is sctp_wfree() and in that sctp_wake_up_waiters().

Reference for kernel waiting: http://www.makelinux.net/ldd3/chp-6-sect-2

Find amount of backlogged data in the sendbuffer. We have found only the total send buffer.

Reference for kprobes: http://www.ibm.com/developerworks/library/l-kprobes/index.html

SCTP Socket Sharing by Multiple Associations
--------------------------------------------
Every association has an underlying struct sctp_association and it points to a common struct sock. wmem_alloc inside struct sock accounts for the buffer space used by all the associations of the socket. Whenever a chunk is created, the write buffer space is incremented in both the asoc->sndbuf_used and sk_wmem_queued. Therefore the sock accounts for the space used by all it's associations.

1) One to one sctp -- socket mapping
	Publish asoc->outqueue->out_qlen
2) Many to one sctp -- socket mapping
	Publish asoc->outqueue->out_qlen

Send Buffer Advertisement using the HeartBeat Chunk
---------------------------------------------------
We can stuff the backlogged sendbuffer data length into a heartbeat chunk, in variable length parameter format,
 without additional overhead to protocol performance(Refer RFC 4960 Section 3.2.1)

Will this frequency be enough? (Default heartbeat interval is 30s)!?
Caution: The sendbuffer backlog length is advertised only in those heartbeat chunks going to the primary address.

Possible problems!
Upper layer can disable the heartbeat for individual addresses

Can only be sent to one idle destination in 1HB interval, so not a broadcast to all the peer addresses.

Also if the receiver address is actively sending back SACK(s) then heartbeats are not sent to it.

Proposed Solution
-----------------

- Add a new chunk type with chunk type value between 128 to 190.

- As specified in the RFC, as the highest order 2 bits are 10 and the chunk
  is not recognized by a receiver, the chunk will be skipped without sending
  a _Unrecognized Chunk Type_ error chunk. This ensures that unmodified hosts
  are unaffected by the proposed changes.

- Chunk format

         0                   1                   2                   3
         0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |      Type     |  Chunk Flags  |      Chunk Length             |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |                    Sendbuffer Size                            |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

- Chunk size - 8 bytes (0.53% of a 1500 byte packet)

- Is the overhead considerable?

Directions Proposed by Anil sir
-------------------------------

- Propose a new chunk type and put the sendbuffer info into that.

- Encode the sendbuffer state as a flag in one of the existing chunks

- Build a test bed by hacking 2 ordinary linux routers and getting them to have SDN functionality

Proposed Topology

- Both the senders and receivers in one side

- Two senders, two receivers and two routers in a dumb-bell arrangement.

- Use tc and dummynet for emulating different network conditions.

## Second Semester
	Implementing the changes proposed and demonstrate it in a test environment
	
## TODO

- Make the necessary modification to the SCTP kernel module incorporating the new chunk type 

- Find a paper related to SCTP and better the results if possible
 
- Explore more on how we can make use of sendbuffer information 



