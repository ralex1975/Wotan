#pragma once

#include "StdAfx.h"


#include "application/logger.hpp"

#include "client.hpp"

namespace Wotan
{
	client::client() 
		: signalReader_(2000)										// 2 seconds timeout
		, client_(new EClientSocket(this, &signalReader_))
		, state_(ST_CONNECT)
		, sleepDeadline_(0)
		, orderId_(0)
		, eReader_(0)
		, extraAuth_(false) 
	{
		client_->asyncEConnect(false);
	}

	client::~client()
	{
		if (eReader_)
			delete eReader_;

		delete client_;
	}

	bool client::connect(const char *host, unsigned int port, int clientId)
	{
		// trying to connect
		if (client_->eConnect(host, port, clientId, extraAuth_)) 
		{
			eReader_ = new EReader(client_, &signalReader_);

			eReader_->start();

			return true;
		}
		else
		{
			return false;
		}
	}

	void client::disconnect() const
	{
		client_->eDisconnect();

		printf("Disconnected\n");
	}

	bool client::isConnected() const
	{
		return client_->isConnected();
	}

	void client::setConnectOptions(const std::string & connectOptions)
	{
		client_->setConnectOptions(connectOptions);
	}

	void client::processMessages() 
	{
		auto now = boost::posix_time::microsec_clock::local_time();

		eReader_->checkClient();
		signalReader_.waitForSignal();
		eReader_->processMsgs();
	}

	// callbacks
	void client::error(const int id, const int errorCode, const std::string errorString)
	{
		LOG_ERROR() << errorString.c_str();
	}

	void client::connectionClosed() 
	{ 
		LOG_INFO() << "connection has been closed";
	}

	void client::currentTime(long time) 
	{
		LOG_INFO() << "current time on server: " << time;
	}

	void client::connectAck() 
	{ 
		if (client_->asyncEConnect())
			client_->startApi();
	}


	// not implemented
	void client::tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) { throw std::exception(); }
	void client::tickSize(TickerId tickerId, TickType field, int size) { throw std::exception(); }
	void client::tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
		double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) { throw std::exception(); }
	void client::tickGeneric(TickerId tickerId, TickType tickType, double value) { throw std::exception(); }
	void client::tickString(TickerId tickerId, TickType tickType, const std::string& value) { throw std::exception(); }
	void client::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
		double totalDividends, int holdDays, const std::string& futureLastTradeDate,
		double dividendImpact, double dividendsToLastTradeDate) { throw std::exception(); }
	void client::orderStatus(OrderId orderId, const std::string& status, double filled,
		double remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const std::string& whyHeld) { throw std::exception(); }
	void client::openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&) { throw std::exception(); }
	void client::openOrderEnd() { throw std::exception(); }
	void client::winError(const std::string& str, int lastError) { throw std::exception(); }
	void client::updateAccountValue(const std::string& key, const std::string& val,
		const std::string& currency, const std::string& accountName) { throw std::exception(); }
	void client::updatePortfolio(const Contract& contract, double position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const std::string& accountName) { throw std::exception(); }
	void client::updateAccountTime(const std::string& timeStamp) { throw std::exception(); }
	void client::accountDownloadEnd(const std::string& accountName) { throw std::exception(); }
	void client::nextValidId(OrderId orderId) { throw std::exception(); }
	void client::contractDetails(int reqId, const ContractDetails& contractDetails) { throw std::exception(); }
	void client::bondContractDetails(int reqId, const ContractDetails& contractDetails) { throw std::exception(); }
	void client::contractDetailsEnd(int reqId) { throw std::exception(); }
	void client::execDetails(int reqId, const Contract& contract, const Execution& execution) { throw std::exception(); }
	void client::execDetailsEnd(int reqId) { throw std::exception(); }
	void client::updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size) { throw std::exception(); }
	void client::updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
		int side, double price, int size) { throw std::exception(); }
	void client::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage,
		const std::string& originExch) { throw std::exception(); }
	void client::managedAccounts(const std::string& accountsList) { throw std::exception(); }
	void client::receiveFA(faDataType pFaDataType, const std::string& cxml) { throw std::exception(); }
	void client::historicalData(TickerId reqId, const std::string& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps) { throw std::exception(); }
	void client::scannerParameters(const std::string& xml) { throw std::exception(); }
	void client::scannerData(int reqId, int rank, const ContractDetails& contractDetails,
		const std::string& distance, const std::string& benchmark, const std::string& projection,
		const std::string& legsStr) { throw std::exception(); }
	void client::scannerDataEnd(int reqId) { throw std::exception(); }
	void client::realtimeBar(TickerId reqId, long time, double open,
		double high, double low, double close,
		long volume, double wap, int count) { throw std::exception(); }
	void client::fundamentalData(TickerId reqId, const std::string& data) { throw std::exception(); }
	void client::deltaNeutralValidation(int reqId, const UnderComp& underComp) { throw std::exception(); }
	void client::tickSnapshotEnd(int reqId) { throw std::exception(); }
	void client::marketDataType(TickerId reqId, int marketDataType) { throw std::exception(); }
	void client::commissionReport(const CommissionReport& commissionReport) { throw std::exception(); }
	void client::position(const std::string& account, const Contract& contract,
		double position, double avgCost) { throw std::exception(); }
	void client::positionEnd() { throw std::exception(); }
	void client::accountSummary(int reqId, const std::string& account, const std::string& tag,
		const std::string& value, const std::string& curency) { throw std::exception(); }
	void client::accountSummaryEnd(int reqId) { throw std::exception(); }
	void client::verifyMessageAPI(const std::string& apiData) { throw std::exception(); }
	void client::verifyCompleted(bool isSuccessful, const std::string& errorText) { throw std::exception(); }
	void client::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallenge) { throw std::exception(); }
	void client::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText) { throw std::exception(); }
	void client::displayGroupList(int reqId, const std::string& groups) { throw std::exception(); }
	void client::displayGroupUpdated(int reqId, const std::string& contractInfo) { throw std::exception(); }
	void client::positionMulti(int reqId, const std::string& account, const std::string& modelCode,
		const Contract& contract, double pos, double avgCost) { throw std::exception(); }
	void client::positionMultiEnd(int reqId) { throw std::exception(); }
	void client::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode,
		const std::string& key, const std::string& value, const std::string& currency) { throw std::exception(); }
	void client::accountUpdateMultiEnd(int reqId) { throw std::exception(); }
	void client::securityDefinitionOptionalParameter(int reqId, const std::string& exchange,
		int underlyingConId, const std::string& tradingClass, const std::string& multiplier,
		std::set<std::string> expirations, std::set<double> strikes) { throw std::exception(); }
	void client::securityDefinitionOptionalParameterEnd(int reqId) { throw std::exception(); }
	void client::softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) { throw std::exception(); }
}