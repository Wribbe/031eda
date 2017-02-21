#include "vns.h"

VNS::VNS() :
    /* Constructors: */
    database(data_vector())
{
    /* Empty body. */
}


void VNS::insert(const HostName& host, const IPAddress& address)
{
    database.push_back(make_hostip_pair(host, address));
}

bool VNS::remove(const HostName& host)
{
    lookup_iter it = get_lookup_iter(host);
    bool found = it != database.end();
    if (found) {
        database.erase(it);
    }
    return found;
}

lookup_iter VNS::get_lookup_iter(const HostName& host) const
    /* Return find_if iterator based on host. */
{
    auto cmp_lambda = [&host](HostIPPair stored)mutable ->bool {
        return host.compare(stored.first) == 0;
    };
    lookup_iter it = std::find_if(database.begin(), database.end(), cmp_lambda);
    return it;
}

IPAddress VNS::lookup(const HostName& host) const
    /* Look up and return host IP address if present. */
{
    lookup_iter it = get_lookup_iter(host);
    if (it == database.end()) {
        return NON_EXISTING_ADDRESS;
    }
    return (*it).second;
}
