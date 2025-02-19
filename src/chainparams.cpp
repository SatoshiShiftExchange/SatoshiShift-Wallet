// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bitcoin Green developers
// Copyright (c) 2018-2019 The Satoshishift developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1529411413, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1529413269,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1529411413,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x16;
        pchMessageStart[1] = 0x62;
        pchMessageStart[2] = 0x62;
        pchMessageStart[3] = 0xea;
        vAlertPubKey = ParseHex("4785977fe28u7u8da9c9a4b4c1b8b881f5551615f0872e7e288b0220ab4c8b3e3d4e47a69aeed22ef689ccff22836fcac9722f908d7bf30a6541f4cf958a02abef");
        nDefaultPort = 20000;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Satoshishift: 1 day
        nTargetSpacing = 2 * 60;  // Satoshishift: 2 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 200000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 150;
        nModifierUpdateBlock = 1; // we use the version 2 for SHFT

        const char* pszTimestamp = "Satoshishift";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0425977fe28u7u8da9c9a4b4c1b8b881f5551615f0872e7e288b0220ab4c8b3e3d4e47a69aeed22ef689ccff22836fcac9722f908d7bf30a6541f4cf958a02abef") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1563214616;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 467957;

 
      

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000039265457c1665f57abe4aa957287f3d19743104460613c541d8420d754a"));
        assert(genesis.hashMerkleRoot == uint256("0xe80dd2427a62d6da97ff0e461160ce4866b17b972c82408b642d46c2bdfecd14"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("155.138.234.195", "155.138.234.195"));


        // Satoshishift addresses start with 'c'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 88);
        // Satoshishift script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        // Satoshishift private keys start with 'Z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 81);
        // Satoshishift BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Satoshishift BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Satoshishift BIP44 coin type is '203' (0x800000cb)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xcb).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04067873AFD8DED0794012043DE67BCB34021DA5959D48172C5C7D5EB466303D91A4436CDA7761B4BB668BEE3E6E2BAE4ABD2771296C739CA039693C9C00A7C4E8";
        strMasternodePoolDummyAddress = "cfAxpVxZGd2h6NWH68AMRXGQxbh19zPY52";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xed;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x34;
        vAlertPubKey = ParseHex("044cc6ad807dc745893dfe342316279970a4f322dfb951580e60d0740299f20084a2628fd447f59152838cef082443772a2946d43e8ee492ca43f13b63bbdf54b1");
        nDefaultPort = 45785;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Satoshishift: 1 day
        nTargetSpacing = 2 * 60;  // Satoshishift: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 400000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1563214616;
        genesis.nNonce = 467957;




        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000039265457c1665f57abe4aa957287f3d19743104460613c541d8420d754a"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Bitcoin Green addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 98);
        // Testnet Bitcoin Green script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet Bitcoin Green BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Bitcoin Green BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "047e10b487fecfa76f9cc5219833ecfb5b438dc340838b8075581f6766a1e5a7e8a87b8d13b4c3844c268e66c0dde9f4727c9062a494ef3271962f6f804d9dc6bf";
        strMasternodePoolDummyAddress = "gdoiPQaA4W39oCdVUyEK9aucaSBfXYb5ke";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x24;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0x61;
	nDefaultPort = 44736;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Satoshishift: 1 day
        nTargetSpacing = 2 * 60;        // Satoshishift: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1563220978;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x1ce14d69a364dca72bec3007a2985da32e7d7c23be52e2faf8db685a5559336c"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 45875;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
