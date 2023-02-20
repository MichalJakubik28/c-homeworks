#ifndef EXITUS_H
#define EXITUS_H

int exitus_count_args(const char **argv);
int exitus(int (*m)(int, const char**), int argc, const char **argv);

#endif // EXITUS_H
