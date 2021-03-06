// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright 2017 University of Massachusetts, Amherst

#include <pthread.h>
#include <signal.h>

#ifdef __linux__
#include <sys/epoll.h>
#endif

#pragma once
#ifndef MESH__REAL_H
#define MESH__REAL_H

#define DECLARE_REAL(name) extern decltype(::name) *name

namespace mesh {
namespace real {
void init();

#ifdef __linux__
DECLARE_REAL(epoll_pwait);
DECLARE_REAL(epoll_wait);
#endif

DECLARE_REAL(pthread_create);

DECLARE_REAL(sigaction);
DECLARE_REAL(sigprocmask);
}  // namespace real
}  // namespace mesh

#endif  // MESH__REAL_H
