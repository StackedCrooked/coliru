try {
    some_throwing_func();
    return;
}
catch (...) {
    try {
        anotherThrowingFunc();
        return;
    }
    catch (...) {}
    throw;
}