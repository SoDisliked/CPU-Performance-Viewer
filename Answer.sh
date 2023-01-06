#!/bin/sh
# Ask a command and return the answer

QUESTION=$1
PARM=$2
TEXT_FILE=$3
while :; do
         echo -n "${QUESTIONS} [${PARM}]" >/dev/tty
         read answer 
         if ["${ANSWER}" = ""]; then 
                break 
        elif ["${ANSWER}" = "?"]; then 
                cat build/${TEXT_FILE} >/dev/tty 
        else 
                echo ${ANSWER}
                break 
        fi 
done 