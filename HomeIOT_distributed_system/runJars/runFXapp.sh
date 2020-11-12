#!/bin/bash

##
## Starts the TCP socket client
## and transmits a message.
##

CMD="/usr/lib/jvm/java-8-openjdk-amd64/bin/java -Dfile.encoding=UTF-8 -jar"
BASE_DIR=`dirname $0`
JAR="${BASE_DIR}/JavaFXApp/JavaFXApp.jar"
${CMD} ${JAR} $@

