#include "ga.h"
int ga_free(GA ga)
{
    int flag;
    void *ga_win_ptr;

    MPI_Win_get_attr(ga->ga_win, MPI_WIN_BASE, &ga_win_ptr,
		     &flag);
    MPI_Win_free(&ga->ga_win);
    if (flag && ga_win_ptr)
        MPI_Free_mem(ga_win_ptr);
    MPE_Mutex_free(&ga->lock_win);

    free(ga);
    return 0;
}
