//
// Created by Kirill Zhukov on 10.06.2022.
//

#ifndef UVM_TRANSACTION_H
#define UVM_TRANSACTION_H
#include "chrono"
#include "rocksdb/db.h"
#include <format>
#include "iostream"
#include <sstream>

class Transaction {
public:
    Transaction();
    Transaction(const std::string &from, const std::string &to, uint64_t type,
                const std::map<std::string, std::string> &extraData, const std::string &previousHash, uint64_t date);
    Transaction(const std::string &from, const std::string &to, uint64_t type,
                const std::map<std::string, std::string> &extraData, const std::string &hash,
                const std::string &previousHash, uint64_t date);

    Transaction(const std::string &from, const std::string &to, uint64_t type,
                const std::map<std::string, std::string> &extraData, const std::string &hash,
                const std::string &previousHash);

    Transaction(const std::string &from, const std::string &to, uint64_t type,
                const std::map<std::string, std::string> &extraData, const std::string &previousHash);

    virtual ~Transaction();
    std::string from;
    std::string to;
    uint64_t type;
    uint64_t date;
    std::map<std::string, std::string> extra_data {{"name", nullptr}, {"value", nullptr}};
    std::string hash;
    std::string previous_hash;

    [[nodiscard]] const std::string &getFrom() const;
    void setFrom(const std::string &from);
    [[nodiscard]] const std::string &getTo() const;
    void setTo(const std::string &to);
    [[nodiscard]] uint64_t getType() const;
    void setType(uint64_t type);
    [[nodiscard]] uint64_t getDate() const;
    void setDate(uint64_t date);
    [[nodiscard]] const std::map<std::string, std::string> &getExtraData() const;
    void setExtraData(const std::map<std::string, std::string> &extraData);
    void generate_tx_hash(); // getting serializing value and make hashed it twice
    friend std::ostream& operator<< (std::ostream &out, const Transaction &transaction);
    std::string to_string();
    void set_current_date();

    bool operator==(const Transaction &rhs) const;

    bool operator!=(const Transaction &rhs) const;
protected:
};


#endif //UVM_TRANSACTION_H