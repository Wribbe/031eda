#include "hns.h"

/* Constructors: */
HNS::HNS() : HNS(default_size)
{
}
HNS::HNS(int table_size) :
    table_size(table_size)
{
    database = hashMap(table_size);
}

size_t HNS::get_index(const HostName& host) const
{
    return hash_host(host) % table_size;
}

void HNS::insert(const HostName& host, const IPAddress& address)
{
    size_t index = get_index(host);
    database[index].push_back(make_hostip_pair(host, address));
}

bool HNS::remove(const HostName& host)
{
    size_t index = get_index(host);
    HostIPPair_iter it = get_HostIPPair_iter(host, index);
    bool found = it != database[index].end();
    if (found) {
        database[index].erase(it);
    }
    return found;
}

HostIPPair_iter HNS::get_HostIPPair_iter(const HostName& host,
                                         size_t index) const
    /* Return find_if iterator based on host. */
{
    auto cmp_lambda = [&host](HostIPPair stored)mutable ->bool {
        return host.compare(stored.first) == 0;
    };
    HostIPPair_iter it = std::find_if(database[index].begin(),
                                      database[index].end(),
                                      cmp_lambda);
    return it;
}

IPAddress HNS::lookup(const HostName& host) const
    /* Look up and return host IP address if present. */
{
    size_t index = get_index(host);
    HostIPPair_iter it = get_HostIPPair_iter(host, index);
    if (it == database[index].end()) {
        return NON_EXISTING_ADDRESS;
    }
    return get_ip(it);
}
