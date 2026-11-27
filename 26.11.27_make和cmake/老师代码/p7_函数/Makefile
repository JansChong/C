#A = $(subst aa,12,abaacd)

#A = $(patsubst %.c,%.o,a.c b.c)

A = /etc/init.d /usr/bin/man
B = $(addprefix C:,$(A))

.PHONY: all
all:
	@echo $(A)
	@echo $(B)