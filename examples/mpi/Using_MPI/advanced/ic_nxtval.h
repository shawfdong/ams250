#ifndef IC_NXTVAL_H_INCLUDED
#define IC_NXTVAL_H_INCLUDED
typedef enum { REQUEST, VALUE, GOAWAY } nxtval_msgtype;
int MPE_Counter_create_ic(MPI_Comm, MPI_Comm *,MPI_Comm *);
int MPE_Counter_free_ic(MPI_Comm *, MPI_Comm *);
int MPE_Counter_nxtval_ic(MPI_Comm, int *);
#define SERVER_RANK 0
#endif
