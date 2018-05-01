#include "mpi.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE    256*1024
#define CMDSIZE    80
/* The maximum path len can be tricky to determine.  We use
   a default value that will work for this application. */
#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

void makehostlist(char *, const char *, int *);

int main(int argc, char *argv[])
{
    int      num_hosts, mystatus, allstatus, done, numread;
    int      infd, outfd;
    char     outfilename[MAXPATHLEN], controlmsg[CMDSIZE];
    char     buf[BUFSIZE];
    char     soft_limit[20];
    MPI_Info hostinfo;
    MPI_Comm pcpworkers, all_processes;

    MPI_Init(&argc, &argv);

    makehostlist(argv[1], "targets", &num_hosts);
    MPI_Info_create(&hostinfo);
    MPI_Info_set(hostinfo, "file", "targets");
    sprintf(soft_limit, "0:%d", num_hosts);
    MPI_Info_set(hostinfo, "soft", soft_limit);
    MPI_Comm_spawn("pcp-spawn-worker", MPI_ARGV_NULL, num_hosts,
                   hostinfo, 0, MPI_COMM_SELF, &pcpworkers,
		   MPI_ERRCODES_IGNORE);
    MPI_Info_free(&hostinfo);
    MPI_Intercomm_merge(pcpworkers, 0, &all_processes);
strcpy(outfilename, argv[3]);
if ((infd = open(argv[2], O_RDONLY)) == -1) {
  fprintf(stderr, "input %s does not exist\n", argv[2]);
  sprintf(controlmsg, "exit");
  MPI_Bcast(controlmsg, CMDSIZE, MPI_CHAR, 0, all_processes);
  MPI_Finalize();
  return -1 ;
} else {
  sprintf(controlmsg, "ready");
  MPI_Bcast(controlmsg, CMDSIZE, MPI_CHAR, 0, all_processes);
}
MPI_Bcast(outfilename, MAXPATHLEN, MPI_CHAR, 0,
          all_processes);
if ((outfd = open(outfilename, O_CREAT|O_WRONLY|O_TRUNC,
	S_IRWXU)) == -1)
  mystatus = -1;
else
  mystatus = 0;
MPI_Allreduce(&mystatus, &allstatus, 1, MPI_INT, MPI_MIN,
              all_processes);
if (allstatus == -1) {
  fprintf(stderr, "Output file %s could not be opened\n",
          outfilename);
  MPI_Finalize();
  return 1 ;
}
    /* at this point all files have been successfully opened */
    done = 0;
    while (!done) {
        numread = read(infd, buf, BUFSIZE);
	MPI_Bcast(&numread, 1, MPI_INT, 0, all_processes);
	if (numread > 0) {
	    MPI_Bcast(buf, numread, MPI_BYTE, 0, all_processes);
	    write(outfd, buf, numread);
	}
	else {
	    close(outfd);
	    done = 1;
	}
    }
    MPI_Comm_free(&pcpworkers);
    MPI_Comm_free(&all_processes);
    MPI_Finalize();
    return 0;
}

/* Create the host list from the named argument and return the number.
   Write the host list to the file fname.  The list is a comma-separated
   set of host names.
   The intent is that this could provide ways to indicate a range of names.
   For example: node37-node42 could be used to indicate node37,node38,node39,
   node40,node41,node42.
*/
void makehostlist(char *list, const char* fname, int *nfound)
{
    char *p;
    char tmpname[MAXPATHLEN];
    FILE *fp;
    fp = fopen(fname, "w");
    if (!fp) {
	fprintf(stderr,"Could not open file %s\n", fname);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    while (*list) {
	p = list;
	while (*p && *p != ',') {
	    tmpname[p-list] = *p;
	    p++;
	}
	tmpname[p-list] = 0;
	fprintf(fp,"%s\n",tmpname);
	p++;
	list = p;
    }
    fclose(fp);
}
