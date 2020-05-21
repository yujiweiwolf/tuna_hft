#pragma once
#pragma once
#include <cstring>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

using namespace std;

#define ORDER_REF_PRELEN 3
#define ORDER_REF_POSTLEN 9
#define ORDER_REF_LEN (ORDER_REF_PRELEN+ORDER_REF_POSTLEN)
#define MAXSTRATEGYID   999
#define THIRD_PART_STRATEGYID 999
#define COMMON_STRATEGY_ID 888

typedef char ExchangeState;
#define Exchange_BeforeTrading '0'
#define Exchange_NoTrading '1'
#define Exchange_Continous '2'
#define Exchange_AuctionOrdering '3'
#define Exchange_AuctionBalance '4'
#define Exchange_AuctionMatch '5'
#define Exchange_Closed '6'

typedef const char* START_MODE;
#define INIT_FINISHED "INIT_FINISH"
#define START_MODE "start"
#define QUICK_MODE "quick"
#define RESUME_MODE "resume"
#define NONE_MODE "none"

typedef int LocalOrderDirType;
#define API_BUY     0
#define API_SELL    1
#define DIRECTION_COUNT 2

typedef const char* MessageType;
#define MEMORY_MESSAGE_TYPE "memory_type"
#define ZMQ_MESSAGE_TYPE "zmq_type"

typedef const char* ExchangeType;
#define SH_GOLD_EXCHAGE "SGE"
#define SH_ENERGE_EXCHANGE "INE"
#define SH_FUTURE_EXCHANGE "SHFE"

typedef int LocalMessageSource;
#define MEMORY_MESSAGE_TRADE 0
#define MEMORY_MESSAGE_REQ 1
#define MEMORY_MESSAGE_MARKET 2
#define STRATEGY_MESSAGE_REQ 3

typedef int LocalPosDirectionType;
#define LONG_POS    API_BUY
#define SHORT_POS   API_SELL

#define API_LONG                API_BUY
#define API_SHORT               API_SELL

typedef int LocalOffsetType;
#define API_OPEN                0
#define API_CLOSE               1
#define API_CLOSE_TODAY          3
#define API_CLOSE_YESTERDAY      4

typedef int LocalOrderPriceType;
#define API_MARKET_PRICE             1
#define API_LIMIT_PRICE              2
#define API_LIMIT_PRICE_FOK          3
#define API_LIMIT_PRICE_FAK          4
#define API_MARKET_PRICE_LIMIT       5
#define API_FIVE_LEVEL_PRICE          6
#define API_FIVE_LEVEL_PRICE_LIMIT    7
#define API_BEST_PRICE               8
#define API_BEST_PRICE_LIMIT         9

typedef char LocalTimeCondition;
#define API_TC_IOC   '1'
#define API_TC_ELSE  '2'

typedef int LocalMessageType;
#define RSP_LOGIN               1
#define REQ_ORDER_INSERT     2
#define RTN_ORDER               3
#define RTN_TRADE               4
#define RTN_CANCEL              5
#define RTN_POSITION   14
#define RSP_ERROR_INSERT        6
#define RSP_ERROR_CANCEL        7
#define RSP_QRY_ORDER           8
#define RSP_QRY_TRADE           9
#define RSP_QRY_CAPITAL         10
#define RSP_QRY_POSITION        11   
#define RSP_QRY_INSTRUMENT  12
#define EXCHANGE_STATE          13

//typedef int STRATEGY_MESSAGE_TYPE;
#define STRATEGY_REQ_INSERT 1001
#define STRATEGY_REQ_CANCEL 1002
#define STRATEGY_REQ_LOGIN 1003
#define STRATEGY_REQ_LOGOUT 1006
#define STRATEGY_REQ_CONTROL 1007
#define STRATEGY_QRY_ACCOUNT 1004
#define STRATEGY_QRY_POSITION 1005
#define STRATEGY_QRY_CAPITAL 1008
#define STRATEGY_SUBSCRIBE  10009

#define EXTERNAL_ORDER_INSERT_ERR 2006
#define EXTERNAL_ORDER_CANCEL_ERR 2007
#define EXTERNAL_RTN_CANCEL 2008
#define EXTERNAL_RTN_ORDER 2009
#define EXTERNAL_RTN_TRADE 2010
#define EXTERNAL_RTN_ACCOUNT_INFO 2011
#define EXTERNAL_RTN_POSITION_DETAIL 2012
#define EXTERNAL_API_ERROR 2013
#define EXTERNAL_RTN_INSTRUMENT_STATUS 2014

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

#define RISK_SELF_TRADE  30050
#define RISK_CANCEL_TIMES 30051
#define RISK_BIG_CANCEL_TIMES 30052
#define RISK_POTENCIAL_SELF_TRADE 30053

#define API_RTN_ERROR -1

//type to strategy
#define STRATEGY_RSP_LOGIN 3000

typedef int RiskControlFlag;
#define RISK_CTRL_FLAG_BEFORE            0
#define RISK_CTRL_FLAG_CURRENT           1
#define RISK_CTRL_FLAG_AFTER             2

typedef int CHANNEL_TYPE;
#define CHANNEL_MARKET__TYPE 100
#define CHANNEL_PRIVATE_TYPE    101
#define CHANNEL_PUBLIC_TYPE     102

typedef const char* MEMORY_TYPE;
#define MEMORY_MARKET_TYPE "market"
#define MEMORY_REQ_TYPE   "req"
#define MEMORY_RTN_TYPE   "rtn"
#define MEMORY_POS_TYPE "position"
#define MEMORY_DIALOG_TYPE "dialog"
#define MEMORY_RISK_TYPE "risk"
#define MEMORY_PUBLIC_TYPE "public"
#define MEMORY_INIT_TYPE "init"

