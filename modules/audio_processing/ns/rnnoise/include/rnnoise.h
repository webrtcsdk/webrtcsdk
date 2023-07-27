#ifndef RNNOISE_H
#define RNNOISE_H

#include <stdio.h>

#if defined(_WIN32) && defined(RNNOISE_BUILD)
#  if defined(DLL_EXPORT)
#    define RNNOISE_EXPORT __declspec(dllexport)
#  else
#    define RNNOISE_EXPORT
#  endif
#elif defined(__GNUC__) && defined(RNNOISE_BUILD)
#  define RNNOISE_EXPORT __attribute__((visibility("default")))
#else
#  define RNNOISE_EXPORT
#endif

typedef struct DenoiseState DenoiseState;
typedef struct RNNModel RNNModel;

/**
 * Return the size of DenoiseState
 */
RNNOISE_EXPORT int rnnoise_get_size(void);

/**
 * Return the number of samples processed by rnnoise_process_frame at a time
 */
RNNOISE_EXPORT int rnnoise_get_frame_size(void);

/**
 * Initializes a pre-allocated DenoiseState
 *
 * If model is NULL, the default model is used.
 *
 * See: rnnoise_create() and rnnoise_model_from_file()
 */
RNNOISE_EXPORT int rnnoise_init(DenoiseState *st, RNNModel *model);

/**
 * Allocate and initialize a DenoiseState
 *
 * If model is NULL, the default model is used.
 *
 * The returned pointer MUST be freed with rnnoise_destroy().
 */
RNNOISE_EXPORT DenoiseState *rnnoise_create(RNNModel *model);

/**
 * Free a DenoiseState produced by rnnoise_create.
 *
 * The optional custom model must be freed by rnnoise_model_free() after.
 */
RNNOISE_EXPORT void rnnoise_destroy(DenoiseState *st);

/**
 * Denoise a frame of samples
 *
 * in and out must be at least rnnoise_get_frame_size() large.
 */
RNNOISE_EXPORT float rnnoise_process_frame(DenoiseState *st, float *out, const float *in);

/**
 * Load a model from a file
 *
 * It must be deallocated with rnnoise_model_free()
 */
RNNOISE_EXPORT RNNModel *rnnoise_model_from_file(FILE *f);

/**
 * Free a custom model
 *
 * It must be called after all the DenoiseStates referring to it are freed.
 */
RNNOISE_EXPORT void rnnoise_model_free(RNNModel *model);

#endif
