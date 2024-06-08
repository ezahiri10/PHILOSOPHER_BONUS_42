#!/bin/bash

addresses=(
"0x7fab00405840 "
"0x7fab004058a0 "
"0x7fab004058e0 "
"0x7fb217405840 "
"0x7fb2174058a0 "
"0x7fb2174058e0 "
"0x7fee09c05840 "
"0x7fee09d04080 "
"0x7fee09e04080 "
)


for address in "${addresses[@]}"; do
  count=$(cat adrress_logs.py | grep "$address" | wc -l)

  if (( count % 2 == 1 )); then
    echo "Address with odd occurrence: $address"
  fi
done

# cat adrress_logs.py| grep alloca | sort | uniq | awk '{print $5}' | awk -F',' '{printf("\"%s\"\n", $1)}'