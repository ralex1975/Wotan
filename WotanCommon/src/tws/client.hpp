#pragma once
#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <vector>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <EWrapper.h>
#include <EClientSocket.h>
#include <EReaderOSSignal.h>
#include <EReader.h>

namespace Wotan
{
	class client : public EWrapper
	{
	public:
		enum State 
		{
			ST_CONNECT,
			ST_TICKDATAOPERATION,
			ST_TICKDATAOPERATION_ACK,
			ST_MARKETDEPTHOPERATION,
			ST_MARKETDEPTHOPERATION_ACK,
			ST_REALTIMEBARS,
			ST_REALTIMEBARS_ACK,
			ST_MARKETDATATYPE,
			ST_MARKETDATATYPE_ACK,
			ST_HISTORICALDATAREQUESTS,
			ST_HISTORICALDATAREQUESTS_ACK,
			ST_OPTIONSOPERATIONS,
			ST_OPTIONSOPERATIONS_ACK,
			ST_CONTRACTOPERATION,
			ST_CONTRACTOPERATION_ACK,
			ST_MARKETSCANNERS,
			ST_MARKETSCANNERS_ACK,
			ST_REUTERSFUNDAMENTALS,
			ST_REUTERSFUNDAMENTALS_ACK,
			ST_BULLETINS,
			ST_BULLETINS_ACK,
			ST_ACCOUNTOPERATIONS,
			ST_ACCOUNTOPERATIONS_ACK,
			ST_ORDEROPERATIONS,
			ST_ORDEROPERATIONS_ACK,
			ST_OCASAMPLES,
			ST_OCASAMPLES_ACK,
			ST_CONDITIONSAMPLES,
			ST_CONDITIONSAMPLES_ACK,
			ST_BRACKETSAMPLES,
			ST_BRACKETSAMPLES_ACK,
			ST_HEDGESAMPLES,
			ST_HEDGESAMPLES_ACK,
			ST_TESTALGOSAMPLES,
			ST_TESTALGOSAMPLES_ACK,
			ST_FAORDERSAMPLES,
			ST_FAORDERSAMPLES_ACK,
			ST_FAOPERATIONS,
			ST_FAOPERATIONS_ACK,
			ST_DISPLAYGROUPS,
			ST_DISPLAYGROUPS_ACK,
			ST_MISCELANEOUS,
			ST_MISCELANEOUS_ACK,
			ST_CANCELORDER,
			ST_CANCELORDER_ACK,
			ST_PING,
			ST_PING_ACK,
			ST_IDLE
		};

	public:

		client();
		~client();

		void setConnectOptions(const std::string&);
		void processMessages();
		bool connect(const char * host, unsigned int port, int clientId = 0);
		void disconnect() const;
		bool isConnected() const;

	protected:

		// callbacks
		virtual void connectionClosed();
		virtual void winError(const std::string& str, int lastError);
		virtual void error(const int id, const int errorCode, const std::string errorString);
		virtual void connectAck();

		// to implement
		virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
		virtual void tickSize(TickerId tickerId, TickType field, int size);
		virtual void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
			double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
		virtual void tickGeneric(TickerId tickerId, TickType tickType, double value);
		virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value);
		virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
			double totalDividends, int holdDays, const std::string& futureLastTradeDate, 
			double dividendImpact, double dividendsToLastTradeDate);
		virtual void orderStatus(OrderId orderId, const std::string& status, double filled,
			double remaining, double avgFillPrice, int permId, int parentId,
			double lastFillPrice, int clientId, const std::string& whyHeld);
		virtual void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
		virtual void openOrderEnd();
		virtual void updateAccountValue(const std::string& key, const std::string& val,
			const std::string& currency, const std::string& accountName);
		virtual void updatePortfolio(const Contract& contract, double position,
			double marketPrice, double marketValue, double averageCost,
			double unrealizedPNL, double realizedPNL, const std::string& accountName);
		virtual void updateAccountTime(const std::string& timeStamp);
		virtual void accountDownloadEnd(const std::string& accountName);
		virtual void nextValidId(OrderId orderId);
		virtual void contractDetails(int reqId, const ContractDetails& contractDetails);
		virtual void bondContractDetails(int reqId, const ContractDetails& contractDetails);
		virtual void contractDetailsEnd(int reqId);
		virtual void execDetails(int reqId, const Contract& contract, const Execution& execution);
		virtual void execDetailsEnd(int reqId);
		virtual void updateMktDepth(TickerId id, int position, int operation, int side,
			double price, int size);
		virtual void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
			int side, double price, int size);
		virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, 
			const std::string& originExch);
		virtual void managedAccounts(const std::string& accountsList);
		virtual void receiveFA(faDataType pFaDataType, const std::string& cxml);
		virtual void historicalData(TickerId reqId, const std::string& date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps);
		virtual void scannerParameters(const std::string& xml);
		virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
			const std::string& distance, const std::string& benchmark, const std::string& projection,
			const std::string& legsStr);
		virtual void scannerDataEnd(int reqId);
		virtual void realtimeBar(TickerId reqId, long time, double open, 
			double high, double low, double close,
			long volume, double wap, int count);
		virtual void currentTime(long time);
		virtual void fundamentalData(TickerId reqId, const std::string& data);
		virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp);
		virtual void tickSnapshotEnd(int reqId);
		virtual void marketDataType(TickerId reqId, int marketDataType);
		virtual void commissionReport(const CommissionReport& commissionReport);
		virtual void position(const std::string& account, const Contract& contract, 
			double position, double avgCost);
		virtual void positionEnd();
		virtual void accountSummary(int reqId, const std::string& account, const std::string& tag, 
			const std::string& value, const std::string& curency);
		virtual void accountSummaryEnd(int reqId);
		virtual void verifyMessageAPI(const std::string& apiData);
		virtual void verifyCompleted(bool isSuccessful, const std::string& errorText);
		virtual void verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallenge);
		virtual void verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText);
		virtual void displayGroupList(int reqId, const std::string& groups);
		virtual void displayGroupUpdated(int reqId, const std::string& contractInfo);
		virtual void positionMulti(int reqId, const std::string& account, const std::string& modelCode, 
			const Contract& contract, double pos, double avgCost);
		virtual void positionMultiEnd(int reqId);
		virtual void accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, 
			const std::string& key, const std::string& value, const std::string& currency);
		virtual void accountUpdateMultiEnd(int reqId);
		virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, 
			int underlyingConId, const std::string& tradingClass, const std::string& multiplier, 
			std::set<std::string> expirations, std::set<double> strikes);
		virtual void securityDefinitionOptionalParameterEnd(int reqId);
		virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers);

	protected:
		EReaderOSSignal signalReader_;
		EClientSocket * const client_;
		State state_;
		time_t sleepDeadline_;
		OrderId orderId_;
		EReader * eReader_;
		bool extraAuth_;
	};
}

#endif