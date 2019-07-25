# STest Changelog
Dates are in YYYY-MM-DD format.

## v0.1.0 (2019-07-24)
- Refactors `Logger` to move part of the implementation into `Logger.cpp`
- Disables logging unless `S_DEBUG` is defined (which `SBuildr` will do automatically for debug builds)
- Adds overloads for `operator<<` for `std::type_info`
- Adds `LOG_RAW` for fold-expression friendliness
- Changes all logging such that when logging is disabled, there is zero runtime cost.
