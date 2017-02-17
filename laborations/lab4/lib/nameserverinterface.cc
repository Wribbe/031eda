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
    return std::make_pair("test", 123);
}

std::istream_iterator<std::pair<HostName, IPAddress>> data_iterator(void)
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
    for (HostIPPair pair : return_vector) {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }

    return std::istream_iterator<std::pair<HostName, IPAddress>>();
}
