#include<stdio.h>
#include<fcntl.h>
#include<utmp.h>
#include<malloc.h>

// test
typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only after the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int main(int argv)
{
    int fd;
    struct utmp cr;
    size_t reclen = sizeof(struct utmp);

    char *to_print = (char *)malloc(reclen);
    fd = open(WTMP_FILE, O_RDONLY);
    if (fd == -1){
        perror("Couldn't open file:");
        exit(1);
    }
    
    while (read(fd, &cr, reclen) == reclen)
    {
        switch (cr.ut_type)
        {
        case 1:
        case 8:
            // printf("%d\n",cr.ut_type);

            break;
        case 2:
            // printf("%d\n",cr.ut_type);
            printf("%s\t ", cr.ut_user); /* user */
            printf("system boot \t ");
            printf("%s\t", cr.ut_host); /* 5.11.0-38 generic (address) */
            printf("%d\t",cr.ut_tv);
            printf("\n");


            break;
                                
        default:
            // printf("%d\n",cr.ut_type);
            printf("%s\t ", cr.ut_user); /* user */
            printf("%s\t\t", cr.ut_line);
            printf(" %s\t\t\t", cr.ut_host); /* 5.11.0-38 generic (address) */
            printf("%d\t ",cr.ut_tv);
            printf("\n");


        }
         
        
        char is_tilde = cr.ut_line[0];
        // if (is_tilde = '~'){
            // printf("system boot\t");
        // }else{
            // printf("%s\t", cr.ut_line); /* this is needed */ 
        // }

        // printf("%s\t", cr.ut_host); /* 5.11.0-38 generic (address) */

        // printf("%d\t",cr.ut_tv);
        // printf("%s\t", cr.ut_id); /* currently ~~~ */
        // printf("\n");
    }
    

    close (fd);
    return 0;
}
