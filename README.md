# SLog

A simple logging utility.

## Setting Logging Verbosity
Logging verbosity can be globally set using the `S_LOG_V` environment variable. A value of `0` corresponds to the lowest logging severity (most verbose), `DEBUG` and a value of `5` corresponds to the highest, `CRITICAL`.

## Disabling SLog Stream Overloads
SLog provides overloads for the stream operator, i.e. `operator<<`. These can be disabled by defining `DISABLE_S_LOG_STREAM_OVERLOADS` before including `SLog.hpp`.
