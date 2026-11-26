#include "Status.h"

const char *Status_ToString(Status_e status)
{
    switch (status)
    {
        case STATUS_OK:
            return "OK";
        case STATUS_BUSY:
            return "BUSY";
        case STATUS_TIMEOUT:
            return "TIMEOUT";
        case STATUS_INVALID_PARAM:
            return "INVALID_PARAM";
        case STATUS_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}
