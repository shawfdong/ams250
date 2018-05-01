/* We will see later how to remove the global variable reqs */
static MPI_Request *reqs;
void MPE_Counter_service(MPI_Comm comm)
{
    static int counter = 0;
    int requester, outcount, size, i;
    MPI_Status *statuses;
    int        *indices;

    MPI_Comm_size(comm, &size);
    /* Allocate space for arrays */
    statuses = (MPI_Status *)malloc(size * sizeof(MPI_Status));
    indices  = (int *)malloc(size * sizeof(int));
    /* Process all pending messages FAIRLY */
    do {
        MPI_Testsome(size, reqs, &outcount, indices, statuses);
        if (outcount) {
            for (i=0; i<outcount; i++) {
                requester = statuses[i].MPI_SOURCE;
            counter++;
            MPI_Send(&counter, 1, MPI_INT, requester,
                     COUNTER, comm);
            /* Repost the nonblocking receive */
            MPI_Irecv(MPI_BOTTOM, 0, MPI_INT, requester,
                      COUNTER, comm, &reqs[indices[i]]);
            }
        }
    } while (outcount);
    free(statuses); free(indices);
}

void MPE_Counter_service_setup(MPI_Comm comm)
{
    int i, size;
    MPI_Comm_size(comm, &size);
    for (i=0; i<size; i++) {
        MPI_Irecv(MPI_BOTTOM, 0, MPI_INT, i, COUNTER, comm,
                  &reqs[i]);
    }
}
