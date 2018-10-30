# FvgnTvService
A Replacement for TCL/Thomson's SmartTV2 software

## What the heck is this

This is a replacement for the "sitatvservice" binary found in TCL/Thomson S69 series TVs, the original service manage pretty much everything on the TV, this replacement intends to only implement parts of it's features, and add a RESTful API to control the TV.

## Who is responsible for this name?!?

`"fvgn" = rot13("sita")`, i didn't had any other idea when i created this repo; "sitatvservice" is the original binary name, hence, "fvgntvservice".

## Should i install this on my TV?

Probably not unless you are well aware of what's implemented and what's not, and are OK with fvgn's features, or lack thereof. and you should know that fvgntvservice is probably not as stable as sitatvservice currently.

## How can install this?

* Get a root shell for your TV
* Get the libraries in `/applications/soc_libs`, and [libonion](https://github.com/davidmoreno/onion) cross compiled for armhf.
* Compile fvgn and link it against the `soc_libs`
* Copy the binary you just compiled in `/applications/tv_bin` or any other place you'd like
* Replace `sitatvservice` with `fvgntvservice` in `/applications/tv_bin/run.sh` (or put it next to sitatvservice)
* Done

### Ok, but how do i get a root shell in my TV?

There's no automated way to do it, follow instructions in [TCL-TV-RE](https://github.com/prototux/TCL-TV-reverse-engineering), if you find a way to do it remotely, that'd be awesome!

## What's it features?

NB: The "Sita only" features are ones that i didn't planned to do, if somebody ask for it or contribute it, it may change. (these are not planned because i personaly have no use for it or my TV doesn't support it)

### Feature table / "sita vs fvgn" / Status

It is a very early project, so don't expect any usuable binary soon.

| Feature                  | sita vs fvgn | Status |
| ------------------------ | ------------ | ------ |
| Power on sequence        | sita + fvgn  | ok     |
| Input selection          | sita + fvgn  | ok     |
| TV Channel selection     | sita only    |        |
| Teletext + subtitles     | sita only    |        |
| MHEG5 and HbbTV          | sita only    |        |
| HDCP2                    | sita only    |        |
| Video parameters         | sita + fvgn  | ok     |
| IR Remote control        | sita only    |        |
| API remote control       | fvgn only    | ok     |
| 3D mode                  | sita only    |        |
| OSD Ui                   | sita only    |        |
| OSD notifications        | fvgn only    | todo   |
| FakeOff mode             | fvgn only    | ok     |
| Audio control            | sita only    |        |
| Smart TV apps            | sita only    |        |
| TV recording/PVR         | sita only    |        |
| CI+                      | sita only    |        |
| IPEPG/EPG                | sita only    |        |
| MHL                      | sita only    |        |
| DLNA/UPNP/Miracast       | sita only    |        |
| Media player/netflix     | sita only    |        |
| HDMI-CEC/HDMI-ARC        | Sita only    |        |

## Configuration

The configuration file is at `/etc/fvgntvservice.conf`, and the path can be overriden with the `FVGN_CONFIG` env variable. There's an example config file to get you started.

## Some more deatils about features

* Input selection: For now i don't plan to fully implement scart and vga because they need some specialized functions.
* Audio: i'd like to implement this, but i have no use for it as i use an external amplifier, so it's a "nice to have" but comes after... everything else, basically.
* TV features (Channel selection, Teletext/Subtitles, MHEG5/HbbTV, PVR, CI+, EPG...): I dont' plan to implement TV features, i don't watch TV at all. besides, in france, almost everybody have set-top-boxes.
* HDMI Extensions (HDCP2, CEC, ARC, MHL): i didn't looked into it much, maybe i'll implement some of them later, not planned now.
* IR Remote control: The plan is to only use the API, so i didn't looked into it
* OSD: I don't plan to display an OSD when there's events (volume change, etc), neither do i plan to implement a UI with menus and the like, because i plan to only use the API, and not the IR remote. I do plan to do stuff with OSD like notifications sent to the API and maybe other features like that.
* SmartTV apps/media player/netflix: The goal is to have a "dumb tv" aka "computer screen".
* DLNA/UPNP/Miracast: I don't plan to implement these are they are quite complicated and i can do it with my PC instead.
* 3D Mode: My TV doesn't support it, so no plan to implement it...

## What models it works on
It's designed to work with the U55S6906, but may work with these models, YMMV.
55UA7706, 49UA7706, 65UA8696, 85UZ8876, 49UA7706, 55UA8696, 55UA9806, U55S6806S, U50S6806S, U50S7806S, L32E4300CE_LSC, U58S7806S, 50UA6406/W, 55UA6406/W, U40S6806S, 40UA6406, 65UA6606, U65S7806S, U65S8806DS, U55S8806DS, 65UA8696-2, LSC460HJ03-S, LT-50HW77U, LT-55HW77U, U55S6806S, 55UA6406/W, LT-55HW77U, U50S6806S, 50UA6406/W, LT-50HW77U, 65UA8796, 55UA8796, LSC460HJ03-S, 78UA8796, 55UB7506, 50UB7506, U55S6906, 55UA6406/W, U55S6806S, U50S6906, 55E5900US, 50E5900US, 40E5900US, LSC460HJ03-S, U50S7806S, U58S7806S, 65UB7506, 65UB7596, 65E5900US, 65C1US, 65C1CUS, 55C1US, 55C1CUS, 55UA8596, 32UA7706, U50S7906, U55S7906, U65S7906, U40S6906, U55S6906, U50S6906, 40UB6406, 50UB6406, 55UB6406, U55S8866S, 55UA7706, 55E5900US, 55UA7706, 32UA7706, U50S7806S, U58S7806S, 50UA6406W, 55UA6406W, 65UB6406, 65E5900US, 70P10US, LSC460HJ03-S, 60E6000US, U50S7906, U65S7906, 65C1US, 49P10US, 43P10US, 55UB6406, U55S6906, 55UA6406W, 65UB6406, 55UA7706, U43S6916, U55SC6916, U49SC6916, 55E5900US, 55UA6406W, LSC460HJ03-S
