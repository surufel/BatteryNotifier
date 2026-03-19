#!/bin/bash

gcc battery-popup.c -o battery-notifier `pkg-config --cflags --libs libnotify`
chmod +x battery-notifier
sudo mv battery-notifier /usr/local/bin/

echo "[+] Installation completed. Make sure to start the program as soon you start the session."
