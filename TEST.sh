#!/bin/bash

cp -f hello.ko ~/repos/busybox/_install
cd ~/repos/busybox
./REPACK.sh
./RUN.sh
cd /home/ura/repos/examples/test2
