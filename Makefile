battery-notifier:	battery-popup.c
	gcc battery-popup.c -o battery-notifier `pkg-config --cflags --libs libnotify`

