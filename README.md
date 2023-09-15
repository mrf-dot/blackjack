# Blackjack

A multi call cards binary

## Functions

`cards -b`		Play an interactive round of Blackjack
`cards -c<n>`		Print a specific card from an ordered deck
`cards -r`		Print a random card
`cards -o`		Print an ordered deck
`cards -s`		Print a random deck.
`cards -h`		Print a help message

## Randomness

This code uses a self-made randomness library based on the [xorshift](https://prng.di.unimi.it) algorithm. It only has one dependency: the Linux randomness header, which allows it to access Linux's true random number generator. This program could easily be ported to Mac, and perhaps a bit more difficultly be ported to Windows.

# Compilation / Installation

Due to this program's simplicity, it is very simple to compile it and install it onto your system. First, clone the git repository.

```sh
git clone https://github.com/mrf-dot/blackjack
```

Then, enter the cloned directory.

```sh
cd blackjack
```

Compile the cards binary using your preferred C compiler.

```sh
cc -O1 -o cards cards.c
```

Make sure to allow execute permissions.

```sh
chmod +x cards
```

Finally, run the program.

```sh
./cards
```

If you would like to make the installation universal (ie be able to run the program by simply typing `cards` onto the command line) you can move the binary to your local installation folder.

```sh
sudo mv cards /usr/local/bin/cards
```
