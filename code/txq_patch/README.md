# What?

- The `sctp_probe` module allows for capturing the changes to SCTP association
  state in response to incoming packets (`net/sctp/Kconfig`).

- It uses something called a jprobe to trap into itself and copy the
  arguments of a function we would like to analyze (read section 1.2 in
  `Documentation/kprobes.txt`).

- In the case of `sctp_probe`, the function being analyzed is
  `sctp_sf_eat_sack_6_2` (in `net/sctp/sm_statefuns.c`), which is called to
  process a received SACK. The jprobe handler is `jsctp_sf_eat_sack` (in
  `net/sctp/probe.c`). Notice that both `jsctp_sf_eat_sack` and
  `sctp_sf_eat_sack_6_2` have the same signature (arg list and return type).

- `output_txq.patch` modifies `net/sctp/probe.c` so the procfs entry
  `/proc/net/sctpprobe` outputs the size of the transmit queue each time the
  SACK processing function `sctp_sf_eat_sack_6_2` is invoked.

- The output from `/proc/net/sctpprobe` is more granular than the `buff.sh`
  script, though not periodic.


# Apply the patch

1. Clone Linus' git tree and switch to v4.2

        git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
        cd linux
        git checkout tags/v4.2

2. Compile and install. Reboot to the new kernel.

3. Copy `output_txq.patch` to the kernel source directory and then:

        git apply output_txq.patch

4. Compile the modified module.

        make M=net/sctp

5. Remove the already loaded modules, and insert the fresh ones (as root)

        rmmod -f sctp_probe sctp
        insmod net/sctp/sctp.ko
        insmod net/sctp/sctp_probe.ko

6. Do a file transfer and simply

        cat /proc/net/sctpprobe > stats
