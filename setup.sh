# setup.sh
#
# David Adams
# January 2020

if [ -n "$DUNESLOW_DIR" ]; then
  echo It appears duneslow is already set up:
  echo DUNESLOW_DIR = $DUNESLOW_DIR

elif [ -z "$DUNETPC_VERSION" ]; then
  echo "Please set up dunetpc."

else

echo Setting up duneslow
DUNESLOW_DIR=$(dirname $(readlink -f $BASH_SOURCE))
PATH=$DUNESLOW_DIR/bin:$PATH
TMPPATH=.:./job:
if [ ${FHICL_FILE_PATH:0:8} = $TMPPATH ]; then FHICL_FILE_PATH=${FHICL_FILE_PATH:8}; fi
FHICL_FILE_PATH=${TMPPATH}$DUNESLOW_DIR/fcl:$FHICL_FILE_PATH
unset TMPPATH

fi

