# Battery Notifier for Linux
This is my first project of the year. I have been using Linux since last year and I've noticed some clean
installs in distributions such as Arch Linux doesn't come with a battery notifier unless your DE (Desktop Environment) comes with it.
WMs (Window Managers) doesn't come with a battery notifier, you would have to install a custom dotfiles which comes with it (unlikely), or make yourself one.

So, I've decided to make my own battery notifier, so you don't have to.

It happens sometimes that you are working on a project, or doing work on your minimal setup. Suddenly, your system turns off, losing progress.
That's very stressing. It has also happened to me, and not just once. So I have made a solution for that problem.

I've built this program for learning purposes, so there is no A.I. code, I have only used the documentation of the used libraries.

This program is a good option for those who need a lightweight notifier and still seeks minimalism. I am improving this code to use less processing power
as possible, how all things should've been done.

## How to Install?

Make sure you have the dependencies before installing

Arch Linux:
```bash
sudo pacman -S libnotify dunst
```

Debian/Mint/Ubuntu:
```bash
sudo apt install libnotify-dev dunst
```

RHEL/Fedora/CentOS:
```bash
sudo dnf install libnotify-devel dunst
```

After installing the dependencies, execute the following command:

```
git clone https://github.com/surufel/BatteryNotifier.git && cd BatteryNotifier && bash ./install.sh
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
