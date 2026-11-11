#!/bin/sh

[ -d tmp ] || mkdir tmp

case $1 in
*) LC_ALL=ja_JP.UTF--8 ruby -Ku utils/ja_filter.rb $1;;
esac
