# Trogdor: Reburninated
This project aims to be an enhanced recreation of the Homestar Runner Flash game, Trogdor. It is available for PC, Android, Switch, Wii U, Wii, Gamecube, Vita, and PSP.
This project will be released in three phases, described below.

**Trogdor Beta (coming soon)**
- A gameplay-complete recreation of the original Trogdor Flash game
- As the name implies, this is a beta
- Certain art and animation-related things (most notably, cutscenes) are incomplete, though a few bugs from the original game are also fixed
- This milestone is mostly for my own benefit and probably won't be publicly released until after the next major version is completed

**Trogdor Classic (coming less soon)**
- A complete recreation of the original game
- The unused high score screen from the original game is restored
- An arcade cabinet-style overlay around the game window

**Trogdor: Reburninated (coming eventually)**
- An enhanced version of the original game, inspired by the many Xbox Live Arcade ports of 80s and 90s arcade games
- Includes a variety of gameplay customization options
- New overlays and music options
- Achievements
- And more...

## FAQ
### Why?
I started making this as a way to get a better understanding of making games using C++ and SDL, and to make a game that would be compatible with both SDL 1.2 and SDL 2, allowing for ports to many different systems. However, it has ended up being *much* more work than I originally anticipated.

Homestar Runner is no stranger to [fan ports](https://www.mrphlip.com/ds/pop_tire/) of its [Flash games](https://www.mrphlip.com/ds/secret/), and it still deserves recognition even today. As for Trogdor specifically, the game exclusively uses pixel art (unlike many other Flash games which rely on vector graphics), and I was able to quickly come up with ways that it could be improved through customization of what's already there.

### What systems will this be released on?
This will be available for PC, Android, Switch, Wii U, Wii, Gamecube, Vita, and PSP. After Reburninated, I will look into porting to other systems, but no promises. I have a few systems in mind that I would definitely like to at least attempt.

### Can't I just play the original Flash version? Or the official HTML5 port?
Sure, but not on all those consoles! <sub>(except Wii)</sub> And the ultimate goal is the release of Reburninated, which aims to be the definitive way to play the game.

### Is this a port? Remake? Remaster?
A bit of everything, but I'm calling it a "recreation".

It was made by opening the original game in a Flash decompiler and porting the original ActionScript code and Flash assets to C++ code by hand. There's no way to automate this as far as I know, so everything was rewritten manually. Additionally, Flash and C++ are two completely separate beasts that handle many things in a completely different way; many things that do not require coding in Flash (like animation frames) need to be recreated as code in C++.

That being said, almost all art and sound assets are ported directly from the original game, with modifications only being made when necessary.

### When will everything be released?
Beta will already be released by the time this repo becomes public.

Classic will also probably be released when this repo goes public, but in case it's not, let's just say... September 2022?

Reburninated will be done when it's done, but I'd like to have it finished by January 13, 2023 (Trogdor's 20th birthday). If not, then before March 17, 2023 (the 20th anniversary of the Flash game). But I'm only working on this as a hobby, so we'll see.

### Legal Stuff
This is an unofficial fan project made without any involvement from anyone involved with the original game. Trogdor and Homestar Runner are owned by the Brothers Chaps, Mike and Matt Chapman.
