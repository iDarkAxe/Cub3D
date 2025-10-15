#!/bin/bash

VALIDS_MAPS="scripts/maps/valid_maps/"
INVALIDS_MAPS="scripts/maps/invalid_maps/"

CUB3D_EXEC="./cub3D"
FAILED_TESTS=""

CUB_LOG="cub_logs.txt"
VALGRIND_LOG="valgrind_log.txt"

if [[ ! -f "$CUB3D_EXEC" ]]; then
  echo -e "Error: cub3D binary not found at $CUB3D_EXEC\n"
  exit 1
elif [[ ! -x "$CUB3D_EXEC" ]]; then
  echo -e "Error: cub3D binary not executable, run 'chmod +x $CUB3D_EXEC'\n"
  exit 1
fi

source scripts/.fx.sh
trap cleanup EXIT # comment if you want to keep logs for debug

make

echo -e "\n--- PARSING TESTS ---\n"

run_parsing_test_group "$VALIDS_MAPS" 0
run_parsing_test_group "$INVALIDS_MAPS" 1
analyze_results
