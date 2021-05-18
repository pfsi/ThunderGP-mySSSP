## Changes to original
* Adds two new datasets (`arrow.txt` and `comb.txt`)
* Adds a `main()` to SSSP
* Adds `userData` field to `graphInfo`
* Changes SSSP `dataPrepareProperty`
  * Makes edge weights constant (1)
  * Changes `select_index` from random to user-defined, via `graphInfo.userData`
  * Sets first bit of source vertex property to 0 instead of 1

## Description of datasets
* All edges are directed, left to right or up to down
* `n = 10000`
* `d0(i)` means "distance from vertex i to vertex 0"

#### Arrow

```
0 ┉┉ 1 ┉┉ 2 ┉┉ ... ┉┉ n-1

d0(i) = i
```

#### Comb
```
0 ┉┉ 2 ┉┉ 4 ┉┉ ... ┉┉ n-2
┋    ┋    ┋            ┋
1    3    5           n-1

d0(i) = i/2 if i is even, (i+1)/2 if i is odd
      = (i + i%2)/2
```
