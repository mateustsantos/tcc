#!/bin/bash
numproc=1
platform=router.lt
proc=mips
exemplo=dijkstra



./MPSoCBench -n=$numproc -i=$platform -p=$proc -s=$exemplo -b
#cd rundir/$proc.$platform.$numproc.$exemplo
#make >> $proc.$platform.$numproc.$exemplo.txt
cd ../..





