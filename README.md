# Trogdor Reburninated
This project aims to be an enhanced recreation of the Homestar Runner Flash game, Trogdor. It is currently available for PC, Switch, Wii U, Wii, Gamecube, Vita, and PSP.
This project will be released in four phases, described below.

**Trogdor Beta (available now)**
- A gameplay-complete recreation of the original Trogdor Flash game
- As the name implies, this is a beta
- Certain art and animation-related things (most notably, cutscenes) are incomplete, though a few bugs from the original game are also fixed
- This milestone is mostly for my own benefit and probably won't be publicly released until after the next major version is completed

**Trogdor Classic (coming soon)**
- Additional Android port
- A complete recreation of the original game
- New Options menu with customizable settings
- Additional Overlay settings

**Trogdor Plus (coming less soon)**
- Additional LibRetro port
- The unused high score screen from the original game is restored
- Hi-Res sprite mode

**Trogdor Reburninated (coming eventually)**
- An enhanced version of the original game, inspired by the many Xbox Live Arcade ports of 80s and 90s arcade games
- Includes a variety of gameplay customization options
- New overlays and music options
- Achievements
- And more...

## FAQ
### Why?
I started making this as a way to get a better understanding of making games using C++ and SDL, and to make a game that would be compatible with both SDL 1.2 and SDL 2, allowing for ports to many different systems. However, it has ended up being *much* more work than I originally anticipated.

Homestar Runner is no stranger to [fan ports](https://www.mrphlip.com/ds/pop_tire/) of its [Flash games](https://www.mrphlip.com/ds/secret/), and it still deserves recognition today. As for Trogdor specifically, the game exclusively uses pixel art (unlike many other Flash games which rely on vector graphics), and I was able to quickly come up with ways that it could be improved through customization of what's already in the original game.

### What systems will this be released on?
This will initially be available for PC, Switch, Wii U, Wii, Gamecube, Vita, and PSP. Android and LibRetro ports will likely be released at a later date. After Reburninated, I will look into porting to other systems, but no promises.

### Why are there multiple versions? And when will they be released?
The multiple versions are for my own benefit, and to allow the game to be released in a playable state sooner. Each version will be an update, so you only need to consider playing the latest version. As for release dates:
- *Beta*: Available now (once this repo becomes public)
- *Classic*: Probably available once this repo goes public, but in case it's not, let's say... October 2022?
- *Plus*: Sometime before January 13, 2023 (Trogdor's 20th birthday)
- *Reburninated*: It'll be done when it's done, but I'd like to have it finished by March 17, 2023 (the 20th anniversary of the Flash game). But I'm only working on this as a hobby, so we'll see.

### Is this a port? Remake? Remaster?
A bit of everything, but I'm calling it a "recreation".

It was made by opening the original game in a Flash decompiler and porting its ActionScript code and Flash assets to C++ code by hand. There's no way to automate this as far as I know, so everything was rewritten manually. Additionally, Flash and C++ are two completely separate beasts that handle many things in a completely different way; many things that do not require coding in Flash (like animation frames) need to be recreated as code in C++.

That being said, almost all art and sound assets are ported directly from the original game, just reorganized into sprite sheets, with modifications only being made when necessary.

### Can't I just play the original Flash version? Or the official HTML5 port?
Sure, but not on all those consoles! <sub>(except Wii)</sub> And the ultimate goal is the release of Reburninated, which aims to be the definitive way to play the game, even on PC.

### Legal Stuff
This is an unofficial fan project made without any involvement from anyone who contributed to the original game. Trogdor and Homestar Runner are owned by the Brothers Chaps, Mike and Matt Chapman. The original Flash game was programmed by Jonathan Howe.
