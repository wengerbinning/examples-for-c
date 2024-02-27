
obj-m += develproc.o

obj-m += develnet.o
obj-m += develskb.o

obj-m += develcrypto.o

# develproc
develproc-objs += proc.o

#develnet
develnet-objs += net.o

# develskb
develskb-objs += skb.o

# develcrypto
develcrypto-objs += crypto.o

clean:
	-rm -rf *.o
	-rm -rf *.ko *.mod *.mod.c .*.cmd
	-rm -rf Module.symvers modules.order
	