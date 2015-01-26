# Makefile for Conditional Variables Server (CV)
PROG=	cv
SRCS=	main.c queue.c mutex.c cond_var.c

DPADD+=	${LIBSYS}
LDADD+=	-lsys

MAN=

BINDIR?= /usr/sbin
FILES=cv.conf
FILESNAME=cv
FILESDIR= /etc/system.conf.d

.include <minix.bootprog.mk>
