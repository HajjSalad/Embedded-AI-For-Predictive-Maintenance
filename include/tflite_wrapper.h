#ifndef TFLITE_WRAPPER_H
#define TFLITE_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void tflite_setup(void);
void tflite_run_inference(void);

#ifdef __cplusplus
}
#endif

#endif // TFLITE_WRAPPER_H
