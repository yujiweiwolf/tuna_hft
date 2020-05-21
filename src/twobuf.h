#pragma once

#include "common.h"
using namespace std;
#define DATALENGTH 256
#define FEEDERLENGTH 1024


class CTwoBuffer {
public:
    CTwoBuffer(const char* title);
    ~CTwoBuffer();
    void Init();
    MemoryHeader* GetMemoryHeader();
    bool IsCrossBoundary(int length);
    void SetMemoryHeader();


    template <typename T>
    MemoryMessage* AllocateMessage(int type) {
        if (IsCrossBoundary(sizeof(T))) {
            SetMemoryHeader();
        }
        MemoryMessage* current_message = (MemoryMessage*)((char*)header_ + header_->offset.load());
        memset(current_message, 0, sizeof(T) + sizeof(MemoryMessage));
        current_message->field = (char*)current_message + sizeof(MemoryMessage);
        current_message->header.length = sizeof(T);
        current_message->header.type = type;
        //printf("open_data header <%x> current_message<%x>, offset<%d>  flag <%d>\n", header_, current_message, header_->offset.load(), flag);
        return current_message;
    }

    template<typename T>
    void CloseAllocate() {
        header_->offset.add(sizeof(MemoryMessage) + sizeof(T));
        printf("close_data header <%x>, offset<%d>  flag <%d>\n", header_, header_->offset.load(), flag);
    }

    void GetMemoryMessage(std::vector<MemoryMessage*>& vec_msg);

private:
    MemoryHeader* header_;
    char* data1_ = nullptr;
    char* data2_ = nullptr;
    int flag;
    string buf_name_;
    int read_offset;
    MemoryHeader* read_header_ = nullptr;
};

template <typename T>
class CycleArray {
public:
    CycleArray() {
        datalenth = sizeof(T);
    };

    ~CycleArray() {
    };

    void WriteData(T* data) {
        int mod = write_index_.load() & (FEEDERLENGTH - 1);
            memcpy(dataArray_ + mod, data, datalenth);
            write_index_.add(1);
    };

    T* GetCycleHeader() {
        return dataArray_;
    }

    void GetMemoryMessage(std::vector<T*>& vec_msg) {
        while (read_index_ < write_index_.load()) {
            int mod = read_index_ & (FEEDERLENGTH - 1);
            vec_msg.push_back(dataArray_ + mod);
            read_index_++;
        }
    };

//public:
    boost::atomic_int write_index_;
    int read_index_ = 0;

//private:
    int datalenth;
    T dataArray_[FEEDERLENGTH];
};