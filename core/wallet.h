#ifndef __WALLET_H__
#define __WALLET_H__

#include "hash.h"
#include "bitc-defs.h"
#include "bitc.h"


struct btc_tx_desc;
struct wallet;
struct config;
struct key;
struct secure_area;


struct wallet_pubkey {
   uint8 *pkey;
   size_t pkey_len;
};


void wallet_close(struct wallet *wallet);
int  wallet_open(struct config *cfg, struct secure_area *pass,
                 char **errStr, struct wallet **wallet);
int  wallet_zap_txdb(struct config *config);
int  wallet_add_key(struct wallet *wallet, const char *desc, char **btc_addr);
bool wallet_has_tx(struct wallet *wlt, const uint256 *txHash);
char *wallet_get_filename(void);
char *wallet_get_change_addr(struct wallet *wallet);
int  wallet_handle_tx(struct wallet *wlt, const uint256 *blkHash,
                      const uint8 *buf, size_t len);

uint64 wallet_get_birth(const struct wallet *wallet);
bool wallet_is_pubkey_hash160_mine(const struct wallet *wallet, const uint160 *pub_key);
bool wallet_is_pubkey_spendable(const struct wallet *wallet, const uint160 *pub_key);
int  wallet_craft_tx(struct wallet *wlt, const struct btc_tx_desc *tx_desc, btc_msg_tx *tx);
void wallet_confirm_tx_in_block(struct wallet *wallet, const btc_msg_merkleblock *blk);
struct key * wallet_lookup_pubkey(const struct wallet *wallet, const uint160 *pub_key);
bool wallet_verify(struct secure_area *pass, enum wallet_state *wlt_state);
int wallet_encrypt(struct wallet *wallet, struct secure_area *pass);
void wallet_get_bloom_filter_info(const struct wallet *wallet,
                                  uint8 **filter, uint32 *filterSize,
                                  uint32 *numHashFuncs, uint32 *tweak);

#endif /* __WALLET_H__ */
