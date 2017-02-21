#include "nameserverinterface.h"

std::istream& operator>>(std::istream &stream, Line &line)
    /* Overload operator>> to dictate how data-flow from std::istream -> Line
     * object behaves. */
{
    std::getline(stream, line.data);
    return stream;
}

Line::operator std::string() const
    /* Specify how a Line object is implicitly converted to a std::string. */
{
    return data;
}

Line::operator HostIPPair() const
    /* Specify how a Line object is implicitly converted to a HostIPPair. */
{
    return make_hostip_pair(data);
}

std::vector<HostIPPair> data_vector(void)
    /* Return iterator over all lines in the data as pairs. */
{
    std::ifstream file(data_path);
    if (!file.is_open()) {
        std::cerr << "No such file: " << data_path << ", aborting."\
            << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    std::istream_iterator<Line> iter = std::istream_iterator<Line>(file);
    std::istream_iterator<Line> end;

    std::vector<HostIPPair> return_vector;
    std::copy(iter, end, back_inserter(return_vector));

    return return_vector;
}

HostIPPair make_hostip_pair(const std::string& string)
    /* Method for making a HostIPPair from space separated string. */
{
    size_t space_index = string.find(" ");
    std::string hostName(string, 0, space_index-1);
    unsigned int ipNumber = std::stoul(std::string(string, space_index+1));
    return std::make_pair(hostName, ipNumber);
}

HostIPPair make_hostip_pair(const HostName& host, const IPAddress& address)
    /* Method for making a HostIPPair from separate values. */
{
    return std::make_pair(host, address);
}

