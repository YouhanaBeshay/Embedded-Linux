#!/bin/bash
if [ -f ~/.bashrc ]; then
    echo "found .bashrc"
    echo "export HELLO=HOSTNAME" >> ~/.bashrc
    value=$(whoami)
    echo "LOCAL=$value" >> ~/.bashrc
    echo "Appended variables to .bashrc , will open a new terminal"
    gnome-terminal
fi