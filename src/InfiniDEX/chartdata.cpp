// Copyright (c) 2017-2018 The Infinex Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "stdafx.h"
#include "chartdata.h"
#include "tradepair.h"

class CChartData;
class CChartDataManager;

std::map<int, mapPeriodTimeData> mapChartData;
CChartDataManager ChartDataManager;

bool CChartDataManager::InitTradePair(int TradePairID)
{
	//if (!tradePairManager.IsValidTradePair(TradePairID))
		//return false;

	if (!mapChartData.count(TradePairID))
	{
		mapPeriodTimeData init;
		init.insert(std::make_pair(MINUTE_CHART_DATA, mapTimeData()));
		init.insert(std::make_pair(HOUR_CHART_DATA, mapTimeData()));
		init.insert(std::make_pair(DAY_CHART_DATA, mapTimeData()));
		mapChartData.insert(std::make_pair(TradePairID, init));
		return true;
	}
	if (!mapChartData[TradePairID].count(MINUTE_CHART_DATA))
	{
		mapChartData[TradePairID].insert(std::make_pair(MINUTE_CHART_DATA, mapTimeData()));
	}
	if (!mapChartData[TradePairID].count(HOUR_CHART_DATA))
	{
		mapChartData[TradePairID].insert(std::make_pair(HOUR_CHART_DATA, mapTimeData()));
	}
	if (!mapChartData[TradePairID].count(DAY_CHART_DATA))
	{
		mapChartData[TradePairID].insert(std::make_pair(DAY_CHART_DATA, mapTimeData()));
	}
	return true;
}

void CChartDataManager::InputNewTrade(int TradePairID, uint64_t Price, uint64_t Qty, uint64_t TradeTime)
{
	if (!InitTradePair(TradePairID))
		return;

	//process minute range	
	mapTimeData::reverse_iterator ri = mapChartData[TradePairID][MINUTE_CHART_DATA].rbegin();
	if (ri == mapChartData[TradePairID][MINUTE_CHART_DATA].rend())
	{
		int TimeRoundDown = TradeTime % 60;
		uint64_t newMinuteStart = TradeTime - TimeRoundDown;
		uint64_t newMinuteEnd = newMinuteStart + 60;
		TimeRange tr = std::make_pair(newMinuteStart, newMinuteEnd);
		CChartData cd(TradePairID, newMinuteStart, newMinuteEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
		mapChartData[TradePairID][MINUTE_CHART_DATA].insert(std::make_pair(tr, cd));
	}
	else
	{
		uint64_t lastMinuteEnd = ri->first.second;
		if (lastMinuteEnd >= TradeTime)
		{
			ri->second.nNoOfTrades++;
			ri->second.nQty += Qty;
			ri->second.nAmount += (Qty * Price);
			ri->second.nClosePrice = Price;
			if (Price > ri->second.nHighPrice)
				ri->second.nHighPrice = Price;
			else if (Price < ri->second.nLowPrice || ri->second.nLowPrice == 0)
				ri->second.nLowPrice = Price;
		}
		else
		{
			uint64_t newMinuteStart = lastMinuteEnd + 1;
			uint64_t newMinuteEnd = lastMinuteEnd + 60;
			TimeRange tr = std::make_pair(newMinuteStart, newMinuteEnd);
			CChartData cd(TradePairID, newMinuteStart, newMinuteEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
			mapChartData[TradePairID][MINUTE_CHART_DATA].insert(std::make_pair(tr, cd));
		}
	}

	//process hour range	
	mapTimeData::reverse_iterator ri2 = mapChartData[TradePairID][HOUR_CHART_DATA].rbegin();
	if (ri2 == mapChartData[TradePairID][HOUR_CHART_DATA].rend())
	{
		int TimeRoundDown = TradeTime % 3600;
		uint64_t newHourStart = TradeTime - TimeRoundDown;
		uint64_t newHourEnd = newHourStart + 3600;
		TimeRange tr = std::make_pair(newHourStart, newHourEnd);
		CChartData cd(TradePairID, newHourStart, newHourEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
		mapChartData[TradePairID][HOUR_CHART_DATA].insert(std::make_pair(tr, cd));
	}
	else
	{
		uint64_t lastHourEnd = ri2->first.second;
		if (lastHourEnd >= TradeTime)
		{
			ri2->second.nNoOfTrades++;
			ri2->second.nQty += Qty;
			ri2->second.nAmount += (Qty * Price);
			ri2->second.nClosePrice = Price;
			if (Price > ri2->second.nHighPrice)
				ri2->second.nHighPrice = Price;
			else if (Price < ri2->second.nLowPrice || ri->second.nLowPrice == 0)
				ri2->second.nLowPrice = Price;
		}
		else
		{
			uint64_t newHourStart = lastHourEnd + 1;
			uint64_t newHourEnd = newHourStart + 3600;
			TimeRange tr = std::make_pair(newHourStart, newHourEnd);
			CChartData cd(TradePairID, newHourStart, newHourEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
			mapChartData[TradePairID][HOUR_CHART_DATA].insert(std::make_pair(tr, cd));
		}
	}

	//process day range	
	mapTimeData::reverse_iterator ri3 = mapChartData[TradePairID][DAY_CHART_DATA].rbegin();
	if (ri3 == mapChartData[TradePairID][DAY_CHART_DATA].rend())
	{
		int TimeRoundDown = TradeTime % 86400;
		uint64_t newDayStart = TradeTime - TimeRoundDown;
		uint64_t newDayEnd = newDayStart + 86400;
		TimeRange tr = std::make_pair(newDayStart, newDayEnd);
		CChartData cd(TradePairID, newDayStart, newDayEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
		mapChartData[TradePairID][DAY_CHART_DATA].insert(std::make_pair(tr, cd));
	}
	else
	{
		uint64_t lastDayEnd = ri3->first.second;
		if (lastDayEnd >= TradeTime)
		{
			ri3->second.nNoOfTrades++;
			ri3->second.nQty += Qty;
			ri3->second.nAmount += (Qty * Price);
			ri3->second.nClosePrice = Price;
			if (Price > ri3->second.nHighPrice)
				ri3->second.nHighPrice = Price;
			else if (Price < ri3->second.nLowPrice || ri->second.nLowPrice == 0)
				ri3->second.nLowPrice = Price;
		}
		else
		{
			uint64_t newDayStart = lastDayEnd + 1;
			uint64_t newDayEnd = newDayStart + 86400;
			TimeRange tr = std::make_pair(newDayStart, newDayEnd);
			CChartData cd(TradePairID, newDayStart, newDayEnd, Price, Price, Price, Price, Price * Qty, Qty, 1);
			mapChartData[TradePairID][DAY_CHART_DATA].insert(std::make_pair(tr, cd));
		}
	}
}