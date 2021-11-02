#include<stdio.h>
#include<fcntl.h>
#include<utmp.h>
#include<malloc.h>
#include<time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
  string *array;
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

int main(int argc, char *argv[])
{

  if (argc != 2 ){
    printf("This program takes a single parameter\n");
    exit(1);
  }
  int num_of_entries = atoi(argv[1]);
  int fd;
  struct utmp cr;
  size_t reclen = sizeof(struct utmp);

  fd = open(WTMP_FILE, O_RDONLY);
  if (fd == -1){
      perror("Couldn't open file");
      exit(1);
  }
  
  int iter = 0;
  while (read(fd, &cr, reclen) == reclen && iter < num_of_entries)
  {
      long c;
      switch (cr.ut_type)
      {
      case 1:
        // RUN_LVL, we need to skip this event
        break;
      case 8:
        // DEAD_PROCESS, we need to dkip this event
        break;
      case 2:
        // BOOT_TIME
        printf("%s\t ", cr.ut_user); /* user */
        printf("system boot \t ");
        printf("%s\t", cr.ut_host); /* 5.11.0-38 generic (address) */
        c = cr.ut_tv.tv_sec;
        printf("%.20s\t", ctime(&c));
        printf("\n");
        break;               
      default:
        // all other events
        printf("%s\t ", cr.ut_user); /* user */
        printf("%s\t\t", cr.ut_line);
        printf(" %s\t\t\t", cr.ut_host); /* 5.11.0-38 generic (address) */
        c = cr.ut_tv.tv_sec;
        printf("%.20s\t\n", ctime(&c));
      }
      ++iter;
  }
  

  close (fd);
  return 0;
}
