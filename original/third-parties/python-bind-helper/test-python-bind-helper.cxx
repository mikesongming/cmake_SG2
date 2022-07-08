/* Implementation of python-bind-helper.
   Copyright (C) 2019-2020 MINES ParisTech
   This file is part of the python-bind-helper library.

   The test_python_bind_helper library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3.0 of the License, or (at your option) any later version.

   The test_python_bind_helper library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the test_python_bind_helper library; if not, see
   <http://www.gnu.org/licenses/>.

   Authors:
     Benoit Gschwind <benoit.gschwind@mines-paristech.fr>

*/

#include "python-bind-helper.hxx"

using namespace python_bind_helper;

static float dummy1(float, float)
{
	return 1.0f;
}

static int dummy2(double, int, float, double)
{
	return 0;
}

static std::tuple<int,double,float> dummy3(double, int, float, double)
{
	return std::make_tuple(1, 1.0, 0.0f);
}

static PyMethodDef methods[] =
{
	{NULL, NULL, 0, NULL}
};

struct module_state {
	PyObject * Error;
};

static int test_python_bind_helper_traverse(PyObject *m, visitproc visit, void *arg) {
	Py_VISIT(reinterpret_cast<module_state*>(PyModule_GetState(m))->Error);
	return 0;
}

static int test_python_bind_helper_clear(PyObject *m) {
	Py_CLEAR(reinterpret_cast<module_state*>(PyModule_GetState(m))->Error);
	return 0;
}


static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"test_python_bind_helper",
	NULL,
	sizeof(module_state),
	methods,
	NULL,
	test_python_bind_helper_traverse,
	test_python_bind_helper_clear,
	NULL
};

PyMODINIT_FUNC
PyInit_test_python_bind_helper(void)
{

	PyObject * m = PyModule_Create(&moduledef);
	if (m == NULL)
		return NULL;

	/** init numpy **/
	import_array();
	import_umath();

	module_state * state = reinterpret_cast<module_state*>(PyModule_GetState(m));
	state->Error = PyErr_NewException("test_python_bind_helper.error", NULL, NULL);
	Py_INCREF(state->Error);
	PyModule_AddObject(m, "error", state->Error);

#define register_ufunc(name) \
static build_ufunc<decltype(name), name> ufunc_##name(#name); \
ufunc_##name.register_to(m);

	register_ufunc(dummy1)
	register_ufunc(dummy2)
	register_ufunc(dummy3)

	return m;

}

