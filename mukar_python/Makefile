_IceKey.so: IceKey_wrap.cxx
	g++ -fPIC -shared IceKey.cpp IceKey_wrap.cxx -o _IceKey.so -I/usr/include/python3.6

IceKey_wrap.cxx: IceKey.cpp IceKey.h IceKey.i
	swig -c++ -python IceKey.i

.PHONY: clean
clean:
	rm IceKey_wrap.cxx _IceKey.so IceKey.py
