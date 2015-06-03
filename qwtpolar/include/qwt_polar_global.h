/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * QwtPolar Widget Library
 * Copyright (C) 2008   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/
#pragma once

#include <QtGlobal>

// QWT_POLAR_POLAR_VERSION is (major << 16) + (minor << 8) + patch.

#define QWT_POLAR_VERSION       0x010200
#define QWT_POLAR_VERSION_STR   "1.2.0"


// Copyright 2012 Keysight Technologies, Inc , Keysight Confidential
#pragma once

#if defined(_WIN32) // static is not supported; need to ensure runtime registration into singleton containers
#if defined(QWT_POLAR_MAKEDLL)
#define QWT_POLAR_EXPORT __declspec(dllexport)
#else
#define QWT_POLAR_EXPORT __declspec(dllimport)
#endif
#define QWT_POLAR_LOCAL  // to decrease chance of someone adding export
#define QWT_POLAR_MODULE // for the occasional case where you must export only on linux
#else
#if __GNUC__ >= 4
#define QWT_POLAR_EXPORT  __attribute__ ((visibility ("default")))
#define QWT_POLAR_MODULE  __attribute__ ((visibility ("default")))
#define QWT_POLAR_LOCAL   __attribute__ ((visibility ("hidden")))
#else
#define  QWT_POLAR_EXPORT
#define  QWT_POLAR_LOCAL
#define  QWT_POLAR_MODULE
#endif
#endif

// enable compilation toggle for yes/no exporting internal objects for tests.
// set it to on for production build.
#if !defined(QWT_POLAR_HIDE_GTEST_EXPORTS)
#define  QWT_POLAR_GTEST  QWT_POLAR_EXPORT
#else
#define  GRAPHS_GTEST  QWT_POLAR_LOCAL
#endif
