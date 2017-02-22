#ifndef HNS_H
#define HNS_H

#include "nameserverinterface.h"

using pairVector = std::vector<HostIPPair>;
using hashMap = std::vector<pairVector>;

class HNS : public NameServerInterface
{
public:
    HNS(int table_size);
    HNS();
    /* Constructors: */
    /*
     * Insert a name/address pair. Does not check if the name
     * or address already exists.
     */
    void insert(const HostName&, const IPAddress&);

    /*
     * Remove the pair with the specified host name. Returns true
     * if the host name existed and the pair was removed, false
     * otherwise.
     */
    bool remove(const HostName&);

    /*
     * Find the IP address for the specified host name. Returns
     * NON_EXISTING_ADDRESS if the host name wasn't in the name
     * server.
     */
    IPAddress lookup(const HostName&) const;
private:
    int default_size = 4500;
    size_t table_size;
    mutable hashMap database;
    std::hash<HostName> hash_host;
    size_t get_index(const HostName& host) const;
    HostIPPair_iter get_HostIPPair_iter(const HostName& host,
                                        size_t index) const;
};

#endif
