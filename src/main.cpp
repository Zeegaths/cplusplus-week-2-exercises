#include "main.h"

// ---- Supporting type member functions ---------------------------------------

bool Outpoint::operator==(const Outpoint& other) const {
    return txid == other.txid && vout == other.vout;
}

bool UTXO::operator==(const UTXO& other) const {
    return txid == other.txid && vout == other.vout && value == other.value;
}

uint64_t TestWallet::balance() const {
    // TODO: return the wallet's confirmed balance
    return 0;
}

// ---- Exercises --------------------------------------------------------------

std::optional<std::vector<uint8_t>> decode_hex(const std::string& hex_str) {
    // TODO: decode `hex_str` into bytes; return std::nullopt on invalid input
    (void)hex_str;
    return std::nullopt;
}

std::vector<uint8_t> to_big_endian(const std::vector<uint8_t>& bytes) {
    // TODO: reverse the byte order of `bytes` and return the result
    (void)bytes;
    return {};
}

std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    // TODO: convert `bytes` to a lowercase hex string
    (void)bytes;
    return "";
}

std::optional<std::vector<uint8_t>> hex_to_bytes(const std::string& hex) {
    // TODO: convert `hex` to bytes; return std::nullopt on invalid input
    (void)hex;
    return std::nullopt;
}

std::array<uint8_t, 4> swap_endian_u32(uint32_t num) {
    // TODO: return the 4 bytes of `num` in reversed (endian-swapped) order
    (void)num;
    return {0, 0, 0, 0};
}

std::optional<uint64_t> parse_satoshis(const std::string& input) {
    // TODO: parse `input` as an unsigned satoshi amount; std::nullopt on failure
    (void)input;
    return std::nullopt;
}

ScriptType classify_script(const std::vector<uint8_t>& script) {
    // TODO: classify `script` as P2PKH (starts with 0x76 0xa9 0x14),
    //       P2WPKH (starts with 0x00 0x14), otherwise Unknown
    (void)script;
    return ScriptType::Unknown;
}

std::vector<uint8_t> read_pushdata(const std::vector<uint8_t>& script) {
    // TODO: return the pushdata portion of `script` (everything from index 2 onwards)
    (void)script;
    return {};
}

void apply_fee(uint64_t& balance, uint64_t fee) {
    // TODO: subtract `fee` from `balance` in place
    (void)balance;
    (void)fee;
}

std::string move_txid(std::string txid) {
    // TODO: return a string of the form "txid: <txid>"
    (void)txid;
    return "";
}

std::optional<Opcode> opcode_from_byte(uint8_t byte) {
    // TODO: 0xac -> Opcode::OpChecksig, 0x76 -> Opcode::OpDup,
    //       anything else -> std::nullopt
    (void)byte;
    return std::nullopt;
}

UTXO consume_utxo(UTXO utxo) {
    // TODO: return `utxo` (demonstrates move semantics)
    (void)utxo;
    return {};
}
