#!/bin/bash

# --- retrieve APPLI path, relative to $HOME, set ${APPLI}
#     on sarge, "which" gives not allways the absolute path...
     
comName=`which $0`
aa=${comName:0:1}
if test x$aa == x\/; then
  mycom=${comName}
elif test x$aa == x\.; then
  mycom=${PWD}/${comName:2}
else
  mycom=${PWD}/${comName}
fi
APPLI=`echo ${HOME} \`dirname $mycom\` | awk ' { print substr($2,length($1)+2) } '`
#echo $APPLI
export APPLI