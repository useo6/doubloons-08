// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
    (         0, uint256("0xbbd01e417e370842498a91038fd40da95f4a6166a231a3bed3c4671207bd8296"))
	(        25, uint256("0x52424ba26dd18c2da10170054c8c39ec649d0ac2630585e53099ac70dc360721"))
	(       125, uint256("0xa13b9e454a00927f6b6fd59eda118d76b270f09f80ff848e7f3cb9a2f47837ed"))
	(      1025, uint256("0xa59d07caeca8b8601803a72729dabb846e4a2adda0022ea212e4911824ff85ae"))
	(      5025, uint256("0xdc5ea38e4b4f68e66ec4fe3c7b742f02388bca5d90f3c340675229f8ae23f8ca"))
	(     10025, uint256("0x5fac2e11b6ab636534d0dc557f86f302b71647c9084eae6fe2ca389a37bb4e68"))
	(     11025, uint256("0xb68d83930c52a880326fdda93fa6963e95133c1592cab5c8488b8aaebb4206b3"))
	(     13025, uint256("0x5d5eb98932c5d81a1bac5fc653c2d95e648d089b2a607ca6ac15975bf05af009"))
	(     15025, uint256("0x2c4305a5e070e1f470fa3289653db98bd7dd6eb847780d6d32e65d5b901b429f"))
	(     20025, uint256("0x38d3027035e4725852203ee4a38768ce3fd12cc8d3d9ee1c00467d17d81c42be"))
	(     25025, uint256("0x005df538003a40bc5f83c299397dce6a4d2a736ab4fdf46752a8fcec5a45cf7f"))
	(     30025, uint256("0x0c3a6a48a8811b9c1683d86148b40384e0920a4020e0229bb7d3928e4c1e3168"))
	(     35000, uint256("0xbc86cab2bf3c1dba06e511b7a0830dd1252b5b860cae1ae90c61c0ff117d191a"))
	(     40025, uint256("0xafc48c6b0414bdc09ab31033ed4dd56d76c3fb29bc775060f2e393d58683625a"))
	(     43665, uint256("0xa77dbe7205f122896e3f172a0fc7e99d662cf15cf4e92324cbf69a472160a1bd"))
	(     43869, uint256("0xa55c9f9c892dc84fc97a670e79d79c3bec8f9dd9e32647fae8d8dcf13351f395"))
	(     46132, uint256("0xcab3584e46e2b038475cee3fc151930a5254989973509463cd9ad5980525c59a"))
	(     46525, uint256("0x80f62adfbb336b80c66a2eea963a705696f83787f375d72454511cef6db9ae77"))
	(     47025, uint256("0x16d4d4462499ade6076ef2996913eb4b91eb6965e9d78b2553a83974ae42b57f"))
	(     47525, uint256("0xa881a1f71726e1606211db240ea34f06343418a60739ce53195ddabee302b5de"))
	(     48025, uint256("0xb63b43ed40ab1aaec59228dcc11259a8bc1407b20257fd1283d74bc60501a158"))
	(     48525, uint256("0xe7754742b376b32a816038256f5277fa073527b6526887484ecbd8439b22eecf"))
	(     49025, uint256("0xef808fbbf7d5588394164b9f6c4190ae895134f1aa0d220f6379394e97ec07d7"))
	(     50025, uint256("0x71c30991bff5baeefb2b6d976f9e54c72a25f164c14fe2239b5de248392f9d80"))
	(     60025, uint256("0x9d7095a313497f158b65a7832e1434d06a52d76799b4d7c6db6a7f966b488013"))
	(     65025, uint256("0x6fa8c8e1980d9929b09e0d8a2536c0fe67f230b02923060ab013d459c2c17184"))
	(     65525, uint256("0xebf93cdd64236622786e8b2b55079f70db658c6b27eccd92574271507789633e"))
	(     85525, uint256("0x482eab083d59ff7846dbeedadd5bffbe31737a9ce703d39e35bb39a17982be25"))
	(     95525, uint256("0xe66cb922df396e62026b2c2c812690ce962bd3ad2a1e70b6d2f8b60732a9978b"))
	(    105525, uint256("0x2ac38e841ca3b8362aa3a7bbf3e757055518a450ce4712c73124be161a03ccc2"))
    (    110000, uint256("0xe2d99af9501e8c2af2cce48516b925ac37c60b479530c72c7f9d198f7ee6fa07"))
    (    120000, uint256("0x931dc828b580cbafe526c7db7e21fe807cba4fd7c0827e56dcf297267db13ba5"))
    (    130000, uint256("0x4ec7cc6e98f87690f90969ff85e2fa133238cb4e80766c0b64796fce5317a902"))
    (    140000, uint256("0xfcfd03560902a1b0ae6ba0de86a0992182600d57825b7a9e301fcca77e434c2c"))
    (    267269, uint256("0x896b0ce91d5d7b3512871444a05f53d34c4c0e6c338b1c6de0e6c92aa10debb9"))
    (    267270, uint256("0x595e91d2ab47f6313c48802a8befce80d83757c095350b1f3b0ce7127fe2b0f6"))
    (    300000, uint256("0xd9941fe7230bb38099fb8bfab31bfa0d54b4806e4f1b4900a3403297e5bc4a1c"))
    (    324000, uint256("0x0e57d704b97c43a97031161604412fd312e4b7de9650e8d85b5b9a4a041d8a80"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1404059363, // * UNIX timestamp of last checkpoint block
        0,    // * total number of transactions between genesis and last checkpoint //IDK!
                    //   (the tx=... number in the SetBestChain debug.log lines)
        100.0     // * estimated number of transactions per day after checkpoint //guess!
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   546, uint256("0xa0fea99a6897f531600c8ae53367b126824fd6a847b2b2b73817a95b8e27e602")) //doubloons data
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1365458829, //doubloons data
        547,
        576
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