#define THIRD_STRATEGY_NAME     "Lurker"

#define ORDER_LOCAL_KEY         "%03ld_%06ld_%012ld"    // front_session_local
#define ORDER_SYSID_KEY         "%s_%s"                // exchange_sysid

//#define MD_NUM    2000000  
#define SEM_TOTAL 10
#define CONDITION_TOTAL 10
#define ALLINFO 100
#define MD_START 10

#define ORDER_REF_START 10000

// strategy client to trade kernel
#define ZMQ_STRATEGY_TRADE_IPC "ipc:///tmp/trade_backend.ipc"
#define ZMQ_API_THREAD_IPC "inproc://api_message"
#define ZMQ_LOOP_THREAD_IPC "inproc://req_backend"

// 下单错误返回
#define  INSERT_ERROR_BASE           -8100
#define  SMARTCENTER_STARTING        INSERT_ERROR_BASE
#define  ORDERREF_REPEAT            (INSERT_ERROR_BASE - 1)
#define  FUNDS_NOT_ENOUGH           (INSERT_ERROR_BASE - 2)
#define  ORDER_FIELD_ERROR          (INSERT_ERROR_BASE - 3)
#define  EXCHANGE_UNINSERT          (INSERT_ERROR_BASE - 4)
#define  NOT_ENOUGH_POS_CLOSED      (INSERT_ERROR_BASE - 5)
#define  SELF_TRADE_PREVENT         (INSERT_ERROR_BASE - 6)
#define  PLATFORM_FORCE_CLOSE       (INSERT_ERROR_BASE - 7)
#define  CANCLE_TIMES_OUT           (INSERT_ERROR_BASE - 8)
#define  OPEN_VOLUME_OUT            (INSERT_ERROR_BASE - 9)
#define  NO_INSTRUMENT_INFO         (INSERT_ERROR_BASE - 10)
#define  INSERT_STREAM_CONTROL      (INSERT_ERROR_BASE - 11)
#define  SELF_TRADE_TIMES_OUT       (INSERT_ERROR_BASE - 12)
#define  ORDER_FIELD_INVALID        (INSERT_ERROR_BASE - 13)
#define  POSITION_CLOSE_LOSS		(INSERT_ERROR_BASE - 14)
#define  ELSE_ORDER_ERROR           (INSERT_ERROR_BASE - 99)

// 撤单错误返回
#define  CANCLE_ERROR_BASE           -8200
#define  ORDERSTATUS_UNBAVAILABLE    CANCLE_ERROR_BASE
#define  NOT_FIND_ORDER             (CANCLE_ERROR_BASE - 1)
#define  EXCHANGE_UNCANCLE          (CANCLE_ERROR_BASE - 2)
#define  CANCLE_STREAM_CONTROL      (CANCLE_ERROR_BASE - 3)
#define  ELSE_CANCLE_ERROR          (CANCLE_ERROR_BASE - 99)

// 风控异常代码
#define  RISKCONTROL_ERROR_BASE      -8300
#define  ORDER_FREQUENCY             RISKCONTROL_ERROR_BASE
#define  FUNDSLOSS_OUTLIMIT         (RISKCONTROL_ERROR_BASE - 1)
#define  POSITION_OUTLIMIT          (RISKCONTROL_ERROR_BASE - 2)
#define  ELSE_RISK_ERROR            (RISKCONTROL_ERROR_BASE - 99)

#define RSP_TRADE_EMPTY         -9000

typedef long int PRICEKEY;

typedef char LocalDateType[32];
typedef char LocalTimeType[32];
typedef char LocalFrontAddrType[64];
typedef char LocalSystemNameType[64];
typedef char LocalAPIName[8];
typedef char LocalPasswordType[32];
typedef char LocalBrokerIDType[32];
typedef char LocalExchangeIDType[32];
typedef char LocalInvestorIDType[32];
typedef char LocalInstrumentIDType[32];
typedef char LocalProductType[32];
typedef char LocalStrategyNameType[32];
typedef char LocalOrderSysIDType[32];
typedef char LocalTradeIDType[32];
typedef char LocalCurrencyIDType[4];
typedef char LocalErrorMsgType[128];
typedef char LocalReserveType[8];

using LONG_INT = long int;
using STRING_VECTOR = vector<string>;
using STRING_SET = set<string>;

using STRING_INT_MAP = unordered_map<string, int>;
using STRING_DOUBLE_MAP = unordered_map<string, double>;
using STRING_BOOL_MAP = unordered_map<string, bool>;
using INT_STRING_MAP = unordered_map<int, string>;
using STRING_STRING_MAP = unordered_map<string, string>;
using LONG_STRING_MAP = unordered_map<long, string>;
using STRING_LONG_MAP = unordered_map<string, long>;
using STRING_SET_STRING_MAP = unordered_map<string, STRING_SET>;
using STRING_STRING_STRING_MAP = unordered_map<string, STRING_STRING_MAP>;
using STRING_STRING_LONG_MAP = unordered_map<string, STRING_LONG_MAP>;
using INT_INT_MAP = unordered_map<int, int>;
using INT_CHAR_MAP = unordered_map<int, char*>;
using LONG_INT_MAP = unordered_map<long, int>;
using INT_BOOL_MAP = unordered_map<int, bool>;
using INT_LONG_MAP = unordered_map<int, long>;
using LONG_LONG_MAP = unordered_map<long, long>;
using LONG_BOOL_MAP = unordered_map<long, bool>;


