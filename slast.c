#include<stdio.h>
#include<fcntl.h>
#include<utmp.h>
#include<malloc.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char *argv[])
{ 
    if( argc != 2 ){
        printf("invalid argument: must run in this format:\n");
        printf("\"./slast n\"\n");
        printf("where n is integer\n");
        exit(1);
    }

    int req_amount = atoi(argv[1]);
    
    int fd;
    struct utmp cr;
    size_t reclen = sizeof(struct utmp);

    fd = open(WTMP_FILE, O_RDONLY);
    if (fd == -1){
        perror("Couldn't open file:");
        exit(1);
    }

    char* records;
    records = (char*)malloc(reclen);
    if (!records){
        printf("failed to alloocate memory.\n");
        exit(1);
    }
    
    
    while (read(fd, &cr, reclen) == reclen)
    {

        long c;

        switch (cr.ut_type)
        {
        case 1:
        case 8:
            break;
        case 2:

            printf("%s\t ", cr.ut_user);      /* user */
            printf("system boot \t ");
            printf("%s\t", cr.ut_host);       /* (address) */

            c = cr.ut_tv.tv_sec;
            printf("%.20s\t", ctime(&c));     /* time */

            printf("\n");

            break;
                                
        default:

            printf("%s\t ", cr.ut_user);      /* user */
            printf("%s\t\t", cr.ut_line);
            printf(" %s\t\t\t", cr.ut_host);  /* (address) */

            c = cr.ut_tv.tv_sec;
            printf("%.20s\t", ctime(&c));     /* time */
  
            printf("\n");

        }
    }
    

    close (fd);
    return 0;
}
