# btech-project

Final year BTech project @ NITC

## To-do List

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
