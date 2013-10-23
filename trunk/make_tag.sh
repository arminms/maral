#!/bin/sh
if [ $# -eq 1 ]; then
	svn copy https://pele.bsc.es/subversion/Maral/trunk https://pele.bsc.es/subversion/Maral/tags/$1 -m "Tagging the $1 release"
else
  echo "Usage: $0 version"
fi
