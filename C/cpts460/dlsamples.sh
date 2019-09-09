#!/bin/bash

mkdir samples
cd samples
wget --no-parent --no-host-directories --recursive  --reject "*.html*" --cut-dirs=2 https://www.eecs.wsu.edu/~cs460/samples/