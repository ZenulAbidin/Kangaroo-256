#!/bin/bash
ccap=""
cd deviceQuery
echo "Attempting to autodetect CUDA compute capability..."
make >cuda_build_log.txt 2>&1 && ccap=$(./deviceQuery | grep "CUDA Capability" |  awk -F '    ' '{print $2}' | sort -n | head -n 1 | sed 's/\.//')
if [ -n "${ccap}" ]; then
	echo "Detected ccap=${ccap}"
else
	echo "Autodetection failed, falling back to ccap=30 (set the ccap variable to override this)"
	ccap="30"
fi
cd -
echo ${ccap} > cuda_version.txt
