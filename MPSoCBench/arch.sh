cd tools/archc 
make distclean
./configure --prefix=/home/felippi/tools2/MPSoCBench/tools/archc --with-systemc=/home/felippi/tools2/MPSoCBench/tools/systemc --with-tlm=/home/felippi/tools2/MPSoCBench/tools/systemc/include
make
make install
cd ../..
