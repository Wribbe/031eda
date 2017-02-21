/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef NAME_SERVER_INTERFACE_H
#define NAME_SERVER_INTERFACE_H

#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using HostName = std::string;
using IPAddress = unsigned int;
using HostIPPair = std::pair<HostName, IPAddress>;
using HostIPPair_iter = std::vector<HostIPPair>::iterator;

const IPAddress NON_EXISTING_ADDRESS = 0;

static const std::string data_path = "input/nameserverdata.txt";

class Line {
public:
    friend std::istream& operator>>(std::istream &stream, Line &line);
    operator std::string() const;
    operator HostIPPair() const;
private:
    std::string data;
};

std::istream& operator>>(std::istream &stream, Line &line);
std::vector<HostIPPair> data_vector();

class NameServerInterface {
public:
	virtual ~NameServerInterface() = default;

	/*
	 * Insert a name/address pair. Does not check if the name
	 * or address already exists.
	 */
	virtual void insert(const HostName&, const IPAddress&) = 0;

	/*
	 * Remove the pair with the specified host name. Returns true
	 * if the host name existed and the pair was removed, false
	 * otherwise.
	 */
	virtual bool remove(const HostName&) = 0;

	/*
	 * Find the IP address for the specified host name. Returns
	 * NON_EXISTING_ADDRESS if the host name wasn't in the name
	 * server.
	 */
	virtual IPAddress lookup(const HostName&) const = 0;
};

HostIPPair make_hostip_pair(const std::string& string);
HostIPPair make_hostip_pair(const HostName& host, const IPAddress& address);
IPAddress get_ip(HostIPPair_iter& iter);
IPAddress get_ip(HostIPPair& pair);

#endif
