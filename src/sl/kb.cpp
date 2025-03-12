#include "sl/kb.h"
#include "dl/common.h"
#include "dl/stm.h"

#define KEYBOARD_SCAN_TIMES 2

#define KEYBOARD_COLUMN_MAX 1
#define KEYBOARD_ROW_MAX 1
#define KEYBOARD_KEYS_MAX (KEYBOARD_COLUMN_MAX * KEYBOARD_ROW_MAX)

static uint8_t key_status_press[KEYBOARD_KEYS_MAX];
static uint8_t key_status_release[KEYBOARD_KEYS_MAX];
static uint8_t key_status_history[KEYBOARD_KEYS_MAX];

void kb_init(void)
{
    memset(key_status_press, 0, sizeof(key_status_press));
    memset(key_status_release, 0, sizeof(key_status_release));
    memset(key_status_history, 0, sizeof(key_status_history));

    /**********************************************************/
    
    /**********************************************************/
}

void kb_scan(void)
{
    for (uint8_t key_id = 0; key_id < KEYBOARD_KEYS_MAX; ++key_id)
    {
        uint8_t status;

        switch (key_id)
        {
        case 0:
        {
            status = LL_GPIO_IsInputPinSet(KEY_0_GPIO_Port, KEY_0_Pin);
        }
        break;

        default:
        {
            LOG("unknow key");
        }
        }

        if (status)
        {
            if (key_status_press[key_id] <= KEYBOARD_SCAN_TIMES)
            {
                key_status_press[key_id]++;
            }

            key_status_release[key_id] = 0;
        }
        else
        {
            if (key_status_release[key_id] <= KEYBOARD_SCAN_TIMES)
                key_status_release[key_id]++;

            // press action is not continue, reset
            key_status_press[key_id] = 0;
        }
    }

    for (int i = 0; i < KEYBOARD_KEYS_MAX; ++i)
    {
        // press detect
        if (key_status_press[i] == KEYBOARD_SCAN_TIMES)
        {
            key_status_history[i] = 1;
            key_evt_t *pe = Q_NEW(key_evt_t, KB_KEY_EVENT_SIG);
            pe->id = i;
            pe->state = 1;
            QF_PUBLISH((QEvt *)pe, NULL);
        }

        if ((key_status_release[i] == KEYBOARD_SCAN_TIMES) && key_status_history[i])
        {
            key_evt_t *pe = Q_NEW(key_evt_t, KB_KEY_EVENT_SIG);
            pe->id = i;
            pe->state = 0;
            QF_PUBLISH((QEvt *)pe, NULL);

            key_status_history[i] = 0;
        }
    }
}

void kb_dispatch_event(uint8_t id, uint8_t state)
{
    uint16_t sig = 0;

    // key release events
    if (state == 0)
    {
        switch (id)
        {
        case 0:
        {
            sig = KB_K0_RELEASE_SIG;
            LOG("K0 release");
        }
        break;
        case 1:
        {
            sig = KB_K1_RELEASE_SIG;
            LOG("K1 release");
        }
        break;

        default:
            break;
        }
    }
    else
    {
        switch (id)
        {
        case 0:
        {
            sig = KB_K0_PRESS_SIG;
            LOG("K0 press");
        }
        break;
        case 1:
        {
            sig = KB_K1_PRESS_SIG;
            LOG("K1 press");
        }
        break;

        default:
        {
            LOG("unknow key!");
        }
        break;
        }
    }

    if (sig)
    {
        key_evt_t *pe = Q_NEW(key_evt_t, sig);
        pe->id = id;
        pe->state = state;
        QF_PUBLISH((QEvt *)pe, NULL);
    }
}
