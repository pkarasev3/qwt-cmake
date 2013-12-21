/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/
#pragma once


#include <qglobal.h>

// QWT_VERSION is (major << 16) + (minor << 8) + patch.

#define QWT_VERSION       0x060101
#define QWT_VERSION_STR   "6.1.1"

#if defined(_MSC_VER) /* MSVC Compiler */
/* template-class specialization 'identifier' is already instantiated */
#pragma warning(disable: 4660)
/* inherits via dominance */
#pragma warning(disable: 4250)
#endif // _MSC_VER


// Copyright 2012 Agilent Technologies, Inc , Agilent Confidential
#pragma once

#if defined(_WIN32) // static is not supported; need to ensure runtime registration into singleton containers
    #if defined(QWT_MAKEDLL)
            #define QWT_EXPORT __declspec(dllexport)
    #else
            #define QWT_EXPORT __declspec(dllimport)
    #endif
    #define QWT_LOCAL  // to decrease chance of someone adding export
    #define QWT_MODULE // for the occasional case where you must export only on linux
#else
    #if __GNUC__ >= 4
      #define QWT_EXPORT  __attribute__ ((visibility ("default")))
      #define QWT_MODULE  __attribute__ ((visibility ("default")))
      #define QWT_LOCAL   __attribute__ ((visibility ("hidden")))
    #else
      #define  QWT_EXPORT
      #define  QWT_LOCAL
      #define  QWT_MODULE
    #endif
#endif

// enable compilation toggle for yes/no exporting internal objects for tests.
// set it to on for production build.
#if !defined(QWT_HIDE_GTEST_EXPORTS)
    #define  QWT_GTEST  QWT_EXPORT
#else
    #define  GRAPHS_GTEST  QWT_LOCAL
#endif

