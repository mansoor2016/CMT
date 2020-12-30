
#include <array>
#include <string>
#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "StockData.h"

StockData::StockData(std::string&& timestamp, std::string&& name, double price) :
	timestamp(timestamp), name(name), price(price) {};

StockData::StockData(std::string&& dataRow)
{
	std::vector<std::string> inputs(3);
	boost::split(inputs, std::move(dataRow), boost::is_any_of(","));

	assert(inputs.size() == 3);

	this->timestamp = inputs[0];
	this->name = inputs[1];
	this->price = boost::lexical_cast<double>(inputs[2]);
}

std::string StockData::ToString() const
{
	return this->timestamp + "," + this->name + "," + std::to_string(price);
}