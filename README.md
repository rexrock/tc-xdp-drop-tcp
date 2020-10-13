# tc-xdp-drop-tcp
Test ebpf by tc and xdp

## 1. Compile the ebpf code
```bash
clang -I ./include/ -O2 -target bpf -c tc-xdp-drop-tcp.c -o tc-xdp-drop-tcp.o
```

## 2. XDP 
Attach XDP program
```bash
ip link set dev <dev> xdp obj tc-xdp-drop-tcp.o sec xdp
```
By default, if the XDP program has attached to the network interface, an error will be reported when it is reloaded. This is designed to prevent the program from being inadvertently overwritten.To force a currently running XDP program, you must specify the -force parameter
```bash
ip --force link set dev <dev> xdp obj tc-xdp-drop-tcp.o sec xdp
```
Remove the XDP program
```bash
ip link set dev <dev> xdp off
```

## 3. TC
Add clsact qdisc
```bash
tc qdisc add dev <dev> clsact
```
Attach ebpf program to tc
```bash
tc filter add dev <dev> <ingress/egress> bpf da obj tc-xdp-drop-tcp.o sec tc verbose
```
Remove the ebpf program from a network device
```bash
tc filter del dev <dev> handle 0x1 prio 49152 <ingress/egress> bpf
```
