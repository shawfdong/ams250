  void MPE_Counter_service(MPI_Comm comm)
  {
     static int counter = 0;
     int        requester, flag;
     MPI_Status status;
     /* Process all pending messages */
     do {
        MPI_Iprobe(MPI_ANY_SOURCE, COUNTER, comm, &flag, &status);
        if (flag) {
           requester = status.MPI_SOURCE;
           MPI_Recv(MPI_BOTTOM, 0, MPI_INT, requester, COUNTER,
                    comm, MPI_STATUS_IGNORE);
           counter++;
           MPI_Send(&counter, 1, MPI_INT, requester,
                    COUNTER, comm);
    	 }
     } while (flag);
   }
