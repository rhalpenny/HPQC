# proof.c Analysis

## main()
- Initialise variables
- Initialise MPI environment
- Get number of processes (size)
- Get process rank
- Check arguments
- Check universe size
- Call check_task()
- Finalise MPI

## check_task()
- If rank == 0:
  - Acts as root
  - Receives values from all other processes
  - Sums them
- Else:
  - Acts as client
  - Performs calculation
  - Sends result to root

## Logic
The program distributes work across processes and collects results at the root node.

## Equivalent mathematical operation
Instead of MPI communication, the result could be computed using a direct formula:
- Sum of values across all processes
- Equivalent to a simple loop or closed-form sum

## Observation
MPI introduces communication overhead but allows parallel computation across nodes.
