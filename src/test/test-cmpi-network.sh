#!/bin/sh

# test sblim-cmpi-network package

SCRIPT_PATH=`dirname ${BASH_SOURCE}`

#******************************************************************************#

export SBLIM_TESTSUITE_RUN=1;

#******************************************************************************#

declare -a CLASSNAMES[];
CLASSNAMES=([0]=Linux_LocalLoopbackPort [1]=Linux_EthernetPort \
[2]=Linux_TokenRingPort [3]=Linux_IPProtocolEndpoint \
[4]=Linux_CSNetworkPort [5]=Linux_NetworkPortImplementsIPEndpoint)

declare -i max=5;
declare -i i=0;

cd $SCRIPT_PATH
while(($i<=$max))
do
  . $SCRIPT_PATH/run.sh ${CLASSNAMES[$i]} $1 $2 $3 $4 || exit 1;
  i=$i+1;
done
