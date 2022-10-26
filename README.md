# Lem-in - "Pathfinding Algorithm"

<img src="./README/pics/banner_gif.gif" alt="Banner Gif" width="40%">

## Table of Contents

[Description](#description)

[Input](#input)

[Output](#output)

[How to use](##howtouse)

[Algorithms](#algorithms)

[Resources](#resources)

[Tools](#tools)

[Keywords](#keywords)

## Description

The main idea behind project `Lem-in` is to find the most efficient set of paths to move **_n_** amount of ants from the `##start` room to the `##end` room. There are certain rules that we need to follow:

1. When the program starts, all of the ants are in the `##start` room.

2. Room can contain only one ant at a time. `##start` and `##end` rooms can contain an unlimited amount of ants.

3. With Each turn you can move every single ant one time.

<img src="./README/pics/rules_gif.gif" alt="example gif" width="60%" >

## Input

Best way to input an ant farm of your choice is to create a file and specify your map there.\
Here is a list of all the specifications that the file can and cannot contain:

| Description                         | Command      | Note                                                                                |
| ----------------------------------- | ------------ | ----------------------------------------------------------------------------------- |
| First line of the file              | `21`         | The first line is always the ant count                                              |
| Specify start room                  | `##start`    | **REQUIRED**                                                                        |
| Specify end room                    | `##end`      | **REQUIRED**                                                                        |
| Comment                             | `#`          | Program will ignore all the commands                                                |
| Specify room                        | `start 0 1`  | Room name cannot start with `L` or `#`. Also, a name cannot contain a `-` character |
| Describe the link between two rooms | `start-end`  |                                                                                     |
| Extra commands                      | `##anything` | Extra commands will be ignored                                                      |

|                  Ant farm                   |               Map visualization               |
| :-----------------------------------------: | :-------------------------------------------: |
| ![File Picture](./README/pics/file_pic.png) | ![Example Map](./README/pics/example_map.png) |

## Output

Output format of the program is the following:\
`Lx-y Lz-w Lr-o`\
x, z, and r represents ant number (going from 1 to number_of_ants).\
y, w, and o represents room names.\
One line == One turn \
When we use the map shoved above, the output is the following:\
`L1-1 L2-3`\
`L1-5 L2-4 L3-1 L4-3`\
`L1-6 L2-2 L3-5 L4-4`\
`L1-end L2-end L3-6 L4-2`\
`L3-end L4-end`

<img src="README/pics/output_gif.gif" width="60%">

**NOTE!**\
If you are wondering what happens between room 1 and room 2, all of this will be explained in [Algorithms](#algorithms) section.

### Compiling

At the root of the repository there is a `Makefile`, simply running `make` will compile the whole program - the name of the program will be `lem-in`.

### Running `lem-in`

`lem-in < name_of_the_map`

### Running with flags

#### `-l` Flag

Running `lem-in` with the flag `-l` will show how many turns it took to move all ants from `##start` to `##end`.

`lem-in -l < name_of_the_map`

```text
./lem-in -l < eval_tests/test_maps/example_3.map
L1-1 L2-3
L1-5 L2-4 L3-1 L4-3
L1-6 L2-2 L3-5 L4-4
L1-end L2-end L3-6 L4-2
L3-end L4-end
Move count:
5
```

#### `-p` Flag

Running `lem-in` with the flag `-p` will show a set of paths used to move ants from `##start` to `##end`.

`lem-in -p < name_of_the_map`

```text
./lem-in -p < eval_tests/test_maps/example_3.map
Our Algo chose paths:
PATH [1] = start -> 1 -> 5 -> 6 -> end length = 3
PATH [2] = start -> 3 -> 4 -> 2 -> end length = 3
```

## Algorithms

Many different Algorithms were used so we can find:

1. Shortest paths
2. Vertex disjoint paths
3. Most efficient set of paths for ***n*** amount of ants

### Breadth-first search

With the help of Breadth-first search algorithm (shortened to bfs), we can find ALWAYS most shortest path from `##start` to `##end`.

Here is an example:

<img src="README/pics/bfs_gif.gif" width="80%">

What we can see from this GIF is that a Breadth-first search can find the shortest path efficiently.

<details>
<summary>Code snippet from the source code </summary>

```c
static int	bfs(t_data *data, t_queue **head)
{
	t_queue	*que;
	t_queue	*tail;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	while (data->end->parent == NULL && que != NULL)
	{
		iterate_links(&tail, que);
		que = que->next;
	}
	if (!data->end->parent)
		return (0);
	set_flows(data);
	return (1);
}
```
</details>

### Matthew Daws Vertex Disjoint

Finding the [Vertex Disjoint](https://www.youtube.com/watch?v=kwWN4FIEyz8&ab_channel=WrathofMath) paths is key thing in whole project. Thank you [Matthew Daws](https://matthewdaws.github.io/blog/index.html)!\
In this GIF we can see something interesting happening between room `1` and room `2`.

<img src="README/pics/output_gif.gif" width="60%">

When our second BFS finds a room, what already belongs to a path - rule goes as follow:
> "If we can get to a vertex v which is used by a path, but the predecessor was not in a path, then we must now follow the path backwards."\
> Matthew Daws

After that one step backwards, we are free to go everywhere.

When BFS has made its way to the end room, we start to backtrack from the end room to the start room. During our backtrack, if a link between 2 rooms has already flow from our previous BFS, we need to cut that flow.\
You can see this happening in above GIF.

<details>
<summary>Code snippet from the source code.</summary>

```c
/*
	We have four different cases when we check that can we step to link.
		1. From current room to link, there is positive flow.
		2. Room where we are at the moment, it was first step to old path.
		3. Room where wea re at the moment, it is second step to old path.
		4. From current room to link, there is not any flow.
*/
void	iterate_links(t_queue **tail, t_queue *que)
{
	size_t	i;
	t_room	**link_array;

	link_array = (t_room **)que->room->links_vec->array;
	i = 0;
	while (i < que->room->links_vec->space_taken)
	{
		if (positive_flow(que->room->flow, link_array[i]))
		{
			i++;
			continue ;
		}
		else if (que->room->flow_from && !que->room->flow_parent)
		{
			found_old_path(tail, que);
			return ;
		}
		else if (que->room->flow_from && que->room->flow_parent)
			can_go_everywhere(que->room, link_array[i], tail);
		else if (link_array[i]->parent == NULL
			&& link_array[i]->parent != que->room)
			visit_using_unused_edge(tail, que, link_array[i]);
		i++;
	}
}
```

</details>

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
- Pathfinding
- Edmons-Karp
- Breadth-first search
- Max-flow min-cut theorem
