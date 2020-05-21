#pragma once
#include "common.h"
#include "twobuf.h"

class Accout {
public:
    Accout();
    ~Accout();
    virtual int SubmitOrder(LocalOrderInfo* order) {
        return 0;
    };

    virtual int SubmitCancel(LocalCancelInfo* order) {
        return 0;
    };

    virtual int QryBasicInfo() {
        return 0;
    }
    virtual int QryCapital(LocalQryCapital* qry_capital) {
        return 0;
    };

    virtual int QryOrderDetail(LocalQryOrder* qry_order) {
        return 0;
    };

    virtual int QryPosition(LocalQryPosition* qry_pos) {
        return 0;
    };

    virtual int QryTrade(LocalQryTrade* qry_trade) {
        return 0;
    };
    CTwoBuffer* buf_ = nullptr;
};

////CTPµÄAPI
//class CThostFtdcTraderSpi {
//public:
//    CThostFtdcTraderSpi() {};
//    ~CThostFtdcTraderSpi() {};
//    virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) {};
//    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) {};
//};
//
//class CtpTrade : public Accout, public CThostFtdcTraderSpi {
//public:
//    CtpTrade();
//    virtual ~CtpTrade();
//    virtual int QryCapital(LocalQryCapital* qry_capital) override;
//    virtual int QryOrderDetail(LocalQryOrder* qry_order) override;
//    virtual int QryPosition(LocalQryPosition* qry_pos) override;
//    virtual int QryTrade(LocalQryTrade* qry_trade) override;
//
//    virtual int SubmitOrder(LocalOrderInfo* order) override;
//    virtual int SubmitCancel(LocalCancelInfo* order) override;
//
//    virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) override;
//    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) override;
//};
