#ifndef PARSE_CSV_H
#define PARSE_CSV_H

#include <string>
#include <vector>

void ParseCSV(const std::string& csvSource, std::vector<std::vector<std::string> >& lines);

#endif // PARSE_CSV_H
