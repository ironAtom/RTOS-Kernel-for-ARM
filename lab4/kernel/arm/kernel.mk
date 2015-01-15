ARM_OBJS := reg.o psr.o asm_irq_handler.o asm_swi_handler.o enter_user_mode.o handler.o interrupt.o swi.o timer.o 
ARM_OBJS := $(ARM_OBJS:%=$(KDIR)/arm/%)

KOBJS += $(ARM_OBJS)
