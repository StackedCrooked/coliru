#include <QtScript/QScriptEngine>
#include <QtCore/QCoreApplication>

#include <iostream>
#include <cassert>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QScriptEngine e;

    QScriptValue result = e.evaluate("pow(5.0, 2.0)")/*.toNumber()*/;

    assert(result.isValid());
    assert(result.isObject());
    assert(result.isError());
    assert("ReferenceError: Can't find variable: pow" == result.toString());
}
