// Copyright (c) 2017-2018 The Infinex Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <iostream>
#include <vector>
#include <map>

class CChartData;
class CChartDataManager;

enum chart_period_enum {
	MINUTE_CHART_DATA = 1,
	HOUR_CHART_DATA = 2,
	DAY_CHART_DATA = 3
};

typedef std::pair<uint64_t, uint64_t> TimeRange;
typedef std::map<TimeRange, CChartData> mapTimeData;
typedef std::map<chart_period_enum, mapTimeData> mapPeriodTimeData;
extern std::map<int, mapPeriodTimeData> mapChartData;
extern CChartDataManager ChartDataManager;

class CChartData
{
public:
	int nTradePairID;
	uint64_t nStartTime;
	uint64_t nEndTime;
	uint64_t nOpenPrice;
	uint64_t nHighPrice;
	uint64_t nLowPrice;
	uint64_t nClosePrice;
	uint64_t nAmount;
	uint64_t nQty;
	uint64_t nNoOfTrades;

	CChartData(int nTradePairID, uint64_t nStartTime, uint64_t nEndTime, uint64_t nOpenPrice, uint64_t nHighPrice, uint64_t nLowPrice,
		uint64_t nClosePrice, uint64_t nAmount, uint64_t nQty, uint64_t nNoOfTrades) :
		nTradePairID(nTradePairID),
		nStartTime(nStartTime),
		nEndTime(nEndTime),
		nOpenPrice(nOpenPrice),
		nHighPrice(nHighPrice),
		nLowPrice(nLowPrice),
		nClosePrice(nClosePrice),
		nAmount(nAmount),
		nQty(nQty),
		nNoOfTrades(nNoOfTrades)
	{}

	CChartData() :
		nTradePairID(0),
		nStartTime(0),
		nEndTime(0),
		nOpenPrice(0),
		nHighPrice(0),
		nLowPrice(0),
		nClosePrice(0),
		nAmount(0),
		nQty(0),
		nNoOfTrades(0)
	{}
};

class CChartDataManager
{
public:
	CChartDataManager() {}
	bool InitTradePair(int TradePairID);
	void InputNewTrade(int TradePairID, uint64_t Price, uint64_t Qty, uint64_t TradeTime);
};

#endif