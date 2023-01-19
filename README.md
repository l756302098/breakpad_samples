# breakpad_samples
Example based on breakpad  

## install breakpad  

1.git clone https://github.com/google/breakpad.git  
2.下载Breakpad依赖的三方库 LSS：git clone https://github.com/adelshokhy112/linux-syscall-support.git ，将 LSS 中的linux_syscall_support.h文件放至breakpad/src/third_party/lss/ 目录下。  
3.将 LSS 中的 linux_syscall_support.h 文件放至 breakpad/src/third_party/lss/ 目录下。  
4.编译 Breakpad.
``` shell
cd breakpad
./configure
make
sudo make install
```
5.安装完成的库文件在 /usr/local/lib 下 libbreakpad.a/libbreakpad_client.a     
可执行程序在 /usr/local/bin 下，包括dump_syms/microdump_stackwalk



## How to use

1. complie   
``` shell
cd breakpad
mkdir build && cd build  
make
```
2.Generate symbol file  

``` shell
cd build
dump_syms ./breakpad_samples > breakpad_samples.sym
head -n1 breakpad_samples.sym  ==> MODULE Linux x86_64 D1D84253C4A3A1011EAD01F3B943DE9D0 breakpad_samples  
mkdir -p ./symbols/breakpad_samples/D1D84253C4A3A1011EAD01F3B943DE9D0  
mv breakpad_samples.sym symbols/breakpad_samples/D1D84253C4A3A1011EAD01F3B943DE9D0/  
```
3.run and collect dmp file
```shell
cd build
./breakpad_samples ==>
Dump path:/tmp/b8cdbe95-e250-4a97-31eb6b88-fffca9fc.dmp
Segmentation fault (core dumped) 
```
4.Generate stack trace based on minnidump and symbol  

```shell
cd build
minidump_stackwalk /tmp/b8cdbe95-e250-4a97-31eb6b88-fffca9fc.dmp symbols > error.log
```
```error
Operating system: Linux
                  0.0.0 Linux 5.4.0-138-generic #155~18.04.1-Ubuntu SMP Fri Jan 13 14:27:01 UTC 2023 x86_64
CPU: amd64
     family 6 model 141 stepping 1
     1 CPU

GPU: UNKNOWN

Crash reason:  SIGSEGV /SEGV_MAPERR
Crash address: 0x0
Process uptime: not available

Thread 0 (crashed)
 0  breakpad_samples!main [main.cpp : 14 + 0x0]
    rax = 0xffffffffffffffff   rdx = 0x00007f077b5b2700
    rcx = 0x0000000000000000   rbx = 0x00007fff35dec520
    rsi = 0x0000000000000000   rdi = 0x000056097c82a7a0
    rbp = 0x00007fff35dec6b0   rsp = 0x00007fff35dec520
     r8 = 0x0000000000000000    r9 = 0x0000000000000000
    r10 = 0x000056097e6a4010   r11 = 0x0000000000000000
    r12 = 0x000056097c612300   r13 = 0x00007fff35dec790
    r14 = 0x0000000000000000   r15 = 0x0000000000000000
    rip = 0x000056097c6122a8
    Found by: given as instruction pointer in context
 1  libc.so.6 + 0x21c87
    rbx = 0x0000000000000000   rbp = 0x000056097c623ca0
    rsp = 0x00007fff35dec6c0   r12 = 0x000056097c612300
    r13 = 0x00007fff35dec790   r14 = 0x0000000000000000
    r15 = 0x0000000000000000   rip = 0x00007f077ac44c87
    Found by: call frame info
 2  ld-linux-x86-64.so.2 + 0x108d3
    rsp = 0x00007fff35dec740   rip = 0x00007f077b7e48d3
    Found by: stack scanning
 3  breakpad_samples!_start + 0x2a
    rsp = 0x00007fff35dec780   rip = 0x000056097c61232a
    Found by: stack scanning
 4  0x7fff35dec788
    rsp = 0x00007fff35dec788   rip = 0x00007fff35dec788
    Found by: call frame info

Loaded modules:
0x56097c610000 - 0x56097c628fff  breakpad_samples  ???  (main)
0x7f077a885000 - 0x7f077aa21fff  libm.so.6  ???
0x7f077ac23000 - 0x7f077ae09fff  libc.so.6  ???  (WARNING: No symbols, libc.so.6, 327430F7B1A837627E77A182B6CC2E530)
0x7f077b014000 - 0x7f077b02afff  libgcc_s.so.1  ???
0x7f077b22c000 - 0x7f077b3a4fff  libstdc++.so.6  ???
0x7f077b5b5000 - 0x7f077b5cefff  libpthread.so.0  ???
0x7f077b7d4000 - 0x7f077b7fcfff  ld-linux-x86-64.so.2  ???  (WARNING: No symbols, ld-linux-x86-64.so.2, 4C01A89E20F0A2219E57AA3E0512E9BB0)
0x7fff35df4000 - 0x7fff35df5fff  linux-gate.so  ???
```
