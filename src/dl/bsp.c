#include "dl/bsp.h"
#include "dl/common.h"
#include "gpio.h"

Q_DEFINE_THIS_FILE // define the name of this file for assertions

// "RTOS-aware" interrupt priorities for FreeRTOS on ARM Cortex-M, NOTE1
#define RTOS_AWARE_ISR_CMSIS_PRI (configMAX_SYSCALL_INTERRUPT_PRIORITY >> (8 - __NVIC_PRIO_BITS))

    //============================================================================
    // Error handler

    Q_NORETURN
    Q_onError(char const *const module, int_t const id)
{
    // NOTE: this implementation of the error handler is intended only
    // for debugging and MUST be changed for deployment of the application
    // (assuming that you ship your production code with assertions enabled).
    Q_UNUSED_PAR(module);
    Q_UNUSED_PAR(id);
    QS_ASSERTION(module, id, 10000U); // report assertion to QS

#ifndef NDEBUG
    // for debugging, hang on in an endless loop...
    for (;;)
    {
        LOG("error");
    }
#else
    NVIC_SystemReset();
    for (;;)
    { // explicitly "no-return"
    }
#endif
}
// Application hooks used in this project ====================================
// NOTE: only the "FromISR" API variants are allowed in vApplicationTickHook
void vApplicationTickHook(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // process time events at rate 0
    QTIMEEVT_TICK_FROM_ISR(0U, &xHigherPriorityTaskWoken, &l_TickHook);

    // notify FreeRTOS to perform context switch from ISR, if needed
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
//............................................................................
void vApplicationIdleHook(void)
{
    // See NOTE01
    QF_INT_DISABLE();
    QF_INT_ENABLE();
}
//............................................................................
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    Q_ERROR();
}

void QF_onStartup(void)
{
    LOG("QF_onStartup");

    // assign all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE1
    NVIC_SetPriority(SysTick_IRQn, RTOS_AWARE_ISR_CMSIS_PRI + 1U);

    /*
     * QF_onStartup() is called after initial_events() in QF_run().
     * But initial_events() will process all events posted during QF initialization(in QACTIVE_START()),
     * QACTIVE_START() do the top-most initial transition, event posted in this top-most initial transition
     * which will be processed before QF_onStartup().
     * If we use QF_onStartup() as a hardware initialize entry, and post an event in core-reset state as a bootstrap
     * signal, this event will be processed before QF_onStartup(), so we can not/should not put any initialize code in
     * QF_onStartup().
     */

    /* Arm BOOT_STRAP_SIG to qm_core as a start point of the whole system */
    QEvt *pe = Q_NEW(QEvt, BOOT_STRAP_SIG);
    QF_PUBLISH((QEvt *)pe, NULL);
}

//............................................................................
void QF_onCleanup(void)
{
}

//============================================================================
// NOTE1:
// The configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY constant from the
// FreeRTOS configuration file specifies the highest ISR priority that
// is disabled by the QF framework. The value is suitable for the
// NVIC_SetPriority() CMSIS function.
//
// Only ISRs prioritized at or below the
// configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY level (i.e.,
// with the numerical values of priorities equal or higher than
// configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY) are allowed to call any
// QP/FreeRTOS services. These ISRs are "kernel-aware".
//
// Conversely, any ISRs prioritized above the
// configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY priority level (i.e., with
// the numerical values of priorities less than
// configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY) are never disabled and are
// not aware of the kernel. Such "kernel-unaware" ISRs cannot call any
// QP/FreeRTOS services. The only mechanism by which a "kernel-unaware" ISR
// can communicate with the QF framework is by triggering a "kernel-aware"
// ISR, which can post/publish events.
//
// For more information, see article "Running the RTOS on a ARM Cortex-M Core"
// http://www.freertos.org/RTOS-Cortex-M3-M4.html
//
// NOTE2:
// The User LED is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invocations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
