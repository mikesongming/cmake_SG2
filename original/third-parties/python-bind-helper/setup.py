#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension
from collections import defaultdict
import numpy

params = defaultdict(list)
params['extra_compile_args'] = ['-std=c++11']
params["include_dirs"] += [numpy.get_include()]


module = Extension('test_python_bind_helper',
    sources = ['test-python-bind-helper.cxx'],
    **params)

setup(name = 'test_python_bind_helper',
      version = '1.0',
      description = 'Dummy module to test python bind helper',
      ext_modules = [module])

