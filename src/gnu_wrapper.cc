// -*- C++ -*-

/**
 * @file   gnuwrapper.cpp
 * @brief  Replaces malloc family on GNU/Linux with custom versions.
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 * @note   Copyright (C) 2010 by Emery Berger, University of Massachusetts Amherst.
 */

#ifndef __GNUC__
#error "This file requires the GNU compiler."
#endif

#include <errno.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include <new>

#include "heaplayers.h"

/*
  To use this library,
  you only need to define the following allocation functions:

  - xxmalloc
  - xxfree
  - xxmalloc_usable_size
  - xxmalloc_lock
  - xxmalloc_unlock

  See the extern "C" block below for function prototypes and more
  details. YOU SHOULD NOT NEED TO MODIFY ANY OF THE CODE HERE TO
  SUPPORT ANY ALLOCATOR.


  LIMITATIONS:

  - This wrapper assumes that the underlying allocator will do "the
    right thing" when xxfree() is called with a pointer internal to an
    allocated object. Header-based allocators, for example, need not
    apply.

*/

#define WEAK(x) __attribute__((weak, alias(#x)))
#ifndef __THROW
#define __THROW
#endif

#ifndef CACHELINE_ALIGNED_FN
#define ATTRIBUTE_ALIGNED(s) __attribute__((aligned(s)))
#define CACHELINE_SIZE 64
#define CACHELINE_ALIGNED_FN ATTRIBUTE_ALIGNED(CACHELINE_SIZE)
#endif

#define CUSTOM_PREFIX(x) mesh_##x

#define WEAK_REDEF1(type, fname, arg1) MESH_EXPORT type fname(arg1) __THROW WEAK(mesh_##fname)
#define WEAK_REDEF2(type, fname, arg1, arg2) MESH_EXPORT type fname(arg1, arg2) __THROW WEAK(mesh_##fname)
#define WEAK_REDEF3(type, fname, arg1, arg2, arg3) MESH_EXPORT type fname(arg1, arg2, arg3) __THROW WEAK(mesh_##fname)

extern "C" {
WEAK_REDEF1(void *, malloc, size_t);
WEAK_REDEF1(void, free, void *);
WEAK_REDEF1(void, cfree, void *);
WEAK_REDEF2(void *, calloc, size_t, size_t);
WEAK_REDEF2(void *, realloc, void *, size_t);
WEAK_REDEF2(void *, memalign, size_t, size_t);
WEAK_REDEF3(int, posix_memalign, void **, size_t, size_t);
WEAK_REDEF2(void *, aligned_alloc, size_t, size_t);
WEAK_REDEF1(size_t, malloc_usable_size, void *);
}

#include "wrapper.cc"
#include "wrappers/gnuwrapper-hooks.cpp"
