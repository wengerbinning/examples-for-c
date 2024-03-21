ccflags-y := -Iinclude

# ccflags-y := -std=c89 

obj-m += develproc.o
obj-m += develnet.o
obj-m += develskb.o
obj-m += develcrypto.o
obj-m += develkthread.o
obj-m += develethernet.o
obj-m += develtime.o

## module ##

#
develtime-objs += time.o
# develproc
develproc-objs += proc.o

# develkthread
develkthread-objs += kthread.o

#develnet
develnet-objs += net.o

# develskb
develskb-objs += skb.o

# develcrypto
develcrypto-objs += crypto.o

# develethernet
develethernet-objs += ethernet.o








clean:
	-rm -rf *.o
	-rm -rf *.ko *.mod *.mod.c .*.cmd
	-rm -rf Module.symvers modules.order
	