#ifndef _PYSCRIPT_OBJECT_H_
#define _PYSCRIPT_OBJECT_H_ 
#include <Python.h>
#include <glib.h>

typedef struct {
    PyObject_HEAD
    PyObject *module; /* module object */ 
    PyObject *argv;  /* list of argument strings from the load command */
    PyObject *modules; /* dict of imported modules for script */
    GSList *signals; /* list of bound signals and commands */
    GSList *registered_signals; /* list of signal names registered */
} PyScript;

extern PyTypeObject PyScriptType;

int pyscript_init(void);
PyObject *pyscript_new(PyObject *module, char **argv);
void pyscript_remove_signals(PyObject *script);
void pyscript_clear_modules(PyObject *script);
#define pyscript_check(op) PyObject_TypeCheck(op, &PyScriptType)
#define pyscript_get_name(scr) PyModule_GetName(((PyScript*)scr)->module)
#define pyscript_get_filename(scr) PyModule_GetFilename(((PyScript*)scr)->module)
#define pyscript_get_module(scr) ((PyScript*)scr)->module

#endif