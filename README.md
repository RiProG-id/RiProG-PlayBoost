# RiProG-PlayBoost

![RiProG-PlayBoost Banner](https://raw.githubusercontent.com/RiProG-id/RiProG-PlayBoost/main/module/banner.png)

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**Enjoy uninterrupted performance with automatic process prioritization.**

## What is RiProG-PlayBoost?

RiProG-PlayBoost is a utility designed to enhance your device's performance by intelligently managing and prioritizing background processes. This ensures a smooth, lag-free experience, especially during resource-intensive tasks like gaming.

## Features

- **Automatic Prioritization:** Dynamically adjusts process priorities without user intervention.
- **Wide Compatibility:** Supports a variety of rooted and modified Android environments.
- **Lightweight:** Designed to have a minimal impact on system resources.

## v2.0.0 Major Update

This major update introduces significant improvements and bug fixes:

- **Core Stability:** Fixed random reboots.
- **Update Mechanism:** Repaired broken `updateJson` and `zipUrl` links.
- **Performance:**
    - Implemented thread-based optimization using a TID linked list.
    - Replaced the legacy priority system with a more efficient high-affinity `taskset`.
    - Added a 1-second throttle to prevent repetitive `taskset` calls.
    - Introduced `clear_optimized_set()` to prevent potential memory leaks.
    - Extended the main loop interval to 10 seconds for improved CPU efficiency.
- **Compatibility:**
    - Blocked execution with AxManager versions 12000 and higher.
    - Prevented duplicate application entries in the game list.
- **General:**
    - Resolved uninstall and bootloop issues.
    - Reorganized the project structure and updated the `build.sh` script.
    - Implemented various other minor enhancements

## v2.0.1 Patch Update

- Fixed an issue where the binary could not run or had the wrong name

## Compatibility

This tool is compatible with the following platforms:

- [Magisk](https://github.com/topjohnwu/magisk)
- [KernelSU](https://github.com/tiann/KernelSU)
- [APatch](https://github.com/bmax121/APatch)
- [AxManager](https://github.com/fahrez182/AxManager) (versions below 12000)
- Other similar rooted environments.

## Installation

1.  Download the latest release from the [releases page](https://github.com/RiProG-id/RiProG-PlayBoost/releases).
2.  Flash the module through your preferred manager (e.g., Magisk, KernelSU).
3.  Reboot your device.

## Credits

This project incorporates components from other open-source repositories. We extend our thanks to their developers:

- **Toast Notifications:** Based on the [RiProG Toast App](https://github.com/RiProG-id/riprog-toast-app).
- **Game List:** Adapted from [Encore Tweaks](https://github.com/Rem01Gaming/encore).

## Author & Support

**Author:** [RiProG](https://github.com/RiProG-id)

For support, questions, or to get involved with the community, please visit:

- **Sociabuzz:** [sociabuzz.com/riprog/tribe](https://sociabuzz.com/riprog/tribe)
- **Telegram Channel:** [t.me/RiOpSo](https://t.me/RiOpSo)
- **Telegram Group:** [t.me/RiOpSoDisc](https://t.me/RiOpSoDisc)