# btech-project
Final year BTech project @ NITC 
##To-do List
[ ] Understand SCTP


[ ] Understand TCP Flow Control


[ ] Read send buffer advertisement RFC


[ ] Linux Kernel (Get the sources if you have not already)
##Bulletin Board

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

