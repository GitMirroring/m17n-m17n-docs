#!/bin/sh

IMDOC=`pwd`/utils/imdoc

set `ls $1/$2`
while [ $# -ge 1 ] ; do
    FILE=$1
    IM=`grep '^(input-method' $FILE`
    if test -n "$IM"; then
	$IMDOC $FILE "$IM"
    else
	echo
	sed -n -e '/^;;; / p' $FILE | sed -e '/^[^;]/ s/$/<br>/' -e '/^;;; / s/^;;; *//'
    fi
    shift
done
