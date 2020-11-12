#!/bin/bash

##
## Starts the TCP socket client
## and transmits a message.
##

CMD="java -jar"
BASE_DIR=`dirname $0`
JAR="${BASE_DIR}/Home-1.0-SNAPSHOT.jar"
${CMD} ${JAR} $@
