/* -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/* Copyright 2017 University of Massachusetts, Amherst */

#ifndef MESH__MESH_H
#define MESH__MESH_H

#include <stddef.h>

#define MESH_VERSION_MAJOR 1
#define MESH_VERSION_MINOR 0

#ifdef __cplusplus
extern "C" {
#endif

// Same API as je_mallctl, allows a program to query stats and set
// allocator-related options.
int mesh_mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen);

// returns the usable size of an allocation
size_t mesh_usable_size(void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* MESH__MESH_H */