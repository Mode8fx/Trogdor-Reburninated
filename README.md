# Trogdor Reburninated
This is an enhanced recreation of the Homestar Runner Flash game, _Trogdor_. It is currently available for PC, Switch, Wii U, Wii, 3DS, Vita, and PSP.

Homestar Runner is no stranger to [fan ports](https://www.mrphlip.com/ds/pop_tire/) of its [Flash games](https://www.mrphlip.com/ds/secret/), and its impact on Flash media, as well as Internet media as a whole, cannot be overstated. Though the original game is still playable on modern devices through its [HTML5 port](https://old.homestarrunner.com/trogdor-canvas/index.html), this project aims to expand on the original release with new features and multiplatform libraries that allow for porting to a wide variety of systems.

<img src="https://github.com/Mips96/Trogdor-Reburninated/blob/main/screenshots/gameplay_v1.0.png?raw=true" width="480" height="360"/>

## Features
- A faithful recreation of the original Flash game, including intermissions
- Change gameplay settings such as enemy speed and points needed for extra lives, or use one of the new difficulty presets
- Support for any frame rate up to 144 FPS (or 30/60, depending on console)
- Save data support, including mid-game progress and high score
- Level select and shuffle
- New cheats, in addition to the original game's Konami code
- Optional soundtrack from the Homestar Runner game *Stinkoman 20X6*
- Screen scaling options for both full-screen and integer scaling/"pixel-perfect"
- Bugs from the original game have been fixed
- Big head mode!

<img src="https://github.com/Mips96/Trogdor-Reburninated/blob/main/screenshots/options_v1.0.png?raw=true" width="480" height="360"/>

## FAQ
### Is this a port? Remake? Remaster?
A bit of everything, but I'm calling it a "recreation".

It was made by opening the original game in a Flash decompiler and porting its ActionScript code and Flash assets to C++ code by hand. There's no way to automate this as far as I know, so everything was rewritten manually. Additionally, Flash and C++ are two completely separate beasts that handle many things in completely different ways; many things that do not require coding in Flash (like animation frames and screen scaling) need to be recreated as code in C++.

That being said, almost all art and sound assets are ported directly from the original game, just reorganized into sprite sheets, with modifications only being made when necessary.

### Will this be ported to \_\_\_\_\_?
This game was made to be compatible with both SDL 1.2 and SDL2 specifically so it could be ported to many systems. In particular, I would like to create a LibRetro core so it runs on a wide variety of systems. You could also try porting it yourself; this is open-source, after all.

### Legal Stuff
This is an unofficial fan project made without any involvement from anyone who contributed to the original game. Trogdor and Homestar Runner are owned by the Brothers Chaps, Mike and Matt Chapman. The original Flash game was programmed by Jonathan Howe.
