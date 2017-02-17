#include "vns.h"

VNS::VNS()
    /* Constructors: */
{
}

void VNS::insert(const HostName& host, const IPAddress& address)
{
    std::istream_iterator<HostIPPair> iter = data_iterator();
}

bool VNS::remove(const HostName& host)
{
    return true;
}

IPAddress VNS::lookup(const HostName& host) const
{
    return NON_EXISTING_ADDRESS;
}
