GNUMAKE?=gmake

all:
	${GNUMAKE} $@ BSD=1

.DEFAULT:
	${GNUMAKE} $@ BSD=1

.PHONY: all
