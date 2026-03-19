# Timeim 

Time, but improved

## Ascii art

I took images from [@yuanqing](https://github.com/yuanginq) here : [https://gist.github.com/yuanqing/ffa2244bd134f911d365](https://gist.github.com/yuanqing/ffa2244bd134f911d365), thanks :)

## Goal

The goal, since I live in a terminal, is to have a command to nicely display the hour of the day

I also intend to push this to **pacman** or something, and (maybe) on **apt** and **apt-get**

## Usage

Since many paremeters are required, I recommend you to edit your `~/.bashrc` file (or equivalent), to add this line :
`alias timeim="timeim --hours --minutes --seconds --color nuanced"`, or anything really, experiment and tweak paremeters as you please

> Don't forget to run `source ~/.bashrc`

### From source

1. Get the code ( `git clone https://github.com/Greensky-gs/timeim && cd timeim` )
2. Install **gcc** and **make** if you don't already have them ( common installations : `pacman -S gcc make`, `apt install gcc make` ... )
3. Compile the projet. **Make sure the `src` and `assets` folder are at the same location**.
  * You can use `sudo make install` for a global installation
  * You can use `make DATADIR=./assets` for a local installation, but now your `./assets` must be in the same directory as the executable. You can tweak this path if you want (ie: to an absolute path) 
4. Execute the code generated in the **bin** directory : it has a **timeim** executable file, if everything went fine

## Issues

If you see an issue or an improvement, please let me know ( by creating an issue for instance )
