#include "umns.h"

/* Constructors: */
UMNS::UMNS(std::vector<HostIPPair> vector_data):
    database(vector_data.begin(), vector_data.end())
{
    /* Empty constructor body. */
}

void UMNS::insert(const HostName& host, const IPAddress& address)
{
    database.insert(make_hostip_pair(host, address));
}

bool UMNS::remove(const HostName& host)
{
    return database.erase(host) > 0;
}

IPAddress UMNS::lookup(const HostName& host) const
{
    std::unordered_map<HostName, IPAddress>::iterator it;
    it = database.find(host);
    if (it == database.end()) {
        return NON_EXISTING_ADDRESS;
    }
    return (*it).second;
}
