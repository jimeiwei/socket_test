/*
 * sm2s_locl.c
 *
 *  Created on: 2012-8-22
 *      Author: zweib
 */

#ifndef HEADER_SM2S_LOCL_H
#define HEADER_SM2S_LOCL_H

#include <openssl/sm2dsa.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct sm2dsa_data_st {
    /* SM2_KEY_METH_DATA part */
    int (*init)(EC_KEY *);
    /* method (SM2DSA) specific part */
    ENGINE    *engine;
    int    flags;
    const SM2DSA_METHOD *meth;
    CRYPTO_EX_DATA ex_data;
} SM2DSA_DATA;

/** sm2dsa_check
 * checks whether ECKEY->meth_data is a pointer to a SM2DSA_DATA structure
 * and if not it removes the old meth_data and creates a SM2DSA_DATA structure.
 * \param  eckey pointer to a EC_KEY object
 * \return pointer to a SM2DSA_DATA structure
 */
SM2DSA_DATA *sm2dsa_check(EC_KEY *eckey);

extern unsigned char *openssl_def_sm2_id;
extern int openssl_def_sm2_id_len;

int sm3_getID(const unsigned char *pucDataInput, int uiInputLength,
        const unsigned char *pucID, int uiIDLength,
        EC_KEY *pucPublicKey, unsigned char *M);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_SM2S_LOCL_H */

