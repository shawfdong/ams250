#include <boost/mpi.hpp>
#include <iostream>
namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;
  int rank, size;

  rank = world.rank();
  size = world.size();
  std::cout << "Hello, world! I am process "
            << rank << " of " << size << endl;

  return 0;
}
