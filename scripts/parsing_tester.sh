#!/bin/bash

# Based on work from LeMuffinMan : https://github.com/LeMuffinMan
# Maps are from various sources, including: gueberso

VALIDS_MAPS="scripts/maps/valid_maps/"
INVALIDS_MAPS="scripts/maps/invalid_maps/"

CUB3D_EXEC="./cub3D"
FAILED_TESTS=""

if [[ ! -f "$CUB3D_EXEC" ]]; then
  echo -e "Error: cub3D binary not found at $CUB3D_EXEC\n"
  exit 1
fi

if [[ ! -x "$CUB3D_EXEC" ]]; then
  echo -e "Error: cub3D binary not executable, run 'chmod +x $CUB3D_EXEC'\n"
  exit 1
fi

run_parsing_test() {
  local file="$1"
  local expected_result="$2"
  local success=1
  local message=""

  cub3d_stderr=$("$CUB3D_EXEC" "$file" 2>&1 >/dev/null)
  cub3d_exit_code=$?
  
  valgrind_output=$(valgrind --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --show-mismatched-frees=yes \
    --track-fds=yes \
    --error-exitcode=42 \
    "$CUB3D_EXEC" "$file" 2>&1 >/dev/null)

  if [[ $expected_result == 0 && $cub3d_exit_code != 0 ]]; then
    message+="Exit code=$cub3d_exit_code "
    success=0
  elif [[ $expected_result != 0 && $cub3d_exit_code == 0 ]]; then
    message+="Exit code = $cub3d_exit_code (Should have failed) "
    success=0
  fi

  if [[ $expected_result != 0 && ! "$cub3d_stderr" == *"Error"* ]]; then
    message+="No 'Error' in stderr "
    success=0
  fi

  if [[ $(echo "$valgrind_output" | grep -q "All heap blocks were freed -- no leaks are possible"; echo $?) != 0 || 
        $(echo "$valgrind_output" | grep -q "ERROR SUMMARY: 0 errors"; echo $?) != 0 ]]; then
    message+="Valgrind errors "
    success=0
  fi

  if [[ $success == 1 ]]; then
    echo -e "\033[0;32mOK\033[0m"
  else
    echo -e "\033[0;31mKO - $message\033[0m"
    FAILED_TESTS+="$file : \033[0;31m$message\033[0m\n"
  fi
}

run_parsing_test_group() {
  local dir="$1"
  local expected_result="$2"

  for file in "$dir"*; do
    echo -n "$file : "
    run_parsing_test "$file" "$expected_result"
  done
}

make

echo -e "\n--- PARSING TESTS ---\n"

run_parsing_test_group "$VALIDS_MAPS" 0
run_parsing_test_group "$INVALIDS_MAPS" 1

if [[ -z "$FAILED_TESTS" ]]; then
  echo -e "\nAll tests passed!\n"
  exit 0
else
  echo -e "\n--- Failed tests ---\n"
  echo -e $FAILED_TESTS
fi
