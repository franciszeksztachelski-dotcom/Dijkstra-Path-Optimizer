# Dijkstra-Path-Optimizer
A low-level C++ implementation of Dijkstra's algorithm designed to solve shortest-path problems in graphs with asymmetric edge weights and periodic time-constraints. It features a custom-built binary heap and manual memory management, operating entirely without the Standard Template Library (STL).


This project is a high-performance pathfinding engine that
calculates the most efficient route through a coordinate-based
graph. Unlike standard Dijkstra implementations, this engine
handles asymmetric edge costs and time-dependent periodic edges.

The core of this project is a modified Dijkstra’s algorithm
designed to handle dynamic weights:Asymmetric Potential Costs:
Movement between nodes is calculated based on "potential"
(elevation). Moving from a node with potential B to potential
A costs (A - B + 1) units if A > B, and a constant 1
unit if A <= B.Time-Dependent Scheduled Edges: The graph
contains special "fast-travel" edges that only activate at
specific time intervals. The algorithm calculates the "waiting
time" at a node based on the modulo of the current elapsed time
and the edge's frequency, making the shortest path calculation
dynamic.

This was built as a deep dive into manual data structure
implementation. To ensure maximum control and performance, I
stripped away the C++ Standard Template Library:Custom Binary
Heap: The Priority Queue required for Dijkstra was built from
scratch. It uses a binary heap with siftUp and siftDown
operations to maintain O(log n) efficiency for extracting the
minimum distance node.Manual Memory Management: To avoid the
overhead of std::vector or std::list, all buffers (distance
maps, visited arrays, and the graph itself) are managed using
dynamic 2D arrays and raw pointers.Memory Efficiency: The
engine is optimized to handle large grids with thousands of
nodes, ensuring that calculations stay within the int range
while keeping the memory footprint minimal.

HOW TO RUN

g++ main.cpp -o path_optimizer

./path_optimizer