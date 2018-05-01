typedef enum { REQUEST, VALUE, GOAWAY } nxtval_msgtype;
void MPE_Counter_create( MPI_Comm, MPI_Comm *,MPI_Comm * );
int MPE_Counter_free( MPI_Comm *, MPI_Comm * );
int MPE_Counter_nxtval( MPI_Comm, int * );

