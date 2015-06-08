#ifndef GET_CPU_TIME
#define GET_CPU_TIME

// http://nadeausoftware.com/articles/2012/03/c_c_tip_how_measure_cpu_time_benchmarking
/**
 * Returns the amount of CPU time used by the current process,
 * in seconds, or -1.0 if an error occurred.
 */
double getCPUTime();

#endif // GET_CPU_TIME