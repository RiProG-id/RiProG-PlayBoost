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

## v2.0.2 Patch Update

- Added support for AxManager version 13000
- Improved installation method
- Fixed random reboot issue after uninstall completion

## v2.0.3 Patch Update

- Switched uninstall.sh to BKT.sh using service.d method  
- Fixed bootloop issue when module is removed

## v2.0.4 Patch Update

- Fixed missing or non-working toast notifications  
- Fixed Toast app not uninstalling with module/plugin

## v2.0.5 Patch Update

- Fixed code typos
- Improved applist initialization and file check
-

## v2.0.6 Patch Update

- Fixed incomplete uninstall process
- Fixed Toast not appearing or not being installed
- Updated game list
- Fixed code typos