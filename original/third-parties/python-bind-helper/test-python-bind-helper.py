#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import test_python_bind_helper
import numpy as np

print(test_python_bind_helper.dummy1(np.float32(0.5), np.float32(0.5)))
print(test_python_bind_helper.dummy2(0.5, np.int32(5), np.float32(0.5), 0.5))
print(test_python_bind_helper.dummy3(0.5, np.int32(5), np.float32(0.5), 0.5))

