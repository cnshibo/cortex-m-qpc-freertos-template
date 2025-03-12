#ifndef __AL_APP_H__
#define __AL_APP_H__

#include "bl/types.h"

class App
{
public:
    App()
    {
    }
    ~App()
    {
    }

    void init(void);
    void deinit(void);

private:
};

extern App l_app;

PN_BEGIN_DECL

// void app_init(void);
// void app_deinit(void);

PN_END_DECL
#endif
