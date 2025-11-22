![moss](./moss.png)

---

# moss
A header-only C++ utility stack.

## `moss/timer.h`

| Type | Description |
|------|-------------|
| moss::timer::immutable | A timer whose start time is set at creation and cannot be set again. |
| moss::timer::resettable | A timer whose start time can be reset arbitrarily. |
| moss::timer::statistic | A timer that takes multiple measurements and provides some automatic statistics about the timings taken. Sample count can optionally be limited, and samples can be reset at any time. |
| moss::timer::rolling | The same as a statistic timer except samples are always unlimited and are automatically purged past a given time limit. |

## `moss/fileio.h`
