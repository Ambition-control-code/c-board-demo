#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H

typedef enum
{
    STATUS_OK = 0U,
    STATUS_BUSY = 1U,
    STATUS_TIMEOUT = 2U,
    STATUS_INVALID_PARAM = 3U,
    STATUS_ERROR = 4U,
} Status_e;

const char *Status_ToString(Status_e status);

#endif
