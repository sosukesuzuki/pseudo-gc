# pseudo-gc

pseudo-gc is an implementation of a pseudo-garbage collection system written in C++. This project is for practicing and experimenting with my GC implementation. The architecture and implementation of this project will continue to evolve.

## Architecture

### Cell

In this project, each allocated object is referred to as a cell. A cell contains a mark bit, a reference count, and pointers to other cells.

### Allocator

A bump allocator is implemented to allocate cells.

### Pseudo Mutator

It generates 1024 cells, designates some of them as roots, and then creates random object trees starting from the roots. After that, it traverses from the roots and randomly cuts references.

### Pseudo Collector

Although called "pseudo," this is essentially a standard mark-and-sweep collector.
