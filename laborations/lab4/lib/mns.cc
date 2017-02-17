#include "mns.h"

MNS::MNS()
    /* Constructors: */
{
}

void MNS::insert(const HostName& host, const IPAddress& address)
{
}

bool MNS::remove(const HostName& host)
{
    return true;
}

IPAddress MNS::lookup(const HostName& host) const
{
    return NON_EXISTING_ADDRESS;
}
