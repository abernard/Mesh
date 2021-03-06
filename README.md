Mesh: A compacting malloc(3) implementation
===========================================

Mesh is a drop in replacement for
[malloc(3)](http://man7.org/linux/man-pages/man3/malloc.3.html) that compacts the heap of C and C++ programs without rewriting application pointers.

Implementation Overview
-----------------------

Mesh is built on [Heap Layers](http://heaplayers.org/), an
infrastructure for building high performance memory allocators in C++
(see
[paper](https://people.cs.umass.edu/~emery/pubs/berger-pldi2001.pdf)
for details.

The entry point of the library is [`libmesh.cc`](src/libmesh.cc).
This file is where `malloc`, `free` and the instantiations of the
Heap used for allocating program memory lives.


DEFINITIONS
-----------

- **Page**: The smallest block of memory managed by the operating
  system, 4Kb on most architectures.  Memory given to the allocator by
  the operating system is always in multiples of the page size, and
  aligned to the page size.
- **Span**: The size of memory managed by Mesh -- [currently 128
  Kb](src/include/miniheap.h#L36).
  It is larger than the page size to amortize the cost of heap
  metadata.
- [**MiniHeap**](src/include/miniheap.h): A bitmap, metadata and associated Span for a
  particular size of objects (size class).
- [**MeshingHeap**](src/include/meshingheap.h): A collection of miniheaps for a particular size
  class, including a _current_ MiniHeap that we are allocating out of.

BUILDING
--------

```
$ git submodule update --init; ./configure; make
```
