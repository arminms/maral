#!/bin/sh
if [ $# -eq 1 ]; then
	svn copy https://subversion.assembla.com/svn/maral/trunk https://subversion.assembla.com/svn/maral/tags/$1 -m "Tagging the $1 release"
else
  echo "Usage: $0 version"
fi
