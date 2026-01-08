# Battery Notifier for Linux
This is my first project of the year. I have been using Linux since last year and I noticed some clean
installs in distributions like Arch Linux, doesn't really come with a battery notifier (telling the user when
the battery is low, critically low, is charging). Such as mine.

So, I've decided to make my own battery notifier.

It happens sometimes that you are using the distribution and your device turns off. That's very stressing.
This has also happened to me.

I've built this program for learning purposes, so there is no A.I. (Artificial Intelligence) code, I only
have used the documentation of the used libraries.

Of course, there are repositories that solves the same problems as mine, maybe better. But as I have said before,
This is a code made purely for learning purposes. I am improving this code to use less processing power
as possible, how all things should've been done.

I don't know if I will program a customized pop-up program in the future. But feel free to use dunst.

## How to Install?

For now, the Makefile is only made to install the dependencies for Arch Linux.
For the pop-up notifications, you'll need Dunst or an alternative for it.

First, you'll have to clone the Git repository:

```
git clone https://github.com/surufel/BatteryNotifier.git
```

Then, you'll have to go inside the directory through the terminal, and type:

```bash
make
```

The dependencies will be installed, and the program will be compiled as well.
You will need the code and the popup program to be running in the background.

I will change the installation method soon.


## For the popup:
Dunst: https://github.com/dunst-project/dunst

Arch Linux:
```
sudo pacman -S dunst
```

You can use other alternatives as well.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
