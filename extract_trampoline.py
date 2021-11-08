#!/usr/bin/env python3

import struct
import binascii
import sys

if __name__ == "__main__":
	_, infile = sys.argv
	print(infile)
	with open(infile, 'rb') as in_fp:
		in_fp.read(3840)
		out_fp = open("out/ar_original_trampoline.bin", 'w+b')
		out_fp.write(in_fp.read(68))

