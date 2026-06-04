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
    return confirmed;
}

// ---- Exercises --------------------------------------------------------------

std::optional<std::vector<uint8_t>> decode_hex(const std::string& hex_str) {
    // TODO: decode `hex_str` into bytes; return std::nullopt on invalid input
    if (hex_str.size() % 2 != 0) return std::nullopt;

    std::vector<uint8_t> bytes{};
    for (size_t i = 0; i < hex_str.size(); i += 2) {
        char first = hex_str[i];
        char second = hex_str[i+1];

        if (!std::isxdigit(first) || !std::isxdigit(second)) return std::nullopt;

        uint8_t byte = std::stoi(std::string{first, second}, nullptr, 16);
        bytes.push_back(byte);
    }   
    
    return bytes;
}

std::vector<uint8_t> to_big_endian(const std::vector<uint8_t>& bytes) {

    // TODO: reverse the byte order of `bytes` and return the result
    (void)bytes;
    return std::vector<uint8_t>(bytes.rbegin(), bytes.rend());
}

std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    // TODO: convert `bytes` to a lowercase hex string
    static const char hexmap[] = "0123456789abcdef";
    std::string result{};
    result.reserve(bytes.size() * 2);    
    for (const auto& byte : bytes) {
        result += hexmap[byte >> 4];
        result += hexmap[byte & 0xf];
    }

    return result;
}

std::optional<std::vector<uint8_t>> hex_to_bytes(const std::string& hex) {
    // TODO: convert `hex` to bytes; return std::nullopt on invalid input
    if (hex.size() % 2 != 0) return std::nullopt;

    std::vector<uint8_t> bytes{};
    bytes.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2) {
        char first = hex[i];
        char second = hex[i + 1];

        if (!std::isxdigit(first) || !std::isxdigit(second)) return std::nullopt;

        uint8_t byte = std::stoi(std::string{first, second}, nullptr, 16);
        bytes.push_back(byte);
    }

    return bytes;
    
}

std::array<uint8_t, 4> swap_endian_u32(uint32_t num) {
    return {
    static_cast<uint8_t>(num & 0xff),
    static_cast<uint8_t>((num >> 8)  & 0xff),
    static_cast<uint8_t>((num >> 16) & 0xff),
    static_cast<uint8_t>((num >> 24) & 0xff),
    // TODO: return the 4 bytes of `num` in reversed (endian-swapped) order
    };
}

std::optional<uint64_t> parse_satoshis(const std::string& input) {
    
    if (input.empty()) return std::nullopt;

    for (const char c : input) {
        if (!std::isdigit(c)) return std::nullopt;
    }

    try {
        uint64_t result = std::stoul(input);
        return result;
    } catch (...) {
        return std::nullopt;
    }

    // TODO: parse `input` as an unsigned satoshi amount; std::nullopt on failure
 
}

ScriptType classify_script(const std::vector<uint8_t>& script) {
    // TODO: classify `script` as P2PKH (starts with 0x76 0xa9 0x14),
    //       P2WPKH (starts with 0x00 0x14), otherwise Unknown
    if (script.size() >= 3 &&
        script[0] == 0x76 &&
        script[1] == 0xa9 &&
        script[2] == 0x14) {
            return ScriptType::P2PKH;
        }

    if (script.size() >= 2 &&
        script[0] == 0x00 &&
        script[1] == 0x14) {
            return ScriptType::P2WPKH;
        }    
    return ScriptType::Unknown;
}

std::vector<uint8_t> read_pushdata(const std::vector<uint8_t>& script) {
    return std::vector<uint8_t>(script.begin() + 2, script.end());
    // TODO: return the pushdata portion of `script` (everything from index 2 onwards)
   
}

void apply_fee(uint64_t& balance, uint64_t fee) {
    // TODO: subtract `fee` from `balance` in place
    if (fee > balance){
        balance = 0;
        return;
    }
    balance -= fee;   
}

std::string move_txid(std::string txid) {
    // TODO: return a string of the form "txid: <txid>"   
    return "txid: " + txid;
}

std::optional<Opcode> opcode_from_byte(uint8_t byte) {
    // TODO: 0xac -> Opcode::OpChecksig, 0x76 -> Opcode::OpDup,
    //       anything else -> std::nullopt
    switch (byte) {
        case 0xac: return Opcode::OpChecksig;
        case 0x76: return Opcode::OpDup;
        default: return std::nullopt;
    }
   
}

UTXO consume_utxo(UTXO utxo) {
    // TODO: return `utxo` (demonstrates move semantics)    
    return utxo;
}
