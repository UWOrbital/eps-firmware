# TIMER App

Logs time since board boot in milliseconds in periods of 4 seconds and 2 seconds

Use of zephyr timers here has less overhead than a while loop using `k_ms_sleep`
