 #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>
    #include <time.h>

    //#define DIM 3
    
   int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);
        int DIM = atoi(argv[1]);
   
        int size, my_rank, os, rows;
        double start,end;
        MPI_Status status;
        
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        if(size > DIM)
        {
            printf("il numero di processi %d è maggiore della dimensione %d.\n",size, DIM);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        if(DIM % size!=0)
        {
            printf("il numero di processi %d non è divisore della dimensione %d.\n",size, DIM);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        rows=DIM/size;
     
       // printf("[Sono il processo %d di %d]\n",my_rank,size);
     
        // Define my value
        int  my_A[DIM][DIM], my_B[DIM][DIM], my_C[DIM][DIM], i,j,nrows;
     
        if (my_rank == 0)
        {
            int A[DIM][DIM], i,j ;
            srand((unsigned int)time(NULL)); 
            for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                    A[i][j]=rand()%50;
                    my_B[i][j]=rand()%50;
                }
            }
            // verifica
            /*
            printf("[processo %d] matrice A:\n", my_rank);
            for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                printf("%d,",A[i][j]);
                }
                printf("\n");
                }
            printf("[processo %d] matrice B:\n", my_rank);
            for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                printf("%d,",my_B[i][j]);
                }
                printf("\n");
                }
            */

            //invio agli altri
           MPI_Barrier(MPI_COMM_WORLD);
           start = MPI_Wtime();

            MPI_Scatter(A, DIM*DIM/size , MPI_INT, &my_A,  DIM*DIM/size, MPI_INT, 0, MPI_COMM_WORLD);
            // printf("%d: inviato \n", my_rank);
        }else{
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Scatter(NULL, DIM*DIM/size , MPI_INT, &my_A,  DIM*DIM/size, MPI_INT, 0, MPI_COMM_WORLD);
            
        }
        MPI_Bcast(my_B, DIM*DIM, MPI_INT, 0, MPI_COMM_WORLD);
         
       
        for( int k=0; k<DIM; k++){
            for(i=0; i<rows;i++){
                my_C[i][k]=0;
                for(j=0; j<DIM; j++){
                    my_C[i][k]+=my_A[i][j]*my_B[j][k];
                }
            }
        }
      
       
       if(my_rank==0){
            int  C[DIM][DIM];
            MPI_Gather(&my_C, DIM*DIM/size, MPI_INT, C, DIM*DIM/size, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            end= MPI_Wtime();
            /*
             for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                printf("%d,",C[i][j]);
                }
                printf("\n");
                }
            */
            

            printf("DIM: %d, N: %d, Durata: %f secondi \n", DIM, size, end-start);

       }else{
           MPI_Gather(&my_C, DIM*DIM/size, MPI_INT, NULL, 1, MPI_INT, 0, MPI_COMM_WORLD);
           MPI_Barrier(MPI_COMM_WORLD);
       }
        
     
        MPI_Finalize();
     
        return EXIT_SUCCESS;
    }