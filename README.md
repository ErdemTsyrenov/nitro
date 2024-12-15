# Build steps
After clonning repo, do following steps:
```
cd NitroCppTest-Erdem
cmake -B build
cmake --build build --config Debug
```
Executable `main` is located in `build` folder.

In order to run unit tests run following command after build:
```
cd build
ctest --verbose -C Debug
``` 

# Run steps
```
cd build
./main <path to json file>
```
Output:
```
Intersections:
Between 1 3 4 at (160,160), w=190, h=20, 
Between 1 3 at (140,160), w=210, h=20, 
Between 1 4 at (160,140), w=190, h=40, 
Between 2 3 4 at (160,200), w=210, h=60, 
Between 2 3 at (140,200), w=230, h=60, 
Between 2 4 at (160,200), w=210, h=130, 
Between 3 4 at (160,160), w=230, h=100,
```

# Solution
## Implementation
To find intersections between rectangles, I use simple brute force algorithm. First, programs finds all subsets of rectangles and then calculates intersection between rectangles of this subset. Since spec gurantees that maximum number of rectangles is 10, iterating over all subsets is relatively fast (we only need 2^10=1024 iterations). Whole algorithm can be described in following steps:
1) Parse json (I used following json parser https://github.com/nlohmann/json)
2) Find all subsets of rectangles
3) Iterate over all subsets and calculate itersections
4) Print result

## Testing
To verify implementation, I used unit and integration tests. For both of them I don't use any third-party tools because of lack of time as it is faster to write simple tests using built-in asserts than integrating testing framework. If I had more time, I would use Google Tests for unittests and LLVM lit (https://llvm.org/docs/CommandGuide/lit.html) for integration tests.  