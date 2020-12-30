 #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>
    #include <time.h>

    //#define DIM 3
    
   int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);
        int DIM = atoi(argv[1]);
   
        int size, my_rank, os, rows, extrarows;
        MPI_Status status;
        double start;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        if(size > DIM)
        {
            printf("il numero di processi %d è maggiore della dimensione %d.\n",size, DIM);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
         
     
        // printf("[Sono il processo %d di %d]\n",my_rank,size);
     
        // Define my value
        int  my_A[DIM][DIM], my_B[DIM][DIM], my_C[DIM][DIM], i,j,nrows;
     
        if (my_rank == 0)
        {
            srand((unsigned int)time(NULL)); 
            for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                    my_A[i][j]=rand()%50;
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
                printf("%d,",B[i][j]);
                }
                printf("\n");
                }
            */
            os=0;
            nrows=DIM/size;
            extrarows=DIM%size;
            //invio agli altri
            MPI_Barrier(MPI_COMM_WORLD);
             start = MPI_Wtime();
            //rows=extrarows>0? nrows+1 : nrows;
            os=extrarows>0? nrows+1 : nrows;
            for(i=1;i<size;i++){
                rows= i<extrarows ? nrows+1 : nrows;
                MPI_Send(&os, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                MPI_Send(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                MPI_Send(&my_A[os][0], DIM*rows, MPI_INT, i, 1, MPI_COMM_WORLD);
                MPI_Send(&my_B, DIM*DIM, MPI_INT, i, 1, MPI_COMM_WORLD);
                os+=rows;
            }

            rows=extrarows>0? nrows+1 : nrows;
           // printf("%d: inviato \n", my_rank);
            
        }else{
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Recv(&os, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&my_A, DIM*rows, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&my_B, DIM*DIM, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            //printf("%d: ricevuto os:%d rows: %d\n", my_rank, os, rows);
        }
           
            
        for( int k=0; k<DIM; k++){
            for(i=0; i<rows;i++){
                my_C[i][k]=0;
                for(j=0; j<DIM; j++){
                    my_C[i][k]+=my_A[i][j]*my_B[j][k];
                }
            }
        }

        if(my_rank==0){
            for( i=1; i<size; i++){
                MPI_Recv(&os, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
                MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
                MPI_Recv(&my_C[os][0], DIM*rows, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            }

            MPI_Barrier(MPI_COMM_WORLD);
            double end= MPI_Wtime();
            /*
             for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                printf("\t%d",my_C[i][j]);
                }
                printf("\n");
                }
            */

            printf("DIM: %d, N: %d, Durata: %f secondi \n", DIM, size, end-start);
        }else{
             //printf("%d: calcolo completato \n", my_rank);
            MPI_Send(&os, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
            MPI_Send(&my_C, DIM*rows, MPI_INT, 0, 2, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
        }
        
     
        MPI_Finalize();
     
        return EXIT_SUCCESS;
    }