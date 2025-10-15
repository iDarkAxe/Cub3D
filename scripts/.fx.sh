#!/bin/bash

# Based on work from LeMuffinMan : https://github.com/LeMuffinMan
# Maps are from various sources, including: gueberso

cleanup() {
  echo -e "\nExiting, removing $CUB_LOG and $VALGRIND_LOG"
  rm -f $CUB_LOG $VALGRIND_LOG
}

run_parsing_test() {
  local file="$1"
  local expected_result="$2"
  local success=1
  local message=""

 valgrind --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --show-mismatched-frees=yes \
    --track-fds=yes \
    --log-file="$VALGRIND_LOG" \
    "$CUB3D_EXEC" "$file" 2> $CUB_LOG 1> /dev/null

  cub3d_exit_code=$?
  cub3d_stderr=$(< $CUB_LOG)
  valgrind_output=$(< $VALGRIND_LOG)

  if [[ $expected_result != $cub3d_exit_code ]]; then
    message+="Exit code = $cub3d_exit_code, expected = $expected_result"
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

analyze_results() {
  if [[ -z "$FAILED_TESTS" ]]; then
    echo -e "\nAll tests passed!\n"
    exit 0
  else
    echo -e "\n--- Failed tests ---\n"
    echo -e $FAILED_TESTS
  fi
}
