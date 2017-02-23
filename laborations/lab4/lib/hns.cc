#include "hns.h"

/* Constructors: */
HNS::HNS() :
    HNS(default_size)
{
}
HNS::HNS(int table_size) :
    table_size(table_size),
    resize_at(get_resize_limit())
{
    database = hashMap(table_size);
}

size_t HNS::get_index(const HostName& host) const
{
    return hash_host(host) % table_size;
}

size_t HNS::get_resize_limit()
    /* Return resize limit. */
{
    return table_size - (table_size/min_free_divisor);
}

void HNS::rehash()
    /* Resize and re-hash the database vector. */
{
    size_t old_size = table_size;

    table_size *= resize_factor;
    database.resize(table_size);
    resize_at = get_resize_limit();

    pairVector collision_temp;

    for(size_t i = 0; i<old_size; ++i) {
        /* Go through the current elements and re-hash. */
        for(HostIPPair pair : database[i]) {
            size_t new_index = get_index(pair.first);
            if (new_index == i) { // Collides, wait.
                collision_temp.push_back(pair);
            } else { // No collision, add now.
                database[new_index].push_back(pair);
            }
        }
        /* Re-add any collisions occurring at this specific i. */
        for(HostIPPair colliding : collision_temp) {
            database[i].push_back(colliding);
        }
        /* Reset collision temp. */
        collision_temp = pairVector();
    }
}

void HNS::insert(const HostName& host, const IPAddress& address)
{
    num_insert++;
    if (num_insert >= resize_at) {
        rehash();
    }
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
