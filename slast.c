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
}
