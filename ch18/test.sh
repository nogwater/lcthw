#!/bin/bash
# set -e # let us know if there are errors

echo Lets get started.

echo Create a database
./ec17 db.dat c 512 100

echo Populate it
./ec17 db.dat s 0 34 Aaron aaron@apejet.org
./ec17 db.dat s 1 34 Jesse jesape@gmail.com
./ec17 db.dat s 2 99 Joe joe@gmail.com

echo List it
./ec17 db.dat l

echo Search for Aaron
./ec17 db.dat f Aaron

echo Search for 34
./ec17 db.dat f 34

echo Delete Aaron
./ec17 db.dat d 0

echo List it
./ec17 db.dat l

echo Get address 1
./ec17 db.dat g 1
