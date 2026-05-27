#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "main.h"

namespace {

// 25-byte P2PKH script: OP_DUP OP_HASH160 <20-byte push> OP_EQUALVERIFY OP_CHECKSIG
const std::vector<uint8_t> kP2pkhScript = {
    0x76, 0xa9, 0x14,
    0x89, 0xab, 0xcd, 0xef, 0xab, 0xba, 0xab, 0xba, 0xab, 0xba,
    0xab, 0xba, 0xab, 0xba, 0xab, 0xba, 0xab, 0xba, 0xab, 0xba,
    0x88, 0xac,
};

// 22-byte P2WPKH script: OP_0 <20-byte push>
const std::vector<uint8_t> kP2wpkhScript = {
    0x00, 0x14,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14,
};

}  // namespace

TEST(BitcoinFunctions, DecodeHex) {
    auto bytes = decode_hex("deadbeef");
    ASSERT_TRUE(bytes.has_value());
    EXPECT_EQ(*bytes, (std::vector<uint8_t>{0xde, 0xad, 0xbe, 0xef}));

    EXPECT_FALSE(decode_hex("xyz").has_value());
    EXPECT_FALSE(decode_hex("abc").has_value());  // odd length
}

TEST(BitcoinFunctions, ToBigEndian) {
    EXPECT_EQ(to_big_endian({0x01, 0x02, 0x03, 0x04}),
              (std::vector<uint8_t>{0x04, 0x03, 0x02, 0x01}));
    EXPECT_EQ(to_big_endian({}), std::vector<uint8_t>{});
}

TEST(BitcoinFunctions, BytesToHex) {
    EXPECT_EQ(bytes_to_hex({0xde, 0xad, 0xbe, 0xef}), "deadbeef");
    EXPECT_EQ(bytes_to_hex({}), "");
}

TEST(BitcoinFunctions, HexToBytes) {
    auto bytes = hex_to_bytes("deadbeef");
    ASSERT_TRUE(bytes.has_value());
    EXPECT_EQ(*bytes, (std::vector<uint8_t>{0xde, 0xad, 0xbe, 0xef}));

    EXPECT_FALSE(hex_to_bytes("zz").has_value());
}

TEST(BitcoinFunctions, SwapEndianU32) {
    EXPECT_EQ(swap_endian_u32(0x01020304u),
              (std::array<uint8_t, 4>{0x04, 0x03, 0x02, 0x01}));
}

TEST(BitcoinFunctions, ParseSatoshis) {
    auto value = parse_satoshis("100");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(*value, 100u);

    EXPECT_FALSE(parse_satoshis("abc").has_value());
    EXPECT_FALSE(parse_satoshis("").has_value());
}

TEST(BitcoinFunctions, ClassifyScript) {
    EXPECT_EQ(classify_script(kP2pkhScript), ScriptType::P2PKH);
    EXPECT_EQ(classify_script(kP2wpkhScript), ScriptType::P2WPKH);
    EXPECT_EQ(classify_script({0xff, 0xee, 0xdd}), ScriptType::Unknown);
}

TEST(BitcoinFunctions, OutpointEquality) {
    Outpoint a{"abc", 0};
    Outpoint b{"abc", 0};
    Outpoint c{"abc", 1};
    EXPECT_EQ(a, b);
    EXPECT_FALSE(a == c);
}

TEST(BitcoinFunctions, ReadPushdata) {
    auto pushdata = read_pushdata(kP2wpkhScript);
    std::vector<uint8_t> expected(kP2wpkhScript.begin() + 2, kP2wpkhScript.end());
    EXPECT_EQ(pushdata, expected);
    EXPECT_EQ(pushdata.size(), static_cast<std::size_t>(20));
}

TEST(BitcoinFunctions, WalletBalance) {
    TestWallet wallet;
    wallet.confirmed = 500;
    EXPECT_EQ(wallet.balance(), 500u);

    const Wallet& as_base = wallet;
    EXPECT_EQ(as_base.balance(), 500u);
}

TEST(BitcoinFunctions, ApplyFee) {
    uint64_t balance = 1000;
    apply_fee(balance, 250);
    EXPECT_EQ(balance, 750u);
}

TEST(BitcoinFunctions, MoveTxid) {
    EXPECT_EQ(move_txid("abc"), "txid: abc");
}

TEST(BitcoinFunctions, OpcodeFromByte) {
    auto checksig = opcode_from_byte(0xac);
    ASSERT_TRUE(checksig.has_value());
    EXPECT_EQ(*checksig, Opcode::OpChecksig);

    auto dup = opcode_from_byte(0x76);
    ASSERT_TRUE(dup.has_value());
    EXPECT_EQ(*dup, Opcode::OpDup);

    EXPECT_FALSE(opcode_from_byte(0xff).has_value());
}

TEST(BitcoinFunctions, ConsumeUtxo) {
    UTXO original{{0x01, 0x02, 0x03}, 0, 100};
    UTXO copy = original;
    UTXO returned = consume_utxo(std::move(copy));
    EXPECT_EQ(returned, original);
}
