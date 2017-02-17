#include "umns.h"

UMNS::UMNS()
    /* Constructors: */
{
}

void UMNS::insert(const HostName& host, const IPAddress& address)
{
}

bool UMNS::remove(const HostName& host)
{
    return true;
}

IPAddress UMNS::lookup(const HostName& host) const
{
    return NON_EXISTING_ADDRESS;
}

