#include "mns.h"

/* Constructors: */
MNS::MNS(std::vector<HostIPPair> vector_data):
    database(vector_data.begin(), vector_data.end())
{
    /* Empty constructor body. */
}

void MNS::insert(const HostName& host, const IPAddress& address)
{
    database.insert(make_hostip_pair(host, address));
}

bool MNS::remove(const HostName& host)
{
    return database.erase(host) > 0;
}

IPAddress MNS::lookup(const HostName& host) const
{
    std::map<HostName, IPAddress>::iterator it;
    it = database.find(host);
    if (it == database.end()) {
        return NON_EXISTING_ADDRESS;
    }
    return (*it).second;
}
