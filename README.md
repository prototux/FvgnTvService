# FvgnTvService
A Replacement for TCL/Thomson's SmartTV2 software

## What the heck is this

This is a replacement for the "sitatvservice" binary found in TCL/Thomson S69 series TVs, the original service manage pretty much everything on the TV, this replacement intends to only implement parts of it's features, and add a RESTful API to control the TV.

## Who is responsible for this name?!?

`"fvgn" = rot13("sita")`, i didn't had any other idea when i created this repo; "sitatvservice" is the original binary name, hence, "fvgntvservice".

## Should i install this on my TV?

Probably not unless you are well aware of what's implemented and what's not, and are OK with fvgn's features, or lack thereof.

## How can install this?

* Get a root shell for your TV
* Get the libraries in `/applications/soc_libs`, and [libonion](https://github.com/davidmoreno/onion) cross compiled for armhf.
* Compile fvgn and link it against the `soc_libs`
* Copy the binary you just compiled in `/applications/tv_bin` or any other place you'd like
* Replace `sitatvservice` with `fvgntvservice` in `/applications/tv_bin/run.sh`
* Done

### Ok, but how do i get a root shell in my TV?

There's no automated way to do it, follow instructions in [TCL-TV-RE](https://github.com/prototux/TCL-TV-reverse-engineering), if you find a way to do it remotely, that'd be awesome!

## What's it features?

NB: The "Sita only" features are ones that i didn't planned to do, if somebody ask for it or contribute it, it may change. (these are not planned because i personaly have no use for it or my TV doesn't support it)

### Feature table / "sita vs fvgn" / Status
| Feature                  | sita vs fvgn | Status |
| ------------------------ | ------------ | ------ |
| Power on sequence        | sita + fvgn  | todo   |
| Input selection          | sita + fvgn  | todo   |
| TV Channel selection     | sita only    |        |
| Teletext + subtitles     | sita only    |        |
| MHEG5 and HbbTV          | sita only    |        |
| HDCP2                    | sita only    |        |
| Video parameters         | sita + fvgn  | todo   |
| IR Remote control        | sita only    |        |
| API remote control       | fvgn only    | todo   |
| 3D mode                  | sita only    |        |
| OSD Ui                   | sita only    |        |
| OSD notifications        | fvgn only    | todo   |
| FakeOff mode             | fvgn only    | todo   |
| Audio control            | sita + fvgn  | todo   |
| Smart TV apps            | sita only    |        |
| TV recording/PVR         | sita only    |        |
| CI+                      | sita only    |        |
| IPEPG/EPG                | sita only    |        |
| MHL                      | sita only    |        |
| DLNA/UPNP/Miracast       | sita only    |        |
| Media player/netflix     | sita only    |        |
| HDMI-CEC/HDMI-ARC        | Sita only    |        |

## Some more deatils about features

* Input selection: For now i don't plan to fully implement scart and vga because they need some specialized functions.
* TV features (Channel selection, Teletext/Subtitles, MHEG5/HbbTV, PVR, CI+, EPG...): I dont' plan to implement TV features, i don't watch TV at all. besides, in france, almost everybody have set-top-boxes.
* HDMI Extensions (HDCP2, CEC, ARC, MHL): i didn't looked into it much, maybe i'll implement some of them later, not planned now.
* IR Remote control: The plan is to only use the API, so i didn't looked into it
* OSD: I don't plan to display an OSD when there's events (volume change, etc), neither do i plan to implement a UI with menus and the like, because i plan to only use the API, and not the IR remote. I do plan to do stuff with OSD like notifications sent to the API and maybe other features like that.
* SmartTV apps/media player/netflix: The goal is to have a "dumb tv" aka "computer screen".
* DLNA/UPNP/Miracast: I don't plan to implement these are they are quite complicated and i can do it with my PC instead.
* 3D Mode: My TV doesn't support it, so no plan to implement it...
