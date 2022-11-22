#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <threads.h>

struct EPCSPRNG;
typedef struct EPCSPRNG EPCSPRNG;

/**
 * @brief create a new instance of the EPCSPRNG.
 * 
 * @param[in] key the key as unsigned octets.
 * @param[in] keylen_octets length of the key in octets.
 * @return the new instance or NULL if something went wrong.
 */
EPCSPRNG *epcsprng_new(uint8_t const *const key, size_t const keylen_octets);

/**
 * @brief create a new instance of the EPCSPRNG with an automatically generated
 * random key.
 *
 * @return the new instance or NULL if something went wrong.
 */
EPCSPRNG *epcsprng_new_auto_key(void);

/**
 * @brief destroy the provided EPCSPRNG instance.
 * @param rng the instance to be destroyed.
 *
 */
void epcsprng_destroy(EPCSPRNG *const rng);

/**
 * @brief rekey the instance with an automatically generated random key.
 *
 * @param rng the instance to be rekeyed.
 * @return true on success.
 * @return false if something went wrong.
 */
bool epcsprng_auto_rekey(EPCSPRNG *const rng);

/**
 * @brief rekey the instance with the provided key.
 *
 * @param rng the instance to be rekeyed.
 * @param[in] key the key as unsigned octets.
 * @param[in] keylen_octets the length of the key in octets.
 * @return true on succes.
 * @return false if something went wrong.
 */
bool epcsprng_rekey(EPCSPRNG *const rng, uint8_t const *const key,
                    size_t const keylen_octets);


/**
 * @brief fill the provided buffer with the output of the CSPRNG.
 *
 * @param buffer the array of unsigned octets to be filled.
 * @param[in] buflen_octets the length of the buffer in octets.
 * @param rng the instance of the CSPRNG that shall be used to fill the buffer.
 * @return true on success.
 * @return false if something went wrong.
 */
bool epcsprng_fill(uint8_t *const buffer, size_t const buflen_octets,
                   EPCSPRNG *const rng);

/**
 * @brief fill the provided buffer with the output of several CSPRNGs in
 * parallel.
 *
 * @param buffer the array of unsigned octets to be filled.
 * @param[in] buflen_octets the length of the buffer in octets.
 * @param rng the instance of the CSPRNG that shall be used to instantiate the
 * parallel generators which in turn then fill the buffer.
 * @param[in] n_parallel how many parallel generators to use.
 * @return true on success.
 * @return false if something went wrong.
 */
bool epcsprng_fill_mt(uint8_t *const buffer, size_t const buflen_octets,
                      EPCSPRNG *const rng, size_t const n_parallel);

/**
 * @brief return the buffer length per thread based upon total # of octets and #
 * of threads, quantized by blocksize_octets.
 *
 * @param[in] num_octets_total the total # of octets that shall be split between
 * the threads.
 * @param[in] blocksize_octets the number of octets per quantized block of data
 * which shan't be split.
 * @param[in] num_threads the number of threads.
 */
size_t per_thread_buflen(size_t const num_octets_total,
                         size_t const blocksize_octets,
                         size_t const num_threads) __attribute__((pure));
