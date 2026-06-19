#!/usr/bin/env bash
set -euo pipefail

echo "== /proc/meminfo =="
cat /proc/meminfo

echo
echo "== /proc/vmstat =="
cat /proc/vmstat

echo
echo "== /proc/stat =="
cat /proc/stat
