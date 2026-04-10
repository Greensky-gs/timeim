% TimeIM(1) TimeIM User Manuals
% Greensky-gs
% April 2026

# Name

timim - Time IMproved, date displayer

# SYNOPSIS

timeim [*OPTIONS*]

# DESCRIPTION

TimeIM is a small C program that aims to nicely display the date in the terminal, ideally to replace `date`. It displays the current **time**, with hours, minutes and seconds. If no **OPTIONS** are given, it defaults to help page

TimeIM will get the time of the day, get the appropriates ascii art files, and then will write the output in the terminal.

    timeim --hours --minutes --suffixes

# OPTIONS

-h,    \--help : Displays help page. If this option is given, it will override any other option

    timeim
    timeim -h
    timeim --help
    timeim --hours --minutes --seconds --suffixes -h

-m,    \--minutes : Toggles minutes in the result. Minutes are displayed after the hours (and its optional suffix), if they are enabled. The suffix for minutes is **m**.

    timeim --minutes
    timeim -m

-s,    \--seconds : Toggles seconds in the result. Seconds are displayed after the minutes (and its optional suffix), if they are enabled. The suffix for seconds is **s**. In 12 hours format, seconds cannot be displayed.

    timeim -s
    timeim --seconds

-f *FORMAT*,    \--format *FORMAT* : Specifies the format of the output. *FORMAT* is either 12 for 12-hours format displaying, or 24 for 24-hours time format. In 12-hours format, seconds cannot be specified. If they are, they are simply ignored. If `--suffixes` is given, the suffixes will be **:** in between hours and minutes, and **am** or **pm** after the minutes, depending on the actual time. In 24 hours, suffixes are the units suffixes, if the said units are specified. Default format is 24

    timeim -f 12
    timeim --format 24
    timeim -f 24

\--hours : Toggles hours in the result. Hours are displayed in first, if they are enabled. The suffix for hours is **h**, unless *FORMAT* is set to **12**, where the suffix will be **:** if minutes are also triggered

    timeim --hours
    timeim -f 12 --hours

\--suffixes : Toggles suffixes. In 24 hours format, the suffixes are appended after the given unit. For hours, it is **h**, for minutes it is **m** and **s** for seconds. In 12 hours format, suffixes are **:** in between hours and minutes (it will not be displayed if one of them is not given), and **am** or **pm**. 

    timeim --hours -m -s --suffixes
    timeim --hours -m -f 12 --suffixes

\--color *COLOR MODE* : Add color to the output. *COLOR MODE* can be one of : **suffixes**, to put color only on suffixes, **numbers**, to add colors only on numbers, **all** to put the same color on everything (numbers + suffixes), or **nuanced** to put different colors on numbers and suffixes. It defaults to **none**, that will have the same effect than not specifying the `--color` flag

# EXAMPLES

Display only hours and minutes, without suffixes, in 24 hours format and then in 12 hours format

    timeim --hours --minutes
    timeim --hours -m -f 24
    timeim --hours --minutes --format 24
    timeim --hours -m --format 24
    
    timeim --hours -m -f 12
    timeim --hours --minutes --format 12

Display hours + minutes + seconds + suffixes in 24 hours format, and then in 12 hours format (seconds will not be displayed), without suffixes

    timeim --hours -m -s
    timeim --hours --minutes --seconds --format 24
    timeim --hours -m -s -f 24

    timeim --hours --minutes --format 12
    timeim --hours -m -f 12 -s

Display the time with suffixes, displaying only hours and minutes, with colors. Colors will change depending on the command below

    timeim --hours -m --format 24 --suffixes --color all
    timeim --hours --minutes -f 24 --suffixes --color nuanced
    timeim --hours -m --suffixes --color numbers

    timeim --hours -m --suffixes -f 12 --color nuanced
    timeim --hours -m --suffixes --format 12 --color suffixes

An alias can *(and should)* be defined in the `~/.bashrc` file or so, to defaultly display time in a nice way. An example of such alias can be :

    alias timeim="timeim --hours --minutes --suffixes --color nuanced"
    alias timeim="timeim --hours -m --suffixes --color numbers -f 12"

# SEE ALSO

`date`(1)

