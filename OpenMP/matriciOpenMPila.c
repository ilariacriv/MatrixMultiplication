 #include <stdio.h>
    #include <stdlib.h>
    #include <omp.h>
    #include <time.h>

    //#define DIM 3
    
   int main(int argc, char* argv[])
    {   
   
        int size, my_rank;
        size=atoi(argv[1]);
        int DIM = atoi(argv[2]);

        if(size > DIM)
        {
            printf("il numero di processi %d è maggiore della dimensione %d.\n",size, DIM);
            exit(1);
        }

        
        
     
       // printf("[Sono il processo %d di %d]\n",my_rank,size);
     
        // Define my value
        int  A[DIM][DIM], B[DIM][DIM], C[DIM][DIM], i,j,k;
     
            srand((unsigned int)time(NULL)); 
            for(i=0;i<DIM;i++){
                for(j=0; j<DIM; j++){
                    A[i][j]=rand()%50;
                    B[i][j]=rand()%50;
                }
            }
            // verifica
        /*    printf("[processo %d] matrice A:\n", my_rank);
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
                }*/
            double start = omp_get_wtime();

        # pragma omp parallel num_threads(size) shared(A,B,C,size) private(i,j,k,my_rank) 
        {
            my_rank= omp_get_thread_num();
           // printf("[processo %d] inizio calcolo\n", my_rank);
            #pragma omp for schedule(dynamic,2)
                for(k=0; k<DIM; k++){
                for(i=0; i<DIM; i++){
                    C[i][k]=0;
                    for(j=0; j<DIM; j++){
                        C[i][k]+=A[i][j]*B[j][k];
                    }
                }
            }
            
            
        }

        double end= omp_get_wtime();
/*
        for(i=0;i<DIM;i++){
            for(j=0; j<DIM; j++){
            printf("%d,",C[i][j]);
            }
            printf("\n");
        }
*/
         printf("DIM: %d, N: %d, Durata: %f secondi \n", DIM, size, end-start);
        
     
        return EXIT_SUCCESS;
    }