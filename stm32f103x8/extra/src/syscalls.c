#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

caddr_t _sbrk_getHeapStartAddress();

caddr_t _sbrk(int Size)
{
    // - Current heap end pointer
    static caddr_t hHeapEnd;

    // - Previous heap end pointer
    caddr_t hPrevHeapEnd;

    // - Init heap pointer
    if (hHeapEnd == 0)
	hHeapEnd = _sbrk_getHeapStartAddress();

    // - Get current stack pointer
    caddr_t hStackTop = (caddr_t)__get_MSP();

    // - Store current heap pointer
    hPrevHeapEnd = hHeapEnd;    

    // - Check is heap overlaps stack
    if (hHeapEnd + Size > hStackTop) {
	errno = ENOMEM;
	return (caddr_t)-1;
    }

    // - Add heap size
    hHeapEnd += Size;

    // - Return result
    return hPrevHeapEnd;
}

int usleep( useconds_t __useconds)
{    
    volatile uint32_t nCount;

    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    nCount = (RCC_Clocks.HCLK_Frequency / 10000000) * __useconds;
    for (; nCount !=0 ; nCount--);
    return 0;
}

unsigned int sleep(unsigned int __seconds)
{
    usleep(__seconds * 1000 * 1000);
    return 0;
}

int _close(int __fd)
{
    return 0;
}

ssize_t _write(int __fd, const void * __buf, size_t __n)
{
    uint8_t * Buffer = (uint8_t*)__buf;

    switch(__fd) {
	// --- USART 1
	case 1:
	    for (size_t i = 0; i < __n; i++) {
		// - Wait until TX ready
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		// - Send
		USART_SendData(USART1, Buffer[i]);
	    }
	    break;
	// --- USART 2
	case 2:
	    for (size_t i = 0; i < __n; i++) {
		// - Wait until TX ready
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		// - Send
		USART_SendData(USART2, Buffer[i]);
	    }
	    break;
	// --- USART 3
	case 3:
	    for (size_t i = 0; i < __n; i++) {
		// - Wait until TX ready
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		// - Send
		USART_SendData(USART3, Buffer[i]);
	    }
	    break;
    }

    return 0;
}

int _open(const char * __file, mode_t mode)
{
    if (!strcmp( __file, "/dev/usart1"))
	return 1;
    else if (!strcmp( __file, "/dev/usart2"))
	return 2;
    else if (!strcmp( __file, "/dev/usart3"))
	return 3;
    else
	return 0;
}

ssize_t _read(int __fd, void * __buf, size_t __nbytes)
{
    size_t i;
    size_t BytesRead = 0;

    switch(__fd) {
	case 1:
	    for (i = 0; i < __nbytes; i++) {
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		char c = (char)(USART_ReceiveData(USART1) & (uint16_t) 0x01FF);
		*((char*)__buf) = c;
		__buf++; BytesRead++;
	    }
	    break;
	case 2:
	    for (i = 0; i < __nbytes; i++) {
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
		char c = (char)(USART_ReceiveData(USART2) & (uint16_t) 0x01FF);
		*((char*)__buf) = c;
		__buf++; BytesRead++;
	    }
	    break;
	case 3:
	    for (i = 0; i < __nbytes; i++) {
		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
		char c = (char)(USART_ReceiveData(USART3) & (uint16_t) 0x01FF);
		*((char*)__buf) = c;
		__buf++; BytesRead++;
	    }
	    break;
	default:
	    errno = EBADF;
	    return -1;
    }

    return BytesRead;
}

void _exit(int x)
{
    while(1);
}

pid_t _getpid(void)
{
    return 1;
}
 
int _kill(int x)
{
    return 0;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    switch (file) {
	case 1:
	case 2:
	case 3:
	    return 1;
	default:
	    errno = EBADF;
	    return 0;
    }
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}
