#!/bin/bash

mkdir ~/myDirectory/secondDirectory -p
cd ~/myDirectory/secondDirectory
touch myNotePaper
cp myNotePaper ..
cd ..
mv myNotePaper myOldNotePaper