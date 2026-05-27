#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// ---- Bitcoin script type enum -----------------------------------------------

enum class ScriptType {
    P2PKH,
    P2WPKH,
    Unknown,
};

// ---- Bitcoin opcode enum ----------------------------------------------------

enum class Opcode {
    OpChecksig,  // 0xac
    OpDup,       // 0x76
    OpInvalid,
};

// ---- Outpoint ---------------------------------------------------------------

struct Outpoint {
    std::string txid;
    uint32_t vout = 0;

    bool operator==(const Outpoint& other) const;
};

// ---- UTXO -------------------------------------------------------------------

struct UTXO {
    std::vector<uint8_t> txid;
    uint32_t vout = 0;
    uint64_t value = 0;

    bool operator==(const UTXO& other) const;
};

// ---- Wallet ----------------------------

class Wallet {
public:
    virtual ~Wallet() = default;
    virtual uint64_t balance() const = 0;
};

class TestWallet : public Wallet {
public:
    uint64_t confirmed = 0;
    uint64_t balance() const override;
};

// ---- Function declarations --------------------------------------------------

std::optional<std::vector<uint8_t>> decode_hex(const std::string& hex_str);

std::vector<uint8_t> to_big_endian(const std::vector<uint8_t>& bytes);

std::string bytes_to_hex(const std::vector<uint8_t>& bytes);

std::optional<std::vector<uint8_t>> hex_to_bytes(const std::string& hex);

std::array<uint8_t, 4> swap_endian_u32(uint32_t num);

std::optional<uint64_t> parse_satoshis(const std::string& input);

ScriptType classify_script(const std::vector<uint8_t>& script);

std::vector<uint8_t> read_pushdata(const std::vector<uint8_t>& script);

void apply_fee(uint64_t& balance, uint64_t fee);

std::string move_txid(std::string txid);

std::optional<Opcode> opcode_from_byte(uint8_t byte);

UTXO consume_utxo(UTXO utxo);
