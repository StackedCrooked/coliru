#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwhatever"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwhatever"
#endif // jesus
// some code here
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // jesus