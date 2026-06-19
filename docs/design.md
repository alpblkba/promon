# promon design

promon is split into three layers:

1. collectors: platform-specific metric collection
2. core model: normalized snapshots and metric types
3. renderers: CLI/TUI/Qt presentation

The collector layer must not print directly.
The UI layer must not parse /proc or call Mach APIs directly.
