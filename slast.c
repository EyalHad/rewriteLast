#include<stdio.h>
#include<fcntl.h>
#include<utmp.h>
#include<malloc.h>
#include<time.h>
<<<<<<< HEAD
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
=======
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

>>>>>>> 60d54ebaf43d259386bc4c34169a95dd1ccb0239

int main(int argc, char *argv[])
{ 
    if( argc != 2 ){
        printf("invalid argument: must run in this format:\n");
        printf("\"./slast n\"\n");
        printf("where n is integer\n");
        exit(1);
    }

<<<<<<< HEAD
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
=======
    int req_amount = atoi(argv[1]);
    
    int fd;
    struct utmp cr;
    size_t reclen = sizeof(struct utmp);

    fd = open(WTMP_FILE, O_RDONLY);
    if (fd == -1){
        perror("Couldn't open file:");
        exit(1);
    }

    int total_amount = 0;
    while (read(fd, &cr, reclen) == reclen)
    {
        if (cr.ut_type != 8 && cr.ut_type != 1){ total_amount++; }   
    }
    close (fd);

    struct utmp records[total_amount];

    fd = open(WTMP_FILE, O_RDONLY);
    if (fd == -1){
        perror("Couldn't open file:");
        exit(1);
    }

    int i = total_amount - 1;
    while (read(fd, &cr, reclen) == reclen)
    {
        if (cr.ut_type != 8 && cr.ut_type != 1){ records[i--] = cr; }
    }

    for (size_t i = 0; (i < req_amount && i < total_amount); i++)
    {

        records[i];
        long c;
        if ((records[i].ut_type) == 2){

            printf("%s\t ", records[i].ut_user); 
            printf("system boot \t ");
            printf("%s\t", records[i].ut_host);
            c = records[i].ut_tv.tv_sec;
            printf("%.20s\t", ctime(&c));     /* time */

            printf("\n");

        }else{

            printf("%s\t ", records[i].ut_user);      /* user */
            printf("%s\t\t", records[i].ut_line);
            printf(" %s\t\t\t", records[i].ut_host);  /* host */

            c = records[i].ut_tv.tv_sec;
            printf("%.20s\t", ctime(&c));     /* time */
  
            printf("\n");

        }

    }

        time_t tmp;
        tmp = records[total_amount-1].ut_tv.tv_sec;
        struct tm* time_struct = gmtime(&tmp);
        printf("\nwtmp begins ");
        printf("%.20s ", ctime(&tmp));
        printf("%d\n", time_struct->tm_year + 1900);
        
    close (fd);
    return 0;
>>>>>>> 60d54ebaf43d259386bc4c34169a95dd1ccb0239
}
