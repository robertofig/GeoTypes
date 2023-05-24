#!/bin/sh

set -u

BSE='test-base'
WKB='test-wkb'
SHP='test-shp'
TinyBasePath=''
CompileOpts='-I../src -I${TinyBasePath} -g -Wall -mavx2 -fpermissive -w'

mkdir -p ../build
cd ../build
g++ -o ${BSE} ../tests/${BSE}.cpp ${CompileOpts}
g++ -o ${WKB} ../tests/${WKB}.cpp ${CompileOpts}
g++ -o ${SHP} ../tests/${SHP}.cpp ${CompileOpts}
cd ../tests