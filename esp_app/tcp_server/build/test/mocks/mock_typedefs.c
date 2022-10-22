#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_typedefs.h"


static struct mock_typedefsInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_typedefs_Verify(void)
{
}

void mock_typedefs_Init(void)
{
  mock_typedefs_Destroy();
}

void mock_typedefs_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

