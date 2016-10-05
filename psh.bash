#!/bin/bash

cd /home/slacker007/unix_enumerator

git add -A

if[$# -eq 0]

then

git commit -m "General Commit"

else

git commit -m "$*"

fi

git status

git push origin master
