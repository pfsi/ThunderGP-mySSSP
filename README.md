## Changes to original
* Adds two new datasets (`arrow.txt` and `comb.txt`)
* Adds a `main()` to SSSP
* Adds `userData` field to `graphInfo`
* Changes SSSP `dataPrepareProperty`
  * Makes edge weights constant (1)
  * Changes `select_index` from random to user-defined, via `graphInfo.userData`
  * Sets first bit of source vertex property to 0 instead of 1
