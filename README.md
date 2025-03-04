# pgne3k - Convert **HUGE** multi-game PGNs to CSVs

## Overview

Convert multi-game PGNs to TSVs (CSVs with tabs). This utility was built
specifically to process Lichess monthly game dumps which are
~90 million games in length.

Supports extracting clock times and filtering on minimum ply and tag values.

## Project Health  [![Tests](https://github.com/axolotl-logic/pgne3k/actions/workflows/test.yml/badge.svg)](https://github.com/axolotl-logic/pgne3k/actions/workflows/test.yml) [![Lints](https://github.com/axolotl-logic/pgne3k/actions/workflows/lint.yml/badge.svg)](https://github.com/axolotl-logic/pgne3k/actions/workflows/lint.yml) [![Docs](https://github.com/axolotl-logic/pgne3k/actions/workflows/docs.yml/badge.svg)](https://github.com/axolotl-logic/pgne3k/actions/workflows/docs.yml)

This project is actively used and maintained, but is also under heavy development.

If the three badges above are green, the `main` branch is suitable for use.

## Quickstart

In order to run this tool, you need to create a "tagspec" and allows you to filter
games and also specify what columns you are interested in.

Here is an example spec:

```text
Site
WhiteElo
BlackElo
TimeControl
Ply > 3
Result
WhiteClock
BlackClock
WhiteTitle ! BOT
BlackTitle ! BOT
Event - Bullet
Result ! *
Moves
```

By supplying the tool with this file:

- You get the listed PGN tags and pseudo tags like clock times.
- Only includes games with more than 3 moves played.
- Excludes Lichess Bot accounts.
- Exclude events with the word "Bullet" in them.
- Exclude incomplete games.

## See Also

[Full Documentation](https://pgne3k.axolotl-logic.io/)

[Org Site](https://axolotl-logic.io/)

## Support

Need help? Lonely?

Say hi on our [Discord](https://discord.gg/ewM37225Xx)!

## Contributing

I read all pull requests and issues!

Here's a nifty badge to support my work financially: [![Patreon patrons](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Daxolotl-logic%26type%3Dpatrons)](https://www.patreon.com/axolotl-logic)! And one for Liberapay [![Liberapay patrons](https://img.shields.io/liberapay/patrons/axolotl-logic)](https://en.liberapay.com/Axolotl-Logic)
