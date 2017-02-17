#include "hns.h"

/* Constructors: */
HNS::HNS(void)
{
}
HNS::HNS(int)
{
}

void HNS::insert(const HostName& host, const IPAddress& address)
{
}

bool HNS::remove(const HostName& host)
{
    return true;
}

IPAddress HNS::lookup(const HostName& host) const
{
    return NON_EXISTING_ADDRESS;
}
