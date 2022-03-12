/*
 * sm2dh_locl.h
 *
 *  Created on: 2012-8-22
 *      Author: zweib
 */

#ifndef SM2DH_LOCL_H_
#define SM2DH_LOCL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <openssl/sm2dh.h>

typedef struct sm2dh_data_st {
    /* EC_KEY_METH_DATA part */
    int (*init)(EC_KEY *);
    /* method specific part */
    ENGINE  *engine;
    int flags;
    const SM2DH_METHOD *meth;
    CRYPTO_EX_DATA ex_data;
} SM2DH_DATA;

SM2DH_DATA *sm2dh_check(EC_KEY *);


#ifdef __cplusplus
}
#endif

#endif /* SM2DH_LOCL_H_ */
