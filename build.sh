#!/bin/bash

dos2unix patch_bin.py

rm -rf ./out

echo export PATH="${PATH}:/opt/sh2-toolchain/bin" >> ~/.bash_rc
source ~/.bash_rc

make