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

	StockData() = delete;
	
	StockData(const StockData&) = default;
	StockData(StockData&&) = default;

	StockData& operator=(const StockData&) = default;
	StockData& operator=(StockData&&) = default;

	StockData(std::string&& timestamp, std::string&& name, double price);

	StockData(std::string&& dataRow);

	std::string ToString() const;
};