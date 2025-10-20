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