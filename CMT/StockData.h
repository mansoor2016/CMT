#pragma once

#include <string>

/// <summary>
/// Simplified data model
/// </summary>
struct StockData
{
	std::string timestamp;
	std::string name;
	double price;

	StockData(std::string&& timestamp, std::string&& name, double price);

	StockData(std::string&& dataRow);
};