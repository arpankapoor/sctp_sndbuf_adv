# What?

- Patch to send a sendbuffer advertisement chunk (chunk id `150`) every
  `sndbuf_adv_interval`.

- Modify the interval value by writing to the sysctl file
  `/proc/sys/net/sctp/sndbuf_adv_interval` (default is 5000 ms).

- Applies to v4.5-rc6, v4.4.3, v4.3.6, v4.1.8, v3.18.27 and v3.14.62, but not
  before that.

# Apply the patch

1. Cd into your kernel source directory and

        git apply /path/to/sctp_sndbuf_adv.patch

2. Compile and install. Reboot to the compiled kernel.

3. Transfer a file and capture the sendbuffer advert chunks in Wireshark
   using the filter `sctp.chunk_type == 130`.

4. Ponder over how to use this information...
