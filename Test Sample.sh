#!/bin/sh
if [ "$1" = "conf" ]
then
	make distclean
	./configure sa_lib_dir=. sar_dir=. conf_dir=. conf_file=sysstat.sysconfig sa_dir=tests --enable-debuginfo
elif [ "$1" = "conflto" ]
then
	make distclean
	./configure sa_lib_dir=. sar_dir=. conf_dir=. conf_file=sysstat.sysconfig sa_dir=tests --enable-debuginfo --enable-lto
elif [ "$1" = "comp" ]
then
	make TFLAGS="-DTEST"
else
	make distclean
	./configure sa_lib_dir=. sar_dir=. conf_dir=. conf_file=sysstat.sysconfig sa_dir=tests --enable-debuginfo && make TFLAGS="-DTEST" && make simtest
fi
if [ "$?" = "0" -a "$1" = "all" ]
then
	make extratest && make distclean && ./configure --disable-nls --disable-sensors --disable-pcp sa_lib_dir=. sar_dir=. conf_dir=. conf_file=sysstat.sysconfig sa_dir=tests --enable-debuginfo && make TFLAGS="-DTEST" && echo "EXTRA TESTS: Success!"
fi