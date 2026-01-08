all: dependencies battery-notifier

battery-notifier:	battery-popup.c
	gcc battery-popup.c -o battery-notifier `pkg-config --cflags --libs libnotify`
dependencies:
	sudo pacman -S --needed --noconfirm libnotify dunst
clean: 
	rm -f battery-notifier.x
