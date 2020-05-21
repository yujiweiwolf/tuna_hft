#pragma once
#ifndef DATATYPE_H
#define DATATYPE_H

#include <list>
#include <vector>
#include <string.h>
#include <unordered_map>
#include<iostream>
#include <set>
#include <map>
#include <memory>
#include <atomic>
#include <thread>
#include <iostream>
#include <string.h>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>
#include "singleton.h"
#include "lockfree.h"


#define STRATEGY_REQ_INSERT 1001
#define STRATEGY_REQ_CANCEL 1002
#define STRATEGY_REQ_LOGIN 1003
#define STRATEGY_REQ_LOGOUT 1006
#define STRATEGY_REQ_CONTROL 1007
#define STRATEGY_QRY_ACCOUNT 1004
#define STRATEGY_QRY_POSITION 1005
#define STRATEGY_QRY_CAPITAL 1008
#define STRATEGY_SUBSCRIBE  10009

// type from api 
#define API_RSP_LOGIN 30001
#define API_RSP_LOGOUT 30006
#define API_RTN_ORDER 30004
#define API_RTN_TRADE 30005
#define API_RTN_TRADE_FAK 30006
#define API_RTN_ERR_INSERT 30007
#define API_RTN_ERR_CANCEL 30008
#define API_RTN_POSITION 30009
#define API_RSP_CAPITAL 30010
#define API_RSP_QRY_ORDER 30011
#define API_RSP_QRY_TRADE 30012
#define API_RTN_INSTRUMENT_STATUS 30013
#define API_RTN_CANCEL  30014
#define API_RSP_INSTRUMENT_INFO 30015

using namespace std;

struct MarketDataField {
    char trading_day[16];
    char updatetime[16];
    char instrument_id[24];
};

//每个内存的头
struct MemoryHeader {
    boost::atomic<int> msg_count;
    boost::atomic<int> offset;
    boost::atomic<bool> next;
    char title[16];
};

struct MessageHeader {
    int type;
    int length;
};

struct MemoryMessage {
    MessageHeader header;
    char* field;
};

struct LocalStrategy {
    int strategy_id;
    char name[16];
};

struct LocalTrade {
    int volume;
    double price;
};

struct LocalOrderInfo {
    char strategy_name[32];
    char investor_id[32];
    char exchange_id[32];
    char instrument_id[32];
    int strategy_id;
    long order_spd_id;
    long strategy_order_ref;
    long local_order_ref;
    long cancel_local_ref;
};

struct LocalCancelInfo {
    char strategy_name[32];
    char investor_id[32];
    char exchange_id[32];
    char instrument_id[32];
    int strategy_id;
    long order_spd_id;
    long strategy_order_ref;
    long local_order_ref;
    long cancel_local_ref;
};

struct LocalQryCapital {
    char investor_id[32];
};

struct LocalQryPosition {
    char investor_id[32];
};

struct LocalQryOrder {
    char investor_id[32];
};

struct LocalQryTrade {
    char investor_id[32];
};

struct LocalRtnOrder {
    char investor_id[32];
};

struct LocalRtnTrade {
    char investor_id[32];
};




struct CThostFtdcOrderField {
    char investor_id[32];
};

struct CThostFtdcTradeField {
    char investor_id[32];
};

struct CThostFtdcDepthMarketDataField {
    char investor_id[32];
};

class Subject {
    Subject();
    ~Subject();
};


#endif /* DATATYPE_H */

