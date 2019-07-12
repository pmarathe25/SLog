# STest Changelog
Dates are in YYYY-MM-DD format.

## vNext()
- Refactors `Logger` to move part of the implementation into `Logger.cpp`
- Disables logging unless `S_DEBUG` is defined (which `SBuildr` will do automatically for debug builds)
