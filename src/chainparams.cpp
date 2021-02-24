// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Herbsters, that it is you";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP34Height = 710000;
        consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
        consensus.BIP65Height = 918684; // bab3041e8977e0dc3eeff63fe707b92bde1dd449d8efafb248c27c8264cc311a
        consensus.BIP66Height = 811879; // 7aceee012833fa8952f8835d8b1b3ae233cd6ab08fdb27a771d2bd7bdc491894
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 35% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1580515261; // February 1, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1582934461; // February 29, 2020

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1583020861; // March 1, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1612051261; // January 31st, 2021

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1583020861; // March 1, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1612051261; // January 31st, 2021

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000ca0abbc040fc8");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x062243c20dd4db9e9f8cff5a2b2aba140f6c03c763327d8cb12a61d9a39c9bd3"); //73650

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xe4;
        pchMessageStart[1] = 0xd8;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xa1;
        nDefaultPort = 7999;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1581176461, 538909, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x8dbad1ca9ac1e7daec572b0208f1232e71d8f1e1310c9e8ed8839408ac8578c0"));
        assert(genesis.hashMerkleRoot == uint256S("0x40aba315a1bffeee4f1032fb9d6a5bb843c12637100bfda0e6b326b13d1c1b3e"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("149.28.46.64", true);
        vSeeds.emplace_back("45.77.144.188", true);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,70);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,33);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x92, 0x84, 0x93, 0xAD};
        base58Prefixes[EXT_SECRET_KEY] = {0x92, 0x84, 0x91, 0x99};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {  0, uint256S("0x8dbad1ca9ac1e7daec572b0208f1232e71d8f1e1310c9e8ed8839408ac8578c0")},
                {  1, uint256S("0xabf4bca73cab731ed994c73e31ecde029fab70d5a56947db44100a44246441c8")},
                {  2, uint256S("0xd0946697f891ed12de2c5675883d5f600a9b8108f440ca2ef58e5d9df6d9db73")},
                {  3, uint256S("0x93ef8af758d0264ccf92496c903de572ec777435d513a53966e0a21eef4bc43f")},
                {  4, uint256S("0x70686f45581171e53a218d609423ad9fafe714abb6785f4f2ee31ab53864c575")},
                {  5, uint256S("0x94cae2884c30add15ad9c3e8e64c81f602c07838a80cf67b07284ca4dd299d4a")},
                {  6, uint256S("0xa6574dfea6cf2a39d65153ba31898528c8fe7ad3c359658d43070c1a8b3132c3")},
                {  7, uint256S("0xcdb79dc618bc71d603f6ba7bdc4a8c8ac6137e2639bfce042969fc072aab1a47")},
                {  8, uint256S("0x991ec43cac183bf4544c0c2d0e7f5c8f6b9d1ee39d206a141a5df489e4445001")},
                {  9, uint256S("0x3f82382ccc25c21975240e259ec5a994fe92f7483e4d59e4d8f050a747bcf301")},
                {  10, uint256S("0x61fcbe1854d7d4b16231dc15fadecc5bb43b75fa75a0072cf6bdb4e083690626")},
                {  11, uint256S("0x503f54a937c857b46c27c90f3627c9f8aa9fa02dddd9b7c665c43addb16821c2")},
                {  12, uint256S("0x8ae976103df2d5c417ae80a26f73f83d21b69dbc121054af23246656062066e5")},
                {  13, uint256S("0x6dee9d1fb7b316f68e53f34ee65097d220137bc583f7653d8b4ff7cd1b0a423f")},
                {  14, uint256S("0x033b3a984c31a24dcfc3f299238cf8a239c6f192879dac5c417e2824b82b1f00")},
                {  15, uint256S("0x44ea753c5b04b5b00d361370ea257a4be3b09ca8d24a3484956abeb6455f4a6a")},
                {  16, uint256S("0x1c26d3b0120cc82e89cb7c460379dcc15308eb81ca00f887d888f22b49b26e22")},
                {  17, uint256S("0xac1e66c61a0b11c0831a0033b1d2adbffac4609a5767c94d5c299d30a00ff79e")},
                {  18, uint256S("0xa61c363b3efdf1df642f374a19ebf51c907022bb1d6ba3fa385d0a212c401ee4")},
                {  19, uint256S("0xae5a8cd551570eedb0f050c174442cb1a5c8197fbc427fca18cb5738f2e54338")},
                {  20, uint256S("0x0a7eaaea0768d5f1349b6f8b65142530b9a731743267577c0046d1db01f946f9")},
                {  21, uint256S("0xe69d8a005dc99ba51e01a3e167e129262462bad4e5b807b0f58b05fca93ef542")},
                {  22, uint256S("0xb24a9baa250475e9ae18685d5a2b4056cf30fc48b8ccea45f0fe7195597fa481")},
                {  23, uint256S("0xf913f44060d013303bfe50db652c1780a78cc5722b14aebc3a5fd50644bec548")},
                {  24, uint256S("0xafc8a5aed02ab70e06dfca836cc2622f15159dc8181f7d006bc312d5c0a6cdc5")},
                {  25, uint256S("0x8226fc450fcba63392273cd40204447a9152adb109e92006dceb418b8e9a9202")},
                {  26, uint256S("0x2c6b2c12fe017c1e797d354ac93d8193637a84876ccd4b6ee835ee7a00b19b4c")},
                {  27, uint256S("0xdbff8bc9f1e356a629fe84dcecd7ec6a2967685881ae1a4d9c641801813eebb4")},
                {  28, uint256S("0x94ff44e34fa682271af1664f4a164bcb2ac0b5fa699ebe3ffda7b7f56ac57d7f")},
                {  29, uint256S("0x571a4964bf51a702df8ad43c288285e96d809f75ea51c5c5266c591b5c7c7be4")},
                {  30, uint256S("0xd446fb872fb2da36402ea6cf629a8a76f297da34793bb45d92cbc64948839d90")},
                {  31, uint256S("0x3c624d5aebbcacecae7a40f6647fefdfc935a5b49774aa1a9eb88f02644ac53e")},
                {  32, uint256S("0xe2ebe7311a97e6cb309c25702f9ba474000566ef37b40b7e74b8488f6f8d02c7")},
                {  33, uint256S("0x099e9a55c8aea15428368b782a8da265c47f9e93e70f8499b96b32c28e044b8c")},
                {  34, uint256S("0xc9349eebb33d8a9e7e0aa3dbfe3a3bc905ea3680c05a0449bab897146e935690")},
                {  35, uint256S("0x5a89b790d20f685785915edac2d12e8dae1cddac370ee15f57fc94fbcbf70735")},
                {  36, uint256S("0x12a8f4d60119ccd174d18fac35385443bd915bbd85632fd5b066bd522bd45c47")},
                {  37, uint256S("0x21bd6bc81d7128ac873744b2ed6c88230b0baa27f7376e3339560da69febd050")},
                {  38, uint256S("0x432a030f0f79c87a542a5d0d97922051be7df83d04de486a8de2509abc0eeb77")},
                {  39, uint256S("0x9996dd92c3e84b47f8896bf18705fb29e075840dcf1beade45a54fafef02342c")},
                {  40, uint256S("0x7e30bc1506b03d3ff6d5f60118e666e590381991dd454689ffd7597be3451825")},
                {  41, uint256S("0x85371bdb164813bbf6ab9c342bf5bc3e813734f81476578245ce57d74e434c18")},
                {  42, uint256S("0x58916bc5b9f5c4da70db0dc24ae86717378a336b22e9d64f06a11cd7858d4bda")},
                {  43, uint256S("0x4cc1588bfe8d066606910f766d901d95aa2340f4912a1b5779f327ce524c1b8f")},
                {  44, uint256S("0xc61a234143dc038fda03fb24b308dd3a09b3b120a7332abd685a2830fd9df7a4")},
                {  45, uint256S("0xe9907fd9cd447d8f5cf8443918deecd3f4b730a2c61057f6499808747b804410")},
                {  46, uint256S("0x918b4df19d7888e38a844066c2a9e234a10a18f91da1e0a8b5024f71e1d7abdc")},
                {  47, uint256S("0xc18237f882eac8a1a76c09b712a83f3b87ed149a28c034c571701f8bb10d17ae")},
                {  48, uint256S("0x5ea82e4e63fc4c4352812d44681a5e5962169331164d7d40761a338e48e9184f")},
                {  49, uint256S("0x760bbc898e8fe4be3954360d59f330c2daa4014a94788c36bec9053f5f1d5ad3")},
                {  50, uint256S("0xe6105dd2412a029b06e99f2a3579713dc8fc22c3a77819d100eddaa8819769f9")},
                {  21638, uint256S("0x50c266b38e30a91d06312c9beda2ed7d6ff831667749550e4f6ddd9349bc9e43")},
                {  71999, uint256S("0xfa52496410a06e951970fb2dae07dfe5600dc157062e769bfe08aad833a1b2e1")},
		{  111111, uint256S("0x0554c365d45a95cc3ee2f7bd8660c4e1e9f73c3e5da0b6e3054c22c4a4b0d1dd")},
		{  175571, uint256S("0xec81c7ce41324b6ab2ad1db420c41e4b113fa03f875fd57ef34c4e44fac834b3")},
		{  200001, uint256S("0x2f290b632e3dc628f2143d3cdb6fd3e8655e1c15b613fb1408010ac8508dec01")},
		{  224724, uint256S("0x9c77097eed4874b1d5606035fff06b669267ab1e2a9f9a81ecc9fa9a2b96484d")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 59c9b9d3fec105bdc716d84caa7579503d5b05b73618d0bf2d5fa639f780a011 (height 1353397).
            1593077958, // * UNIX timestamp of last known number of transactions
            95902,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0     // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP34Height = 76;
        consensus.BIP34Hash = uint256S("8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573");
        consensus.BIP65Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6"); //343833

        pchMessageStart[0] = 0xf4;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xf6;
        pchMessageStart[3] = 0xc2;
        nDefaultPort = 17999;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1593157878, 669382, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0ef603d2b07fa30fca02702a51f052a712295fa5a13173ea874929986d55a0f7"));
        assert(genesis.hashMerkleRoot == uint256S("0x40aba315a1bffeee4f1032fb9d6a5bb843c12637100bfda0e6b326b13d1c1b3e"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("149.28.46.64", true);
        vSeeds.emplace_back("45.77.144.188", true);


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x82, 0x81, 0x84, 0xB6};
        base58Prefixes[EXT_SECRET_KEY] = {0x91, 0x81, 0x89, 0x92};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x0ef603d2b07fa30fca02702a51f052a712295fa5a13173ea874929986d55a0f7")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block a0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6 (height 343833)
            1593157878,
            0,
            0
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0xe7;
        pchMessageStart[2] = 0xd7;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 27999;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1593158556, 0, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xcd5bd250f939169e81207fefbd976d3daffb46a3bd2fadec1a89d53135f6f045"));
        assert(genesis.hashMerkleRoot == uint256S("0x40aba315a1bffeee4f1032fb9d6a5bb843c12637100bfda0e6b326b13d1c1b3e"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0xcd5bd250f939169e81207fefbd976d3daffb46a3bd2fadec1a89d53135f6f045")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x93, 0x86, 0x83, 0xF8};
        base58Prefixes[EXT_SECRET_KEY] = {0x93, 0x86, 0x87, 0x93};
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
