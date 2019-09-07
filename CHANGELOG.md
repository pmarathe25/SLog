# STest Changelog
Dates are in YYYY-MM-DD format.

## v0.2.1 (2019-09-07)
- Updates build system

## v0.2.0 (2019-07-31)
- Headers are no longer included when logging components are disabled.
- All macros are now prefixed with `S_`
- Adds `S_ASSERT` - an assert that is only active in debug builds.

## v0.1.0 (2019-07-24)
- Refactors `Logger` to move part of the implementation into `Logger.cpp`
- Disables logging unless `S_DEBUG` is defined (which `SBuildr` will do automatically for debug builds)
- Adds overloads for `operator<<` for `std::type_info`
- Adds `LOG_RAW` for fold-expression friendliness
- Changes all logging such that when logging is disabled, there is zero runtime cost.
