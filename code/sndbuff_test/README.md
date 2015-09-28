# Info

- `lksctp-tools` includes a binary called `sctp_test`, which is especially made
  to test the kernel implementation. Just type `sctp_test` on your terminal to
  see all the options possible (packet size, no of streams, stream pattern,
  order pattern, etc.)

- [client.sh](./client.sh) and [server.sh](./server.sh) are small wrappers on
  top of `sctp_test` to measure the sendbuffer data using the patched
  `sctp_probe` module (from `/proc/net/sctpprobe`).

- The client sends data to the server using different sized packets for a
  particular duration of time (30 seconds).

- I have plotted the [graph](./graph/graph.pdf) for the 7 possible cases in
  `sctp_test`.

- Next step would be to vary the other parameters such as number of streams,
  order pattern, etc.

# Measure SCTP sendbuffer

1. Install [GNU parallel](https://www.gnu.org/software/parallel/).

2. Run the server.

        ./server.sh

3. Insert the patched `sctp_probe` module.

        sudo insmod sctp_probe.ko

3. Run the client, giving the IP address of the server as argument.

        sudo ./client.sh <SERVER_IP>

5. The recorded data is in the [data](./data) directory.
