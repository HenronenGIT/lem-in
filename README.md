<!-- Lem-in gif or any banner picture -->
# Lem-in - "Elementary algorithmic project"

<img src="./README/pics/banner_gif.gif" alt="Banner Gif" height="400">

## Table of Contents

[Description](#description)

[Input](#input)

[Output](#output)

<!-- [How to run](##HowToRun) -->

[Algorithm](#algorithm)

[Resources](#resources)

[Tools](#tools)

[Keywords](#keywords)

<!-- <p align="left"><img src="./README/pics/score.jpg" height="150" /></p> -->
## Description

> Main idea behind project `Lem-in` is to find most efficient set of paths to move ***n*** amount of ants from `##start` room to the `##end` room. There are certain rules what we need to follow:

1. Ants are in the `##start` room when program starts.

2. Room can contain only one ant at the time. `##start` and `##end` room can contain unlimited amount of ants.

3. Each turn you can move every single ant ones.

<img src="./README/pics/rules_gif.gif" alt="example pic" >

## Input

> Best way to input ant farm of your choice is to create file and specify your map there.<br>
>Here is list of all the specifications what file can and cannot contain:

| Description | Command | Note |
| --- | --- | --- |
| First line of the file | `21` | First line is always the ant count |
| Specify start room | `##start` | **REQUIRED** |
| Specify end room | `##end` | **REQUIRED**  |
| Comment | `#` | All comments will be ignored  |
| Specify room | `start 0 1` | Room name cannot start with `L` or `#`. Also name cannot contain `-` character |
| Describe link between two rooms | `start-end` |  |
| Extra commands | `##anything` |  Extra commands will be ignored |

### Example map

<!-- ``` text
3
##start
start 4 0
##end
end 4 6
3 2 2
4 0 4
1 4 2
2 4 4
5 8 2
6 8 4
start-1
3-4
2-4
1-5
6-5
end-6
1-2
2-end
3-start
``` -->

File             |  Example map
:-------------------------:|:-------------------------:
![File Picture](./README/pics/file_pic.png)  |  ![Example Map](./README/pics/example_map.png)

<!-- <p align="left"><img src="./README/pics/example_map.png" height="300" /></p> -->

## How to run

test

## Resources

### Vertex disjoint paths

[Disjoint Paths](https://matthewdaws.github.io/blog/2015-06-08-Paths.html)

[Disjoint Paths; Implementation Issues](https://matthewdaws.github.io/blog/2015-06-15-Paths-Implementation.html)

### Edmonds–Karp

[Edmonds-Karp - YouTube](https://www.youtube.com/watch?v=RppuJYwlcI8&ab_channel=WilliamFiset)

[Edmonds-Karp algorithm - Wikipedia](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)

### Maximum flow problem

[Maximum flow problem - Wikipedia](https://en.wikipedia.org/wiki/Maximum_flow_problem)

## Tools

### Drawings

[Excalidraw](https://excalidraw.com/)

[Graph Editor](https://csacademy.com/app/graph_editor/)

### Keywords

- Algorithms
- Path finding
- Edmons-Karp
- Breadth-first search
- Max-flow min-cut theorem
