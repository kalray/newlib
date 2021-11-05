/* This file has been modified or added by Kalray, SA. 2010 */

#include <sys/types.h>
#include <sys/stat.h>
#include "errno.h"


/***************************************************************
 *	stat
 ***************************************************************/
int sc_stat(const char *filename, int *);

int _stat(const char *filename, struct stat *st)
{
    int ret;
    int res[13];

    ret = sc_stat(filename, res);

    if( ret < 0 ) {
      errno = ret * -1;
      ret = -1;
    } else {
	st->st_dev = res[0];
	st->st_ino = res[1];
	st->st_mode = res[2];
	st->st_nlink = res[3];
	st->st_uid = res[4];
	st->st_gid = res[5];
	st->st_rdev = res[6];
	st->st_size = res[7];
	st->st_blksize = res[8];
	st->st_blocks = res[9];
	st->st_atime = res[10];
	st->st_mtime = res[11];
	st->st_ctime = res[12];
    }

    return ret;
}

int stat(const char *filename, struct stat *st) __attribute__ ((weak, alias ("_stat")));
