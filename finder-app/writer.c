#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // Mở syslog với facility LOG_USER
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid arguments. Usage: %s <writefile> <writestr>", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr  = argv[2];

    // Mở file để ghi đè
    FILE *fp = fopen(writefile, "w");
    if (!fp) {
        syslog(LOG_ERR, "Could not open file %s for writing", writefile);
        closelog();
        return 1;
    }

    // Ghi nội dung vào file
    if (fputs(writestr, fp) == EOF) {
        syslog(LOG_ERR, "Failed to write to file %s", writefile);
        fclose(fp);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    fclose(fp);
    closelog();
    return 0;
}
