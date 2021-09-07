#include "FreeRTOSApplicationHooks.h"

__attribute__((weak))
__attribute__((optimize("no-optimize-sibling-calls"))) 
void vApplicationIdleHook( void )
{
}

__attribute__((weak))
__attribute__((optimize("no-optimize-sibling-calls"))) 
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
}

__attribute__((weak))
__attribute__((optimize("no-optimize-sibling-calls"))) 
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
}
