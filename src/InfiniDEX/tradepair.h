// Copyright (c) 2017-2018 The Infinex Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRADEPAIR_H
#define TRADEPAIR_H

#include <iostream>
#include <vector>
#include <map>
#include "userconnection.h"

class CTradePair;
class CTradePairManager;

extern std::map<int, CTradePair> mapCompleteTradePair;
extern CTradePairManager tradePairManager;

enum tradepair_enum {
	TRADEPAIR_INVALID = 0,
	TRADEPAIR_EXIST = 1,
	TRADEPAIR_ADDED = 2,
	TRADEPAIR_UPDATED = 3,
	TRADEPAIR_COINID_EXIST = 4,
	TRADEPAIR_REVERSE_COINID_EXIST = 5,
	TRADEPAIR_SYMBOL_EXIST = 6,
	TRADEPAIR_REVERSE_SYMBOL_EXIST = 7
};

class CTradePair
{
private:
	std::vector<unsigned char> vchSig;

public:
	int nTradePairID;
	std::string nName;
	int nCoinID1;
	std::string nSymbol1;
	int nCoinID2;
	std::string nSymbol2;
	bool nTradeEnabled;
	uint64_t nMinimumTradeQuantity;
	uint64_t nMaximumTradeQuantity;
	uint64_t nMinimumTradeAmount;
	uint64_t nMaximumTradeAmount;
	int nBidTradeFee; //regular trade fee in percentage for bid, can be negative as form of incentive
	int nBidTradeFeeCoinID; //trade fee coin type payout for bid
	int nAskTradeFee; //regular trade fee in percentage for ask, can be negative as form of incentive
	int nAskTradeFeeCoinID; //trade fee coin type payout for ask
	std::string nStatus;
	uint64_t nLastUpdate;
	std::string nHash;

	CTradePair(int nTradePairID, std::string nName, int nCoinID1, std::string nSymbol1, int nCoinID2, std::string nSymbol2,
		bool nTradeEnabled, uint64_t nMinimumTradeQuantity, uint64_t nMaximumTradeQuantity, uint64_t nMinimumTradeAmount, uint64_t nMaximumTradeAmount,
		int nBidTradeFee, int nBidTradeFeeCoinID, int nAskTradeFee, int nAskTradeFeeCoinID, std::string nStatus, uint64_t nLastUpdate, std::string nHash) :
		nTradePairID(nTradePairID),
		nName(nName),
		nCoinID1(nCoinID1),
		nSymbol1(nSymbol1),
		nCoinID2(nCoinID2),
		nSymbol2(nSymbol2),
		nTradeEnabled(nTradeEnabled),
		nMinimumTradeQuantity(nMinimumTradeQuantity),
		nMaximumTradeQuantity(nMaximumTradeQuantity),
		nMinimumTradeAmount(nMinimumTradeAmount),
		nMaximumTradeAmount(nMaximumTradeAmount),
		nBidTradeFee(nBidTradeFee),
		nBidTradeFeeCoinID(nBidTradeFeeCoinID),
		nAskTradeFee(nAskTradeFee),
		nAskTradeFeeCoinID(nAskTradeFeeCoinID),
		nStatus(nStatus),
		nLastUpdate(nLastUpdate),
		nHash(nHash)
	{}

	CTradePair() :
		nTradePairID(0),
		nName(""),
		nCoinID1(0),
		nSymbol1(""),
		nCoinID2(0),
		nSymbol2(""),
		nTradeEnabled(false),
		nMinimumTradeQuantity(0),
		nMaximumTradeQuantity(0),
		nMinimumTradeAmount(0),
		nMaximumTradeAmount(0),
		nBidTradeFee(0),
		nBidTradeFeeCoinID(0),
		nAskTradeFee(0),
		nAskTradeFeeCoinID(0),
		nStatus(""),
		nLastUpdate(0),
		nHash("")
	{}

	bool Verify();
	bool RelayTo(CNode* node, CConnman& connman);
};

class CTradePairManager
{
private:
	std::vector<unsigned char> vchSig;

public:
	CTradePairManager() {}
	void ProcessMessage(CNode* node, std::string& strCommand, CDataStream& vRecv, CConnman& connman);
	void SendCompleteTradePairs(CNode* node, CConnman& connman);
	void SendTradePair(CTradePair TradePair, CNode* node, CConnman& connman);
	tradepair_enum ProcessTradePair(CTradePair TradePair);
	bool IsValidTradePairID(int TradePairID);
	CTradePair GetTradePair(int TradePairID);
	bool IsTradeEnabled(int TradePairID);
	std::string GetTradePairStatus(int TradePairID);
	int GetAskSideCoinID(int TradePairID);
	int GetBidSideCoinID(int TradePairID);
	void GetTradeFee(int TradePairID, int &BuyFee, int &SellFee);
	int GetBidTradeFee(int TradePairID);
	int GetAskTradeFee(int TradePairID);
};

#endif