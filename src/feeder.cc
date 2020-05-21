#include "feeder.h"

Feeder::Feeder() {
    cycle_array_ = new CycleArray<MarketDataField>();
}

Feeder::~Feeder() {

}


void Feeder::SubscribeMarketData(std::vector<string>& vec_instruments) {
    for (auto & it : vec_instruments) {
        set_instruments_.insert(it);
    }
}

void Feeder::UnSubscribeMarketData(std::vector<string>& vec_instruments) {
    for (auto & it : vec_instruments) {
        auto itor = set_instruments_.find(it);
        if (itor != set_instruments_.end()) {
            set_instruments_.erase(it);
        }
    }
}


void Feeder::WriteData(MarketDataField* data) {
    if (set_instruments_.find(data->instrument_id) != set_instruments_.end()) {
        cycle_array_->WriteData(data);
    }

    auto it = map_instruments_.find(data->instrument_id);
    if (it == map_instruments_.end()) {
        map_instruments_.insert(make_pair(data->instrument_id, *data));
    } else {
        it->second = *data;
    }
}

void Feeder::AddCallBack(std::function<void(MarketDataField*)> func) {
    vec_funcs_.push_back(func);
}

void Feeder::Dispatch() {
    vec_md_.clear();
    cycle_array_->GetMemoryMessage(vec_md_);
    for (auto& it : vec_md_) {
        for (auto& itor : vec_funcs_) {
            itor(it);
        }
    }
}


MarketDataField* Feeder::GetLastBar(const char* instrument) {
    auto it = map_instruments_.find(instrument);
    if (it == map_instruments_.end()) {
        return nullptr;
    }
    else {
        return &it->second;
    }
}


CTP::CTP() {

}

CTP::~CTP() {

}

//转化成通用的结构
void CTP::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
    MarketDataField data;
    Feeder::WriteData(&data);
}

