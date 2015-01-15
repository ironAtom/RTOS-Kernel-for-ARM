/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 * @date   2014-11-24
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>

#define EOT_CHAR 0x04
#define DEL_CHAR 0x7f


/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), char *buf __attribute__((unused)), size_t count __attribute__((unused)))
{
    char tempCh;
    unsigned length = 0;
    unsigned start = (unsigned int)buf;
    unsigned end = (unsigned int)(buf+count);
    
    //file descriptor is not stdin
    if (fd != STDIN_FILENO)
        return -EBADF;
    
    //memory range not exceeds SDRAM
    if (start >= 0xa0000000 && end <= 0xa3ffffff)
    {
        while (length < count)
        {
            tempCh = getc();
            
            if(tempCh == 4) //EOT, echo to stdout and return length
                return length;
            else if(tempCh == 8 || tempCh == 127) //Backspace or delete, echo "\b \b"
            {
                if (length > 0) {
                    length -= 1;
                    buf[length] = '\0';
                }
                puts("\b \b");
            }
            else if(tempCh == 10 || tempCh == 13) // new line or carriage return, newline in buffer, echo and retun
            {
                buf[length] = '\n';
                putc('\n');
                length += 1;
                return length;
            }
            else
            {
                buf[length] = tempCh;
                putc(tempCh);
                length += 1;
            }
        }
    }
    else
        return -EFAULT;
    
    return length;
}

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd  __attribute__((unused)), const char *buf  __attribute__((unused)), size_t count  __attribute__((unused)))
{
    unsigned i;
    unsigned start = (unsigned int)buf;
    unsigned end = (unsigned int)(buf+count);
    
    //file descriptor is not stdout
    if (fd != STDOUT_FILENO)
        return -EBADF;
    
    //memory range not exceeds ROM or SDRAM
    if ( end <= 0x00ffffff ||
        (start >= 0xa0000000 && end <= 0xa3ffffff))
    {
        for(i=0; i<count; ++i) //stdout won't encounter short write
            putc(buf[i]);
    }
    else
        return -EFAULT;
    
    return i;
}

