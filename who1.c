#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST

int main() {
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
    perror( UTMP_FILE );
    exit(1);
    }
    
    while(read(utmpfd, &current_record, reclen) == reclen){
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

show_info(struct utmp *utbufp){
    struct tm ts;
    char buf[80];
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    ts = *localtime(utbufp->ut_time);
    strftime(buf, sizeof(buf), "%b %e %H:%M", &ts);
    printf("%s", buf);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
    
}