#pragma once
#include "common.h"
#include "twobuf.h"


class Feeder {
public:
    Feeder();
    virtual ~Feeder();
    void SubscribeMarketData(std::vector<string>& vec_instruments);
    void UnSubscribeMarketData(std::vector<string>& vec_instruments);
    void WriteData(MarketDataField* data);
    MarketDataField* GetLastBar(const char* instrument);
    void AddCallBack(std::function<void(MarketDataField*)> func);
    void Dispatch();

private:
    std::set<string> set_instruments_;
    CycleArray<MarketDataField>* cycle_array_;
    unordered_map<string, MarketDataField> map_instruments_;
    std::vector<std::function<void(MarketDataField*)>> vec_funcs_;
    std::vector<MarketDataField*> vec_md_;
};

//CTP 行情的Spi
class CThostFtdcMdSpi {
public:
    ///深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {};
};

class CTP : public Feeder, public CThostFtdcMdSpi {
public:
    CTP();
    virtual ~CTP();
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) override;
};
